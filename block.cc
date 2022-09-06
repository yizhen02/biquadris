#include <iostream>
#include <vector>
#include <string>
#include "block.h"
#include "cell.h"

using namespace std;

Block::Block(Board* player, vector<vector<Cell>>& board, char type, bool effectHeavy, int level, bool dropped):
    player{player}, board{board}, type{type}, level{level},
    is_effectheavy{effectHeavy}, is_dropped{false}, leftcorner{1} {
    }


void Block::attachBoard(){
	for (size_t i = 0; i < posns.size(); ++i) {
                        board[posns[i][0]][posns[i][1]].setCell(type);
			//cout << to_string(posns[i][0])<< " " << to_string(posns[i][1]) << type << endl;
	}
}

bool Block::downMove(int times) {
    int countDrop = 0; // count how many cells this Block can be dropped.
    if (times < 0) {
	bool exitLoop = false;
	for (size_t i = 0; i < posns.size(); ++i) {
                      	board[posns[i][0]][posns[i][1]].resetCell();
	}
    	while(!exitLoop) {
		for (size_t i = 0; i < posns.size(); ++i) {
            		if (posns[i][0] + countDrop + 1 >= 18 || (player->map[posns[i][0]+ countDrop + 1][posns[i][1]].getType() != ' ')) {
                		exitLoop = true;
				break;
            		}
        	}
		if(!exitLoop){
			countDrop += 1;
		} else if (exitLoop) {
			break;
		}
	}
	if (countDrop != 0) {
		for (size_t i = 0; i < posns.size(); i++) {
			board[posns[i][0]][posns[i][1]].resetCell();
			posns[i][0] += countDrop;
			//cout << to_string(posns[i][0])<< " " << to_string(posns[i][1]) << type << endl;
			board[posns[i][0]][posns[i][1]].setCell(type);
		}
	}
    } else {
    	bool stop = false;
    	for(int t = 0; t < times; t++) {
        	for (size_t i = 0; i < posns.size(); i++) {
            		if (posns[i][0] + 1 >= 18 || (board[posns[i][0] + 1][posns[i][1]].getType() != ' ')) {
                		stop = true;
				break;
            		}
        	}
		if (!stop){
			countDrop += 1;
		} else{
			break;
		}
    	}
    	for (size_t i = 0; i < posns.size(); i++) {
 		board[posns[i][0]][posns[i][1]].resetCell();
                posns[i][0] += countDrop;
                board[posns[i][0]][posns[i][1]].setCell(type);        
        }
    }
    bool inside = checkPosition();
    if (!inside) {
         player->endGame = true;
    }
    return inside;
}


bool Block::affectByHeavy() {
    if (level >= 3) {
        bool ok = downMove(1);
	if (ok == false) {
		return false;
	}
    }
    if (is_effectheavy){
        bool ok = downMove(1);
	if (ok == false) {
		return false;
	}
    }
    if (level < 3 && !is_effectheavy) {
    	return true;
    }
    return true;
}

void Block::leftMove(int times) {
   for (size_t i = 0; i < posns.size(); i++) {
                board[posns[i][0]][posns[i][1]].resetCell();
   }
   bool stop = false; 
   for(int i = 0; i < times; ++i) {
        for (size_t j = 0; j < posns.size(); ++j) {
            // check if there is space for the block to move
            if (posns[j][1] <= 0 || player->map[posns[j][0]][posns[j][1] - 1].getType() != ' ') {
                stop = true;
		break;
            }
        }
	if (stop == true) break;
        // adjust the position of the block
        for (size_t j = 0; j < posns.size(); ++j) {
		posns[j][1] -= 1;
        }
    	bool ok = affectByHeavy();
   	if (!ok) {
		break;
	}	
   }
   for (size_t i = 0; i < posns.size(); i++) {
             board[posns[i][0]][posns[i][1]].setCell(type);
   }
}

bool Block::checkPosition(){
	for (size_t i = 0; i < posns.size(); i++) {
            if (posns[i][0] < 3){
	    	return false;
	    }
        }
	return true;
}

