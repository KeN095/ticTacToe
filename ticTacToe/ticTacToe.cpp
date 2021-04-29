#include "pch.h"
#include "ticTacToe.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>

using namespace std;

ticTacToe::ticTacToe()
{
	cout << "\n" << "Welcome to Tic-Tac-Toe!" << endl; //Creation of object will display a welcome message
}

ticTacToe::~ticTacToe()
{
}

int ticTacToe::getCombinedTotalMoves() {return (totalMovesByX + totalMovesByO);}

int ticTacToe::getTotalGames() { return (winsByX + winsByO + ties); }

void ticTacToe::printBoard() {
	//Board is centered by adjusting different widths on each line and between pipes  
	cout << "\n" << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(33) << board[0] << setw(11) << "|" << setw(10) << board[1] << setw(9) << "|" << setw(7) << board[2] << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(79) << "_____________________________________________________" << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(33) << board[3] << setw(11) << "|" << setw(10) << board[4] << setw(9) << "|" << setw(7) << board[5] << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(79) << "_____________________________________________________" << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(33) << board[6] << setw(11) << "|" << setw(10) << board[7] << setw(9) << "|" << setw(7) << board[8] << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
	cout << setw(44) << "|" << setw(19) << "|" << endl;
}

bool ticTacToe::checkInput(int num) {

	if (num <= 0 || num > 9) {
		cout << "Please enter a number between 1 and 9: ";
		return false;
	}
	else if (board[num - 1] == 'X' || board[num - 1] == 'O') {
		cout << "\n" << "Player " << board[input - 1] << " has already marked that spot. Please enter another number: ";
		return false;
	}
	return true;
}

bool ticTacToe::checkAnswer(char ans) {

	if (ans == 'Y' || ans == 'N' || ans == 'y' || ans == 'n') {
		return true;
	}
	return false;
}

bool ticTacToe::checkStatus() {

	//Function checks to see whether there are any horizontal, vertical or diagonal matches on the board

	if (board[0] == board[1] && board[1] == board[2]) return true;

	else if (board[3] == board[4] && board[4] == board[5]) return true;

	else if (board[6] == board[7] && board[7] == board[8]) return true;

	else if (board[0] == board[3] && board[3] == board[6]) return true;

	else if (board[1] == board[4] && board[4] == board[7]) return true;

	else if (board[2] == board[5] && board[5] == board[8]) return true;

	else if (board[0] == board[4] && board[4] == board[8]) return true;

	else if (board[6] == board[4] && board[4] == board[2]) return true;
	
	else return false;
}

bool ticTacToe::replay() {

	//Function prompts the player to play the game again 

	unsigned char answer;

	cout << "\n" << "Would you like to play again? (Y/N): ";
	cin >> answer;

	while (!cin || !checkAnswer(answer)) {
		cout << "Invalid answer; Please try again: ";

		cin.clear();
		cin.ignore();
		cin >> input;
	}

	answer = toupper(answer); //Capitalize the players answer in case they entered it in lowercase

	if (answer == 'Y'){
		//Refills the board with numbers 1 to 9 if player wants to play again

		unsigned char num = '1';

		for (int i = 0; i < sizeof(board); i++) {
			board[i] = num++;
		} 

		game();
	}
	else {
		return false;
	}
}
	
void ticTacToe::game() {

	unsigned short int turns = 0;

	cout << "\n" << "To play the game, enter a number corresponding to the spot on the board to place your mark." << endl;

	printBoard();

	cout << "\n" << "Player ";

	this_thread::sleep_for(chrono::seconds(1)); // Small pause for a more random feeling as to who goes first

	int first = rand() % (1 + 1 - 0) + 0;

	if (first == 0) {
		player = 'X';
	}
	else {
		player = 'O';
	}

	cout << player << " is going first!" << endl;

	for (int i = 0; i < sizeof(board); i++) {

		cout << "\n" << "Player " << player << ", pick a number: ";
		cin >> input; 

		//Validating players input through function check or cin errors

		while (!cin || !checkInput(input)) {
			if (!cin) {
				cout << "That's not a numeric value! Try again: ";
			}

			cin.clear();
			cin.ignore();
			cin >> input;
		} 

		board[input - 1] = player; //Player input is recorded by subtracting one to players input and recording it to the board character array

		turns++;

		printBoard(); // Printing the board to show updated changes

		if (turns >= 5 && checkStatus()) { //Checking for a win after 5 or more turns have been made
			cout << "Player " << player << " has won!" << endl;
			
			//If either X or O wins, then increment the moves and the win they made
			if (player == 'X') { 
				
				totalMovesByX++;
				winsByX++;
			}else {
				totalMovesByO++;
				winsByO++;
			}

			summary(); //Summary call will display wins between player and calls replay function if players want to play one more game, otherwise it will close
		} 

		//Incrementing the moves a player has made and switching that player
		else if (player == 'X') {
			totalMovesByX++;
			player = 'O';
		}else {
			totalMovesByO++;
			player = 'X';
		}
	}

	if (!checkStatus()) { // If theres no winner even after the for loop is over, then it is assumed theres a tie
		ties++;

		cout << "\n" << "It's a tie!" << endl;
		summary();
	}
}

void ticTacToe::summary() {
	//This function provides a short end game summary as well as a larger summary breakdown if players do not want to play the game anymore

	cout << "\n" << "Game " << getTotalGames() << "\n\n" << "Wins By X: " << winsByX << "\n" << "Wins by O: " << winsByO <<  endl; //End game summary presents wins made by X and O

	if (!replay() && getTotalGames() > 1) { 
		//If players no longer wants to play and has played more than 1 game, then a larger summary of wins, ties, and total moves are outputted

		this_thread::sleep_for(chrono::seconds(1));
		cout << "\n" << "Total games played: " << getTotalGames();

		this_thread::sleep_for(chrono::seconds(1));
		cout << "\n\n" << "Ties: " << ties << endl;

		this_thread::sleep_for(chrono::seconds(1));
		cout << "Wins by X: " << winsByX << endl;

		this_thread::sleep_for(chrono::seconds(1));
		cout << "Wins by O: " << winsByO << endl;

		this_thread::sleep_for(chrono::seconds(1));
		cout << "\n\n" << "Total moves made: " << getCombinedTotalMoves() << endl;

		this_thread::sleep_for(chrono::seconds(1));
		cout << "\n" << "Total moves by X: " << totalMovesByX << endl;

		this_thread::sleep_for(chrono::seconds(1));
		cout << "Total moves by O: " << totalMovesByO << endl;

		cout << "\n\n" <<"Thank you for playing!" << endl;
		
		exit(0);
	}else {
		//If only played once, game will be exited 
		cout << "\n" << "Thank you for playing!" << endl;
		exit(0);
	}
}