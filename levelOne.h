#ifndef _LEVELONE_H_
#define _LEVELONE_H_
#include <iostream>
#include <vector>
#include "level.h"

class LevelOne: public Level{
	public:
	LevelOne();
	char createBlock() override;
};

#endif
