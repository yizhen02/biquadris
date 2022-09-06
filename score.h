#ifndef _SCORE_H_
#define _SCORE_H_

class View;

class Score{
	int curLevel;
	int highScore;
	int curScore;
	View* view;
	int horShift;
	int verShift;
	public:
	Score(View*, int, int, int); // constructor
	void lineCleared(int); // adds score if the board has the specified number of rows cleared
	void blockCleared(int); // adds score if the board has the specified level of block that is cleared 
	void levelSetter(int); // sets Score's level to the specified level
	void scoreReset(); // reset the current Score(leaving the highest score)
	int highScoreGetter(); // return the highest score
	int curScoreGetter(); // return the current score
	void addScore(int); // add score of the specified amount
	void drawScore(); // draw the score to window
};

#endif
