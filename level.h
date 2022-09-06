#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include <iostream>

class Level {
	public:
	int level;
	int curBlockIndex;
        std::vector<char> blocks;
	std::string file;
	Level(int level, std::string file = ""); // Level Constructor
	virtual char createBlock()=0; // Create new blocks
	int getLevel(); // return current level
	void readFile(); // read in file
	virtual void countNotClearSetter(int); // count for level 4
	virtual int countNotClearGetter(); // set count back to 0 for level 4
};

#endif
