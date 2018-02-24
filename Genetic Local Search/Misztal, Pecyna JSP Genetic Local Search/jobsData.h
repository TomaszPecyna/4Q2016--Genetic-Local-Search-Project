#pragma once
#include "vector"
using namespace std;
class jobsData
{
	vector<vector<pair<int, int>>> data;
	int numberOFJobs;
	int numberOfMachines;
	vector<int> times;
public:
	void load(char**);
	int getNumberOfMachines() { return numberOfMachines; }
	int getNumberOfJobs() { return numberOFJobs; }
	int getMachine(int i, int j);
	int getTime(int i, int j);
	int getConTime(int i) { return times[i]; }
	jobsData();
	~jobsData();
};

