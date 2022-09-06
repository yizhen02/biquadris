#include "score.h"
#include "board.h"
#include "view.h"
#include <sstream>
#include <iomanip>
using namespace std;

Score::Score(View* v,int level, int horShift, int verShift): curLevel{level},
	highScore{0},curScore{0},view{v},horShift{horShift},verShift{verShift}{}

void Score::lineCleared(int numLines) {
	int n = curLevel+numLines;
	addScore(n * n);
}

void Score::blockCleared(int blockLevel) {
	int n = blockLevel + 1;
	addScore(n * n);
}

void Score::levelSetter(int lev) {
	curLevel = lev;
}

void Score::scoreReset(){
	curScore = 0;
	drawScore();
}

int Score::highScoreGetter(){
	return highScore;
}

int Score::curScoreGetter() {
	return curScore;
}

void Score::addScore(int addedVal) {
	curScore += addedVal;
	if(curScore > highScore) {
		highScore = curScore;
	}
	drawScore();
}

void Score::drawScore(){
	view->textBox(horShift + 260, verShift - 30, 90);
	stringstream s;
	s << "Score:" << setfill(' ') << setw(6) << curScore;
	string scoreStr;
	s >> scoreStr;
	view->drawString(scoreStr,horShift + 260, verShift - 30);
}
