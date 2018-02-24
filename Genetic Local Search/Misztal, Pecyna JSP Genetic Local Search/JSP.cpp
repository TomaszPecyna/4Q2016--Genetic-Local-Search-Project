// JSP.cpp : Defines the entry point for the console application.
//

#include "iostream"
#include "jobsData.h"
#include "chromosome.h"
#include "graph.h"
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip> 

using namespace std;

bool forSorting(pair<int, int> a, pair<int, int>b);
void localSearchForOne(jobsData &data, vector <pair<chromosome*, int>> &population, graph &myGraph, int pop, int whichOne, int, int, int);
void analysis(vector <pair<chromosome*, int>> population, jobsData data, clock_t start, int, int, int);
void genetic(int argc, char** argv, int ,int, int);
void analysis3(vector <pair<chromosome*, int>> population, jobsData data, clock_t start, int POPULATION, int HOW_MANY_SKIP_IN_LS, int LOCAL_SEARCH_ITERATIONS);

const int EXCHANGE_ITERATIONS = 1;
const int SHUFFLE = 1;
const int NUMBER_OF_CROSSOVERS = 100000;
const int NOT = 2000000000;

int main(int argc, char** argv)
{
	int POPULATION = 50		;
	int LOCAL_SEARCH_ITERATIONS = 150;
	int HOW_MANY_SKIP_IN_LS = 6;
	genetic(argc, argv, POPULATION, LOCAL_SEARCH_ITERATIONS, HOW_MANY_SKIP_IN_LS);
	return 0;
}


void genetic(int argc, char** argv, int POPULATION, int LOCAL_SEARCH_ITERATIONS, int HOW_MANY_SKIP_IN_LS)
{
	clock_t start;
	start = clock();

	// ladujemy stale dane
	jobsData data;
	data.load(argv);
	graph myGraph(&data);
	myGraph.makeConjunctiveArcs(&data);

	//tworzymy populacje
	vector <pair<chromosome*, int>> population;
	population.reserve(POPULATION);
	population.resize(POPULATION);
	graph tmpGraph(&data);
	tmpGraph.makeConjunctiveArcs(&data);
	for (int i = 0; i < POPULATION; i++)
	{
		population[i] = { new chromosome, 0 };
		population[i].first->loadAndMix(&data);
		population[i].second = myGraph.betterMakespan(population[i].first, &data, NOT);
	}
	analysis(population, data, start, POPULATION, HOW_MANY_SKIP_IN_LS, LOCAL_SEARCH_ITERATIONS);
	if ((clock() - start) * 1.0 / CLOCKS_PER_SEC > 180)
	{
		return;
	}

	//wymiana
	chromosome *mom, *dad;
	int justAnArray[2];
	vector <int> randomFromPopulation;
	randomFromPopulation.reserve(POPULATION);
	randomFromPopulation.resize(POPULATION);
	for (int i = 0; i < POPULATION; i++)
	{
		randomFromPopulation[i] = i;
	}

	vector <pair<int, int>> randomFour;
	randomFour.reserve(4);
	randomFour.resize(4);

	chromosome *child;
	for (int populationNumber = 0; populationNumber < NUMBER_OF_CROSSOVERS; populationNumber++)
	{
		for (int i = 0; i < SHUFFLE; i++)
		{
			random_shuffle(randomFromPopulation.begin(), randomFromPopulation.end());
		}

		//szukanie rodzicow a potem lecimy z dzieciakami
		for (int i = 0; i < POPULATION; i = i + 4)
		{
			if (i + 4 <= POPULATION)
			{
				for (int j = i; j < i + 4; j++)
				{
					randomFour[j - i].first = randomFromPopulation[j];
					randomFour[j - i].second = population[randomFromPopulation[j]].second;
				}

				sort(randomFour.begin(), randomFour.end(), forSorting);

				mom = population[randomFour[3].first].first;
				dad = population[randomFour[2].first].first;
				justAnArray[0] = randomFour[0].first;
				justAnArray[1] = randomFour[1].first;

				for (int i = 0; i < 2; i++)
				{
					delete population[justAnArray[i]].first;

					//bierzemy sie za wlasciwy crossover
					child = new chromosome;
					if (i == 1)
						child->giveMeGenesFromMommyAndDaddy(mom, dad, mom->getSize(), data.getNumberOfJobs());
					else
						child->giveMeGenesFromMommyAndDaddy(dad, mom, mom->getSize(), data.getNumberOfJobs());

					//mutujemy tatusia
					for (int i = 0; i < EXCHANGE_ITERATIONS; i++)
					{
						dad->exchange();
					}
					myGraph.betterMakespan(dad, &data, NOT);
					population[randomFour[2].first].second = myGraph.getMakespan();
					population[justAnArray[i]].first = child;

					population[justAnArray[i]].second = myGraph.betterMakespan(population[justAnArray[i]].first, &data, NOT);
				}
			}
		}
		int random = rand() % POPULATION;
		float mutationRate = float(HOW_MANY_SKIP_IN_LS * 1.0 / 100);
		for (int i = 0; i < POPULATION * mutationRate; i++)
		{
			localSearchForOne(data, population, myGraph, 0, random, POPULATION, HOW_MANY_SKIP_IN_LS, LOCAL_SEARCH_ITERATIONS);
		}

		analysis(population, data, start, POPULATION, HOW_MANY_SKIP_IN_LS, LOCAL_SEARCH_ITERATIONS);
		if ((clock() - start) * 1.0 / CLOCKS_PER_SEC >180)
		{
			return;
		}
	}
}



