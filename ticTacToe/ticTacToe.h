
class ticTacToe
{
private:

	unsigned int winsByX = 0; 
	unsigned int winsByO = 0;
	unsigned int ties = 0;
	unsigned int totalMovesByX = 0;
	unsigned int totalMovesByO = 0;
	unsigned int input;
	
	char board[9] = {'1','2','3','4','5','6','7','8','9'};
	unsigned char player;

public:

	
	int getCombinedTotalMoves();  // total moves by X and O in all games: getTotalMovesByX() + getTotalMovesByO()
	int getTotalGames();  // total number of games: getWinsByX() + getWinsByO()
	
	bool checkInput(int num); // check players input
	bool checkAnswer(char ans); //checks player answer if they would like to replay the game
	bool checkStatus();
	bool replay();
	 
	void printBoard(); // prints the board
	void game(); // holds the main content of the game
	void summary(); // Displays stats from either single or total games 
	
	ticTacToe();
	~ticTacToe();
};

