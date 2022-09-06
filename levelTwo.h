#ifndef _LEVELTWO_H_
#define _LEVELTWO_H_
#include <iostream>
#include "level.h"

class LevelTwo: public Level{
	public:
	LevelTwo();
	char createBlock() override;
};

#endif
