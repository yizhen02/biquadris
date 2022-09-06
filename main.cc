#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "controller.h"
#include "view.h"
using namespace std;

int main(int args, char *argv[]) {
	bool graphics = true;
	int level = 0;
	string file1 = "biquadris_sequence1.txt";
	string file2 = "biquadris_sequence2.txt";
	for(int i = 0; i < args; ++i) {
		string com = argv[i];
		if(com == "-text") {
			graphics = false;
		}
		if(com == "-seed") {
			++i;
			stringstream what{argv[i]};
			int seed;
			what >> seed;
			srand(seed);
		}
		if(com == "-scriptfile1") {
			++i;
			string f= argv[i];
			file1 = f;
		}
		if (com == "-scriptfile2") {
			++i;
			string f = argv[i];
			file2 = f;
		}
		if (com == "-startlevel") {
			++i;
			string num = argv[i];
			stringstream s{num};
			s >> level;
		}
	}
	Controller c{graphics, level, file1, file2};
	c.run();
}


