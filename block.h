#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include <string>
#include "cell.h"
#include "board.h"

class Cell;
class Board;

class Block {
    protected:
    Board* player;
    std::vector<std::vector<Cell>> board;
    char type;
    int level;
    bool is_effectheavy;
    bool is_dropped;
    int leftcorner;
    public:
    std::vector<std::vector<int>> posns;
    Block(Board* player,std::vector<std::vector<Cell>>& board, char type, bool effectHeavy, int level, bool dropped = false);
    bool downMove(int times); // move block downwards
    void attachBoard(); // attach to the player's board when initiliazing
    void leftMove(int times); // move block leftwards
    void rightMove(int times); // move block rightwards
    bool drop(); // return if the block is successfully dropped, considering outbound
    std::vector<std::vector<int>>& getposn();// get positions of cells of current block
    bool isDropped(); // return whether the block is dropped
    bool isLevelHeavy(); //return if the block is in level with heavy
    bool isEffectHeavy(); // return if the block is under special action of heavy
    bool affectByHeavy(); // return if the block is successfully moved under the possible effect of heavy.
    char getBlockType(); // return block's type
    int getLevel(); // return block's level when it is created.
    bool isFull(int, int,int); // check if the positions are available to move.
    std::vector<std::vector<int>>& getPosn(); // return the positions of cells of this block
    bool rotatable(std::vector<int>); // return whether this block can move to the specific sets of cells.
    virtual void rotate(bool clockwise, int times) = 0; // rotate the block
    bool checkPosition(); // check if the block is in in bound.
    ~Block();
};

class IBlock: public Block {
    public:
    IBlock(Board* player,std::vector<std::vector<Cell>>& board, bool effectHeavy, int level);
    void rotate(bool clockwise,int times) override;
};

class JBlock: public Block {
    public:
    JBlock(Board* player,std::vector<std::vector<Cell>>& board, bool effectHeavy, int level);
    void rotate(bool clockwise, int times) override;
};

class LBlock: public Block {
    public:
    LBlock(Board* player,std::vector<std::vector<Cell>>& board, bool effectHeavy, int level);
    void rotate(bool clockwise, int times) override;
};

class OBlock: public Block {
    public:
    OBlock(Board* player,std::vector<std::vector<Cell>>& board, bool effectHeavy, int level);
    void rotate(bool clockwise, int times) override;
};

class SBlock: public Block {
    public:
    SBlock(Board* player,std::vector<std::vector<Cell>>& board, bool effectHeavy, int level);
    void rotate(bool clockwise, int times) override;
};

class TBlock: public Block {
    public:
    TBlock(Board* player,std::vector<std::vector<Cell>>& board, bool effectHeavy, int level);
    void rotate(bool clockwise, int times) override;
};

class ZBlock: public Block {
    public:
    ZBlock(Board* player,std::vector<std::vector<Cell>>& board, bool effectHeavy, int level);
    void rotate(bool clockwise, int times) override;
};

#endif
