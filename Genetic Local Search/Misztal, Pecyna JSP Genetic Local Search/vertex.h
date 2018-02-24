#pragma once
#include <vector>
using namespace std;
class vertex
{
	int machine;
	int job;
	int processingTime;
	int processedTime;
	bool wasSet;
	vector <vertex*> predecessorList;
	vertex* predecessor;
	vertex* successor;
	int biggestSoFar;
public:
	void setConjunctive(int time, vertex* pred, vertex *suc);
	vertex(int m, int j);
	void set(bool b) { wasSet = b; }
	bool wasProcessed(){return wasSet;}
	void addPredecessor(vertex* pred) { predecessorList.push_back(pred); }
	void betterAddActuallyNotPredecessorButTimeIfNeeded(int predBiggest);
	void setProcessedTime();
	void betterSetProcessedTime();
	int getbiggest(){ return biggestSoFar; }
	int getProcessedTime() { return processedTime; }
	int getProcessingTime() { return processingTime; }
	vertex *getSuccessor() { return successor; }
	void speak();
	void speakingPredecessor();
	void clear();
	~vertex();
};