bool forSorting(pair<int, int> a, pair<int, int>b)
{
	return a.second > b.second;
}


void localSearchForOne(jobsData &data, vector <pair<chromosome*, int>> &population, graph &myGraph, int pop, int whichOne, int POPULATION, int HOW_MANY_SKIP_IN_LS, int LOCAL_SEARCH_ITERATIONS)
{
	graph tmpGraph(&data);
	tmpGraph.makeConjunctiveArcs(&data);
	myGraph.preparingForNewChromosome();
	int tmpMakespan = 0;
	chromosome tmp;
	for (int j = 0; j < LOCAL_SEARCH_ITERATIONS + POPULATION *pop; j++)
	{
		tmp = *population[whichOne].first;
		for (int i = 0; i < EXCHANGE_ITERATIONS; i++)
		{
			tmp.exchange();
		}
		tmpMakespan = tmpGraph.betterMakespan(&tmp, &data, population[whichOne].second);
		if (tmpMakespan < population[whichOne].second)
		{
			*population[whichOne].first = tmp;
			population[whichOne].second = tmpMakespan;
			myGraph.betterMakespan(&tmp, &data, tmpMakespan);
			j = 0;
		}
	}
	myGraph.preparingForNewChromosome();
}

void analysis(vector <pair<chromosome*, int>> population, jobsData data, clock_t start, int POPULATION, int HOW_MANY_SKIP_IN_LS, int LOCAL_SEARCH_ITERATIONS)
{
	double duration;
	duration = (clock() - start) * 1.0 / CLOCKS_PER_SEC;

	pair<chromosome*, int> *best;

	best = &(population[0]);
	for (size_t i = 0; i < population.size(); i++)
	{
		if (population[i].second < best->second)
			best = &(population[i]);
	}

	graph toFile(&data);
	toFile.makeConjunctiveArcs(&data);
	toFile.betterMakespan(best->first, &data, best->second);
	toFile.printSolution(&data);

	double mean = 0;
	int worst = population[0].second;
	int bestv = best->second;
	for (int i = 0; i < POPULATION; i++)
	{
		mean += population[i].second;
		if (population[i].second > worst) worst = population[i].second;
	}
	mean /= POPULATION;
	ofstream file;
	file.open("czasy.txt", ios::out | ios::app);
	file << setprecision(4);
	file << bestv << " " << mean << " " << worst << " "  << duration << "00" << "\n";
	file.close();
}