#pragma once
#include "vector"
#include "jobsData.h"
#include <algorithm>
using namespace std;
class chromosome
{
	vector <int> sequence;
public:
	int exchange();
	void showSequence();
	void giveMeGenesFromMommyAndDaddy(chromosome *mommy, chromosome *daddy, size_t size, int jobs);
	size_t getSize() { return sequence.size(); }
	int getGenom(int i) { return sequence[i]; }
	chromosome();
	~chromosome();
	void loadAndMix(jobsData *data);
};

