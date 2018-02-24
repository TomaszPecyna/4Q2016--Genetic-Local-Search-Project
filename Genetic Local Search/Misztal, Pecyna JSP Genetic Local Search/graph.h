#pragma once
#include <vector>
#include "vertex.h"
#include "chromosome.h"
class graph
{
	vector<vector<vertex>> G;
	int makespan;
	int jobs;
	int machines;
public:
	void makeConjunctiveArcs(jobsData *D);
	void makeDisjunctiveArcs(chromosome *X, jobsData *D);
	void betterDisjunctiveArcsPTTogether(chromosome *X, jobsData *D, int currentMakespan);
	void speak(jobsData *D);
	void preparingForNewChromosome();
	int getMakespan() { return makespan;}
	void printSolution(jobsData *D);
	int betterMakespan(chromosome *X, jobsData *D, int currentMakespan);
	graph(jobsData *D);
	~graph();
};

