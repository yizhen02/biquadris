#include "view.h"
#include "cell.h"
#include "window.h"
#include "score.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int totalRow = 18;
const int totalCol = 11;

View::View(bool b): canGraph{b}, xWind{nullptr} {
	if(canGraph) {
		xWind = make_unique<Xwindow>(1080, 960);
		xWind->fillRectangle(0 ,0, 1080, 960, Xwindow::White);
		xWind->fillRectangle(35,55,445, 725, Xwindow::Black);
		xWind->fillRectangle(515,55,445, 725, Xwindow::Black);
		xWind->drawString(450, 50, "Biquadris");
		xWind->drawString(50, 800, "Next:");
		xWind->drawString(530, 800, "Next:");
		xWind->drawString(400, 800, "Score:");
		xWind->drawString(880,800, "Score:");
	}
}

void View::textDisplay(Board* p1, Board* p2){
	if(canGraph) {
		for (int i = 0; i < totalRow; ++i) {
                	for(int j = 0; j < totalCol; ++j) {
				fill(40+j*40, 60+i*40, 35, p1->map[i][j].getCol());
                        	//xWind->fillRectangle(40+j*40, 60+i*40, 35, 35, p1->map[i][j].getCol());
                        	fill(520+j*40, 60+i*40, 35, p2->map[i][j].getCol());
				//xWind->fillRectangle(520+j*40, 60+i*40, 35, 35, p2->map[i][j].getCol());
                	}
        	}
		for(int i = 0; i < 2; ++i) {
			for(int j = 0; j < 4; ++j) {
				fill(50+j*40, 850+i*40, 35, p1->nextBlock->getBlock()[i][j].getCol());
				//xWind->fillRectangle(50+j*40, 850+i*40, 35, 35, p1->nextBlock->getBlock()[i][j].getCol());
                                fill(530+j*40, 850+i*40, 35, p2->nextBlock->getBlock()[i][j].getCol());
				//xWind->fillRectangle(530+j*40, 850+i*40, 35, 35, p2->nextBlock->getBlock()[i][j].getCol());
			}
		}
		xWind->fillRectangle(400, 825, 100, 100, Xwindow::White);
		xWind->drawString(420, 850,to_string(p1->getScore()));
		xWind->fillRectangle(880, 825, 100, 100, Xwindow::White);
		xWind->drawString(900, 850,to_string(p2->getScore()));
		
	}
	cout << "Level:" << setfill(' ') << setw(5) << p1->getCurLevel();
	cout << "       ";
	cout << "Level:" << setfill(' ') << setw(5) << p2->getCurLevel();
	cout << endl;
	cout << "Score:" << setfill(' ') << setw(5) << p1->getScore();
	cout << "       ";
        cout << "Score:" << setfill(' ') << setw(5) << p2->getScore();
	cout << endl;
	cout << "-----------       -----------" << endl;
	vector<vector<Cell>>& axes1 = p1->map;
	vector<vector<Cell>>& axes2 = p2->map;
	for (int i = 0; i < totalRow; ++i) {
		for(int j = 0; j < totalCol; ++j) {
			cout << axes1[i][j];
		}
		cout << "       ";
		for(int j = 0; j < totalCol; ++j) {
                        cout << axes2[i][j];
                }
		cout << endl;
	}
	cout << "-----------       -----------" << endl;
	cout << "Next:             Next:      " << endl;
	vector<vector<Cell>>& c1 = p1->nextBlock->getBlock();
	vector<vector<Cell>>& c2 = p2->nextBlock->getBlock();
	for(int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << c1[i][j];
		}
		cout << "              ";
		for (int j = 0; j < 4; ++j) {
                        cout << c2[i][j];
                }
		cout << endl;
	}
}

void View::textBox(int xLoc,int yLoc, int boxWidth) {
	if (!canGraph) return;
	xWind->fillRectangle(xLoc,yLoc,boxWidth,30, Xwindow::White);
}

void View::drawString(string s, int xLoc, int yLoc) {
	if (!canGraph) return;
	xWind->drawString(xLoc,yLoc, s);
}

void View::fill(int xLoc, int yLoc,int cellWidth, int col) {
	if (!canGraph) return;
	xWind->fillRectangle(xLoc,yLoc, cellWidth, cellWidth, col);
}

bool View::canGraphGetter(){
	return canGraph;
}

void View::terminateGame(Board* p1, Board* p2){
	if (canGraphGetter()){
		int p1High = p1->getHigh();
		int p2High = p2->getHigh();
		string congrats;
		if (p1High > p2High) {
			congrats = "Player 1 wins!";
		} else if (p1High < p2High) {
			congrats = "Player 2 wins!";
		} else {
			congrats = "Tie!";
		}
		xWind->fillRectangle(0 ,0, 1260, 1080, Xwindow::White);
        	xWind->drawString(560, 500, congrats);
        	xWind->drawString(400, 700, "Player 1's high score: "+to_string(p1High));
        	xWind->drawString(400, 800, "Player 2's high score: "+to_string(p2High));
	}
}