void Block::rightMove(int times) {
   for (size_t i = 0; i < posns.size(); i++) {
                board[posns[i][0]][posns[i][1]].resetCell();
   }
   bool stop = false;
   for(int i = 0; i < times; ++i) {
        for (size_t j = 0; j < posns.size(); ++j) {
            // check if there is space for the block to move
            if (posns[j][1] >= 10 || player->map[posns[j][0]][posns[j][1] + 1].getType() != ' ') {
		stop = true;
                break;
            }
        }
        if (stop == true) break;
        // adjust the position of the block
        for (size_t j = 0; j < posns.size(); ++j) {
                posns[j][1] += 1;
        }
        bool ok = affectByHeavy();
        if (!ok) {
                break;
        }
    }
   for (size_t i = 0; i < posns.size(); i++) {
                board[posns[i][0]][posns[i][1]].setCell(type);
    }
}

bool Block::drop() {
    bool success = downMove(-1);
    is_dropped = true; 
    return success;
}


vector<vector<int>>& Block::getPosn() {
     vector<vector<int>>& n = posns;
     return n;
}

bool Block::isDropped() {
    return is_dropped;
}

bool Block::isLevelHeavy() {
    return level >= 3;
}

bool Block::isEffectHeavy() {
    return is_effectheavy;
}

char Block::getBlockType() {
    return type;
}

int Block::getLevel(){
	return level;
}

bool Block::isFull(int i, int x, int y) {
    int y_axis = posns[i][0] + x;
    int x_axis = posns[i][1] + y;
    if(y_axis < 0 || y_axis >= 18 || x_axis < 0 || x_axis >= 11 || (board[y_axis][x_axis].getType() != ' ')) {
	return false;
    }
    return true;
}

bool Block::rotatable(vector<int> changes){
    for (size_t i = 0; i < posns.size(); i++) {
                board[posns[i][0]][posns[i][1]].resetCell();
    }
    int first_x = changes[0];
    int first_y = changes[1];
    int second_x = changes[2];
    int second_y = changes[3]; 
    int third_x = changes[4];
    int third_y = changes[5];
    int forth_x = changes[6];
    int forth_y = changes[7];
    if(isFull(0,first_x, first_y) && isFull(1, second_x , second_y) 
    && isFull(2,third_x, third_y) && isFull(3, forth_x, forth_y)) {
        return true;
    }
    else {
        return false;
    }
}

Block::~Block() {}


// types of blocks
IBlock::IBlock(Board* player,vector<vector<Cell>>& board, bool effectHeavy, int level): 
    Block{player,board, 'I', effectHeavy, level, false} {
        posns = {{3, 0}, {3, 1}, {3, 2}, {3, 3}};
	attachBoard();
    }

void IBlock::rotate(bool clockwise, int times) {
	vector<vector<int>> changes = {{-3,0,-2,-1,-1,-2,0,-3},{3,3,2,2,1,1,0,0},
		{0,-3,-1,-2,-2,-1,-3,0},{0,0,1,1,2,2,3,3}};
	while(times > 0) {
		if (clockwise) {
			int index = leftcorner - 1;
			vector<int> actualChange = changes[index];
			if (!rotatable(actualChange)) break;
			posns[0][0] += actualChange[0];
                    	posns[0][1] += actualChange[1];
                    	posns[1][0] += actualChange[2];
                    	posns[1][1] += actualChange[3];
                    	posns[2][0] += actualChange[4];
                    	posns[2][1] += actualChange[5];
                    	posns[3][0] += actualChange[6];
                    	posns[3][1] += actualChange[7];
			leftcorner += 1;
			if (leftcorner > 4) {
				leftcorner -= 4;
			}
		} else {
			int index = leftcorner - 2;
			if (index < 0) {
				index += 4;
			}
                        vector<int> actualChange;
			for (int i = 0; i < 8; ++i) {
				actualChange.emplace_back(changes[index][i]* -1);
			}
                        if (!rotatable(actualChange)) break;
                        posns[0][0] += actualChange[0];
                        posns[0][1] += actualChange[1];
                        posns[1][0] += actualChange[2];
                        posns[1][1] += actualChange[3];
                        posns[2][0] += actualChange[4];
                        posns[2][1] += actualChange[5];
                        posns[3][0] += actualChange[6];
                        posns[3][1] += actualChange[7];
                        leftcorner -= 1;
                        if (leftcorner < 1) {
                                leftcorner += 4;
                        }	
		}
		times -= 1;
	}		
}

