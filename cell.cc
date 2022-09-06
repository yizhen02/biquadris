#include <iostream>
#include "view.h"
#include "cell.h"
using namespace std;

const int width = 60;


Cell::Cell(): type{' '}, horShift{0}, verShift{0}, cellWidth{width},isBlind{false}, color{Xwindow::White}{
}

Cell& Cell::operator=(Cell & c) {
	type = c.type;
	horShift = c.horShift;
	verShift = c.verShift;
	cellWidth = c.cellWidth;
	relativeX = c.relativeX;
	relativeY = c.relativeY;
	view = c.view;
	isBlind = c.isBlind;
	color = c.color;
	return *this;
}

void Cell::setCell(char t){
	type = t;
	if (type == 'I') {
		color = Xwindow::Red;
	} else if (type == 'J') {
		color = Xwindow::Green;
	} else if (type == 'L') {
		color = Xwindow::Blue;
	} else if (type == 'O') {
		color = Xwindow::Cyan;
	} else if (type == 'S') {
		color = Xwindow::Yellow;
	} else if (type == 'Z') {
		color = Xwindow::Magenta;
	} else if (type == 'T') {
		color = Xwindow::Orange;
	} else if (type == '*') { // for 1x1 block for level 4
		color = Xwindow::Brown;
	} else if (type == ' ') { // for NextBlock appearance
		color = Xwindow::Black;
	}
}

int Cell::getCol(){
	return color;
}	

void Cell::resetCell(){
	type = ' ';
        horShift = 0;
        verShift = 0;
        color = Xwindow::White;
}


void Cell::setRelative(int x, int y) {
	relativeX = x;
	relativeY = y;
}

void Cell::setAbsolutePos(int horizontal, int vertical) {
	horShift = horizontal;
	verShift = vertical;
}

void Cell::attachView(View* v) {
	view = v;
}

char Cell::getType(){
	return type;
}

void Cell::setWhetherBlind(bool blind) {
	isBlind = blind;
}

void Cell::draw(int row, int col){
	if (view != nullptr) {
		if (view->canGraphGetter()) {
			if (isBlind) {
				view->fill(col*cellWidth, row*cellWidth, Xwindow::Black, cellWidth);
			} else {
				view->fill(col*cellWidth, row*cellWidth, color, cellWidth);
			}
		}
	}
}

ostream& operator<<(ostream& out, Cell& cell) {
	if(cell.isBlind) {
		out << "?";
	} else {
		out << cell.getType();
	}
	return out;
}
