#ifndef _LEVELTHREE_H_
#define _LEVELTHREE_H_
#include <iostream>
#include "level.h"

class LevelThree: public Level {
	public:
	LevelThree(std::string file);
	char createBlock() override;
};

#endif