JBlock::JBlock(Board* player,vector<vector<Cell>>& board, bool effectHeavy, int level): 
    Block{player,board, 'J', effectHeavy, level, false} {
        posns = {{2, 0}, {3, 0}, {3, 1}, {3, 2}};
	attachBoard();
}

void JBlock::rotate(bool clockwise, int times){
    vector<vector<int>> changes = {{-1,1,-2,0,-1,-1,0,-2}, {2,1,1,2,0,1,-1,0},
    {0,-2,1,-1,0,0,-1,1}, {-1,0,0,-1,1,0,2,1}};
    while(times > 0) {
		if (clockwise) {
			int index = leftcorner - 1;
			vector<int> actualChange = changes[index];
			if (!rotatable(actualChange)) break;
			posns[0][0] += actualChange[0];
                    	posns[0][1] += actualChange[1];
                    	posns[1][0] += actualChange[2];
                    	posns[1][1] += actualChange[3];
                    	posns[2][0] += actualChange[4];
                    	posns[2][1] += actualChange[5];
                    	posns[3][0] += actualChange[6];
                    	posns[3][1] += actualChange[7];
			leftcorner += 1;
			if (leftcorner > 4) {
				leftcorner -= 4;
			}
		} else {
			int index = leftcorner - 2;
			if (index < 0) {
				index += 4;
			}
                        vector<int> actualChange;
			for (int i = 0; i < 8; ++i) {
				actualChange.emplace_back(changes[index][i]* -1);
			}
                        if (!rotatable(actualChange)) break;
                        posns[0][0] += actualChange[0];
                        posns[0][1] += actualChange[1];
                        posns[1][0] += actualChange[2];
                        posns[1][1] += actualChange[3];
                        posns[2][0] += actualChange[4];
                        posns[2][1] += actualChange[5];
                        posns[3][0] += actualChange[6];
                        posns[3][1] += actualChange[7];
                        leftcorner -= 1;
                        if (leftcorner < 1) {
                                leftcorner += 4;
                        }	
		}
		times -= 1;
    }
}
    


LBlock::LBlock(Board* player,vector<vector<Cell>>& board, bool effectHeavy, int level): 
    Block{player,board, 'L', effectHeavy, level, false} {
        posns = {{2, 2}, {3, 0}, {3, 1}, {3, 2}};
	attachBoard();
    }

void LBlock::rotate(bool clockwise, int times) {
    vector<vector<int>> changes = {{1,-1,-2,0,-1,-1,0,-2}, {0,-1,1,2,0,1,-1,0},
    {-2,0,1,-1,0,0,-1,1}, {1,2,0,-1,1,0,2,1}};
    while(times > 0) {
		if (clockwise) {
			int index = leftcorner - 1;
			vector<int> actualChange = changes[index];
			if (!rotatable(actualChange)) break;
			posns[0][0] += actualChange[0];
                    	posns[0][1] += actualChange[1];
                    	posns[1][0] += actualChange[2];
                    	posns[1][1] += actualChange[3];
                    	posns[2][0] += actualChange[4];
                    	posns[2][1] += actualChange[5];
                    	posns[3][0] += actualChange[6];
                    	posns[3][1] += actualChange[7];
			leftcorner += 1;
			if (leftcorner > 4) {
				leftcorner -= 4;
			}
		} else {
			int index = leftcorner - 2;
			if (index < 0) {
				index += 4;
			}
                        vector<int> actualChange;
			for (int i = 0; i < 8; ++i) {
				actualChange.emplace_back(changes[index][i]* -1);
			}
                        if (!rotatable(actualChange)) break;
                        posns[0][0] += actualChange[0];
                        posns[0][1] += actualChange[1];
                        posns[1][0] += actualChange[2];
                        posns[1][1] += actualChange[3];
                        posns[2][0] += actualChange[4];
                        posns[2][1] += actualChange[5];
                        posns[3][0] += actualChange[6];
                        posns[3][1] += actualChange[7];
                        leftcorner -= 1;
                        if (leftcorner < 1) {
                                leftcorner += 4;
                        }	
		}
		times -= 1;
    }
}

