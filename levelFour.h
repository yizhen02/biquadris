#ifndef _LEVELFOUR_H_
#define _LEVELFOUR_H_
#include <iostream>
#include "level.h"

class LevelFour: public Level{
	int countNotClear = 0;
	public:
	LevelFour(std::string file);
	char createBlock() override;
	void countNotClearSetter(int n);
	int countNotClearGetter();
};

#endif
