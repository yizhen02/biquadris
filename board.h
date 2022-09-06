#ifndef _BOARDD_H_
#define _BOARDD_H_
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "cell.h"
#include "block.h"
#include "score.h"
#include "view.h"
#include "nextBlock.h"
#include "levelZero.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"
#include <memory>
#include "level.h"

class Block;

class Board {
    const int width = 11; //width of board
    const int height = 18; //height of board
    // const int score; //score of board
    // const int level; //curlevel of board
    // const int player; //which player
    View * view;
    int blocksCreated;
    bool blind; 
    bool heavy; 
    bool force; 
    //bool lostt;
    Score * score; 
    int HShift;
    int VShift;
    std::string file;
  
    public:
    std::vector<std::unique_ptr<Block>> blocks; 
    std::vector<std::vector<Cell>> map;
    std::unique_ptr<Block> curBlock;
    std::unique_ptr<Level> lev;
    std::unique_ptr<NextBlock> nextBlock;
 	bool specialAvail;
    	bool endGame;
       	Board(int lev,View * v,Score * s,std::string file, int horShift, int verShift);
	~Board();
        // void setObserver(Observer *ob); //Adds ob to the boards list of observers
        void create(); // create the map of current board
        // void restBlock(int levelGenerated); //adds the block to the restingBlocks vector
        int getScore(); //Gets the current score
	int getHigh(); // Gets highest score for now
	void setCrBlock(); //current block
	void setNBlock(); // next block
        //Block* getCurBlock(); //returns the current block
	//NextBlock* getNextBlock(); //returns the next block
        int getCurLevel(); //returns the curLevel
        void unsetBlock(); // unset the features of block
        bool Blind(); //returns whether board is blind
        void setBlind(); //sets this board is blind
	void unsetBlind(); // set this board to unblind
	bool Heavy(); //returns whether board is heavy
        void setHeavy(bool heavy); //sets whether board is heavy
        bool Force(); //returns whether board has force active
        void setForce(bool force); //sets whether board has force active
        void resetBoard(); //Clears out the board for a restart
        //void setlost(bool l); //sets whether player is dead
        //bool getlost(); //returns whether player is dead
        //bool lost();
        void levelup(); // adds current board's level
        void leveldown(); // reduce current board's level
        //void generateBlock();
        const int getWidth(); // get Board's total columns
        const int getHeight(); // get Board's total rows
        void setCurLevel(int l) ; // set board to the specified level
        void drop(); // drop this board's current block got
        void moveBlock(int xShift,int yShift, int rotationShift);// move this board's current block got
	std::vector<std::vector<Cell>>& getBoard(); //Returns reference to theBoard
	void random(std::string); // Only for level 3 and four; related to whether the level is set random
	void changeBlock(char ); // change board's current block to the specified block type
	int rowCleared(); // check whether two or more rows are cleared.
	void removeRow(int); // remove rows that are full and fill in gaps
	//void clearBoard();
        //ostream &operator<<(ostream &out, const Board &g); //operator << for printing
};
#endif