OBlock::OBlock(Board* player,vector<vector<Cell>>& board, bool effectHeavy, int level): 
    Block{player,board, 'O', effectHeavy, level, false} {
        posns = {{2, 0}, {2, 1}, {3, 0}, {3, 1}};
    	attachBoard();
    }

void OBlock::rotate(bool clockwise, int times){
    vector<vector<int>> changes = {{0,1,1,0,-1,0,0,-1},{1,0,0,-1,0,1,-1,0},
    {0,-1,-1,0,1,0,0,1},{-1,0,0,1,0,-1,1,0}};
    while(times > 0) {
		if (clockwise) {
			int index = leftcorner - 1;
			vector<int> actualChange = changes[index];
			if (!rotatable(actualChange)) break;
			posns[0][0] += actualChange[0];
                    	posns[0][1] += actualChange[1];
                    	posns[1][0] += actualChange[2];
                    	posns[1][1] += actualChange[3];
                    	posns[2][0] += actualChange[4];
                    	posns[2][1] += actualChange[5];
                    	posns[3][0] += actualChange[6];
                    	posns[3][1] += actualChange[7];
			leftcorner += 1;
			if (leftcorner > 4) {
				leftcorner -= 4;
			}
		} else {
			int index = leftcorner - 2;
			if (index < 0) {
				index += 4;
			}
                        vector<int> actualChange;
			for (int i = 0; i < 8; ++i) {
				actualChange.emplace_back(changes[index][i]* -1);
			}
                        if (!rotatable(actualChange)) break;
                        posns[0][0] += actualChange[0];
                        posns[0][1] += actualChange[1];
                        posns[1][0] += actualChange[2];
                        posns[1][1] += actualChange[3];
                        posns[2][0] += actualChange[4];
                        posns[2][1] += actualChange[5];
                        posns[3][0] += actualChange[6];
                        posns[3][1] += actualChange[7];
                        leftcorner -= 1;
                        if (leftcorner < 1) {
                                leftcorner += 4;
                        }	
		}
		times -= 1;
    }
}


SBlock::SBlock(Board* player,vector<vector<Cell>>& board, bool effectHeavy, int level):
    Block{player,board, 'S', effectHeavy, level, false} {
        posns = {{2, 1}, {2, 2}, {3, 0}, {3, 1}};
    	attachBoard();
    }

void SBlock::rotate(bool clockwise, int times){
    vector<vector<int>> changes = {{0,0,1,-1,-2,0,-1,-1},{1,0,0,-1,1,2,0,1},
    {-1,-1,-2,0,1,-1,0,0}, {0,1,1,2,0,-1,1,0}};
    while(times > 0) {
		if (clockwise) {
			int index = leftcorner - 1;
			vector<int> actualChange = changes[index];
			if (!rotatable(actualChange)) break;
			posns[0][0] += actualChange[0];
                    	posns[0][1] += actualChange[1];
                    	posns[1][0] += actualChange[2];
                    	posns[1][1] += actualChange[3];
                    	posns[2][0] += actualChange[4];
                    	posns[2][1] += actualChange[5];
                    	posns[3][0] += actualChange[6];
                    	posns[3][1] += actualChange[7];
			leftcorner += 1;
			if (leftcorner > 4) {
				leftcorner -= 4;
			}
		} else {
			int index = leftcorner - 2;
			if (index < 0) {
				index += 4;
			}
                        vector<int> actualChange;
			for (int i = 0; i < 8; ++i) {
				actualChange.emplace_back(changes[index][i]* -1);
			}
                        if (!rotatable(actualChange)) break;
                        posns[0][0] += actualChange[0];
                        posns[0][1] += actualChange[1];
                        posns[1][0] += actualChange[2];
                        posns[1][1] += actualChange[3];
                        posns[2][0] += actualChange[4];
                        posns[2][1] += actualChange[5];
                        posns[3][0] += actualChange[6];
                        posns[3][1] += actualChange[7];
                        leftcorner -= 1;
                        if (leftcorner < 1) {
                                leftcorner += 4;
                        }	
		}
		times -= 1;
    }
}


