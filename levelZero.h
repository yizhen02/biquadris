#ifndef _LEVELZERO_H_
#define _LEVELZERO_H_
#include <vector>
#include <iostream>
#include "level.h"

class LevelZero: public Level{
	public:
	LevelZero(std::string file);
	char createBlock() override;
};

#endif
