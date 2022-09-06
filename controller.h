#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "board.h"
#include "score.h"
#include "view.h"
#include <memory>
#include <fstream>

class Score;
class Board;

class Controller{
	bool canGraph;
	int level;
	View* view;
	Score* scorePlayer1;
	Score* scorePlayer2;
	Board* player1;
	Board* player2;
	public:
        Controller(bool ableGraph,int level, std::string file1, std::string file2);// constructor
	void run(); // run the game; ask for commands
	void restart(); // restart the game
	void end(); // end the game
	void reset(); // reset the game
	void specialAction(Board*); // ask for special actions to be applied on the player provided
};

#endif