TBlock::TBlock(Board* player,vector<vector<Cell>>& board, bool effectHeavy, int level):
    Block{player,board, 'T', effectHeavy, level, false} {
        posns = {{2, 0}, {2, 1}, {2, 2}, {3, 1}};
	attachBoard();
    }

void TBlock::rotate(bool clockwise, int times) {
    vector<vector<int>> changes = {{-1,1,0,0,1,-1,-1,-1}, {2,1,1,0,0,-1,0,1},
    {0,-2,-1,-1,-2,0,0,0}, {-1,0,0,1,1,2,1,0}};
    while(times > 0) {
		if (clockwise) {
			int index = leftcorner - 1;
			vector<int> actualChange = changes[index];
			if (!rotatable(actualChange)) break;
			posns[0][0] += actualChange[0];
                    	posns[0][1] += actualChange[1];
                    	posns[1][0] += actualChange[2];
                    	posns[1][1] += actualChange[3];
                    	posns[2][0] += actualChange[4];
                    	posns[2][1] += actualChange[5];
                    	posns[3][0] += actualChange[6];
                    	posns[3][1] += actualChange[7];
			leftcorner += 1;
			if (leftcorner > 4) {
				leftcorner -= 4;
			}
		} else {
			int index = leftcorner - 2;
			if (index < 0) {
				index += 4;
			}
                        vector<int> actualChange;
			for (int i = 0; i < 8; ++i) {
				actualChange.emplace_back(changes[index][i]* -1);
			}
                        if (!rotatable(actualChange)) break;
                        posns[0][0] += actualChange[0];
                        posns[0][1] += actualChange[1];
                        posns[1][0] += actualChange[2];
                        posns[1][1] += actualChange[3];
                        posns[2][0] += actualChange[4];
                        posns[2][1] += actualChange[5];
                        posns[3][0] += actualChange[6];
                        posns[3][1] += actualChange[7];
                        leftcorner -= 1;
                        if (leftcorner < 1) {
                                leftcorner += 4;
                        }	
		}
		times -= 1;
    }
}


ZBlock::ZBlock(Board* player,vector<vector<Cell>>& board, bool effectHeavy, int level): 
    Block{player,board, 'Z', effectHeavy, level, false} {
        posns = {{2, 0}, {2, 1}, {3, 1}, {3, 2}};
	attachBoard();
    }

void ZBlock::rotate(bool clockwise, int times) {
    vector<vector<int>> changes = {{-1,1,0,0,-1,-1,0,-2}, {2,1,1,0,0,1,-1,0}, 
    {0,-2,-1,-1,0,0,-1,1}, {-1,0,0,1,1,0,2,1}};
    while(times > 0) {
		if (clockwise) {
			int index = leftcorner - 1;
			vector<int> actualChange = changes[index];
			if (!rotatable(actualChange)) break;
			posns[0][0] += actualChange[0];
                    	posns[0][1] += actualChange[1];
                    	posns[1][0] += actualChange[2];
                    	posns[1][1] += actualChange[3];
                    	posns[2][0] += actualChange[4];
                    	posns[2][1] += actualChange[5];
                    	posns[3][0] += actualChange[6];
                    	posns[3][1] += actualChange[7];
			leftcorner += 1;
			if (leftcorner > 4) {
				leftcorner -= 4;
			}
		} else {
			int index = leftcorner - 2;
			if (index < 0) {
				index += 4;
			}
                        vector<int> actualChange;
			for (int i = 0; i < 8; ++i) {
				actualChange.emplace_back(changes[index][i]* -1);
			}
                        if (!rotatable(actualChange)) break;
                        posns[0][0] += actualChange[0];
                        posns[0][1] += actualChange[1];
                        posns[1][0] += actualChange[2];
                        posns[1][1] += actualChange[3];
                        posns[2][0] += actualChange[4];
                        posns[2][1] += actualChange[5];
                        posns[3][0] += actualChange[6];
                        posns[3][1] += actualChange[7];
                        leftcorner -= 1;
                        if (leftcorner < 1) {
                                leftcorner += 4;
                        }	
		}
		times -= 1;
    }
}
