#include "graph.h"
#include "iostream"
#include <fstream>


void graph::makeConjunctiveArcs(jobsData *D)
{
	for (int i = 0; i < jobs; i++)
	{
		for (int task = 0; task < machines; task++)
		{
			if (task == 0)
			{
				G[i][D->getMachine(i, task)].setConjunctive(D->getTime(i, task), NULL, &G[i][D->getMachine(i, task + 1)]);
			}
			else if (task + 1 == D->getNumberOfMachines())
			{
				G[i][D->getMachine(i, task)].setConjunctive(D->getTime(i, task), &G[i][D->getMachine(i, task - 1)], NULL);
			}
			else
			{
				G[i][D->getMachine(i, task)].setConjunctive(D->getTime(i, task), &G[i][D->getMachine(i, task - 1)], &G[i][D->getMachine(i, task + 1)]);
			}
		}
	}
}

void graph::makeDisjunctiveArcs(chromosome * X, jobsData *D)
{
	size_t chSize = X->getSize();
	int* progress = new int[jobs];
	for (int i = 0; i < jobs; i++)
	{
		progress[i] = 0;
	}
	int whichMachine;
	vertex *currentVertex;
	int job;
	for (size_t i = 0; i < chSize; i++)
	{
		job = X->getGenom(i);
		whichMachine = D->getMachine(job, progress[job]);
		currentVertex = &G[job][whichMachine];
		currentVertex->set(true);
		for (int j = 0; j < jobs; j++)
		{
			if (!G[j][whichMachine].wasProcessed())
			{
				G[j][whichMachine].addPredecessor(currentVertex);
			}
		}
		progress[job]++;
	}
	delete progress;
}


void graph::betterDisjunctiveArcsPTTogether(chromosome * X, jobsData * D, int currentMakespan)
{
	size_t chSize = X->getSize();
	int* progress = new int[jobs];
	for (int i = 0; i < jobs; i++)
	{
		progress[i] = 0;
	}
	//upperbound
	vector <int> times;
	times.reserve(jobs);
	times.resize(jobs);
	for (int i = 0; i < jobs; i++)
	{
		times[i] = D->getConTime(i);
	}

	int whichMachine;
	vertex *currentVertex;
	int job;
	int processedTime;
	int minTime;
	for (size_t i = 0; i < chSize; i++)
	{
		job = X->getGenom(i);
		whichMachine = D->getMachine(job, progress[job]);
		currentVertex = &G[job][whichMachine];
		times[job] -= currentVertex->getProcessingTime();
		minTime = times[job];
		currentVertex->set(true);
		currentVertex->betterSetProcessedTime();
		processedTime = currentVertex->getProcessedTime();
		if (processedTime > makespan) makespan = processedTime;
		if (makespan > currentMakespan)
		{
			//cout << "\nprzerwalem po " << i << " genie";
			delete[] progress;
			return;
		}
		if (processedTime + minTime > currentMakespan)
		{
			makespan = processedTime + minTime;
			//cout << "\nprzerwalem po " << i << " genie";
			delete[] progress;
			return;
		}

		for (int j = 0; j < jobs; j++)
		{
			if (!G[j][whichMachine].wasProcessed())
			{
				G[j][whichMachine].betterAddActuallyNotPredecessorButTimeIfNeeded(processedTime);
			}
		}
		progress[job]++;
	}		
	delete[] progress;
}

void graph::speak(jobsData *D)
{
	for (int i = 0; i < jobs; i++)
	{
		for (int j = 0; j < machines; j++)
		{
			G[i][j].speak();
			cout << "\t\t\t\t";
		}
		cout << endl << endl;
	}
}

void graph::preparingForNewChromosome()
{
	makespan = 0;
	for (int i = 0; i < jobs; i++)
	{
		for (int j = 0; j < machines; j++)
		{
			G[i][j].clear();
		}
	}
}


void graph::printSolution(jobsData *D)
{
	ofstream file;
	file.open("solution.txt");
	file << makespan << "\n";
	vertex *current;
	int first;
	for (int i = 0; i < jobs; i++)
	{
		first = D->getMachine(i, 0);
		current = &G[i][first];
		for (int j = 0; j < machines; j++)
		{
			file << current->getProcessedTime() - current->getProcessingTime() << " ";
			current = current->getSuccessor();
		}
		file << endl;
	}
	file.close();
}

int graph::betterMakespan(chromosome * X, jobsData * D, int currentMakespan)
{
	preparingForNewChromosome();
	betterDisjunctiveArcsPTTogether(X, D, currentMakespan);
	return getMakespan();
}

graph::graph(jobsData *D)
{
	machines = D->getNumberOfMachines();
	jobs = D->getNumberOfJobs();
	for (int i = 0; i < jobs; i++)
	{
		vector<vertex> row;
		for (int j = 0; j < machines; j++)
		{
			row.push_back(vertex(j, i));
		}
		G.push_back(row);
	}
	makespan = 0;
}

graph::~graph()
{
}
