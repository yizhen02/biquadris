#ifndef _CELL_H_
#define _CELL_H_
#include <iostream>
#include "window.h"

class View;

class Cell{
	char type;
	int relativeX;
       	int relativeY;
	int horShift;
	int verShift;
	int cellWidth;
	View* view;
	bool isBlind;
	int color;
	public:
	Cell();// constructor
	Cell& operator=(Cell &); // copy assignment constructor
	void setCell(char); // set this Cell to the specified type
	void resetCell(); // set this Cell to blank
	void setRelative(int, int); // set this cell's relative positions
	void setAbsolutePos(int, int); // set this cell's absolute positions
	void attachView(View*); // attach view to this Cell for display
	char getType(); // returns the type of this cell
	void setWhetherBlind(bool); // set this cell to either Blind or not Blind as specified
	void draw(int,int); // draw cell to Xwindow
	int getCol(); // returns the color of this cell
	friend std::ostream& operator<<(std::ostream&, Cell&); // output cells
};

std::ostream& operator<<(std::ostream&, Cell&);

#endif
