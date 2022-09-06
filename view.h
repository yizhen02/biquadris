#ifndef _VIEW_H_
#define _VIEW_H_
#include <memory>
#include "window.h"
#include "board.h"
#include "level.h"

class Board;

class View{
	bool canGraph;
	std::unique_ptr<Xwindow> xWind;
	public:
	View(bool b = true); // constructor
	void textDisplay(Board*, Board*); // display the text output of the game
	void textBox(int, int, int); // draw a textBoax window
	void drawString(std::string, int, int); // write a string to window
	void fill(int, int,int, int color = Xwindow::Black); // draw cells to window
	bool canGraphGetter(); // check whether view wants graphics or not
	void terminateGame(Board*, Board*); // end the game and so the display
};

#endif
