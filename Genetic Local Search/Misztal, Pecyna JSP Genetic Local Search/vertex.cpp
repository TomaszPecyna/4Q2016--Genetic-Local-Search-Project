#include "vertex.h"
#include "iostream"


void vertex::setConjunctive(int time, vertex * pred, vertex * suc)
{
	processingTime = time;
	predecessor = pred;
	successor = suc;
}

vertex::vertex(int m, int j)
{
	machine = m;
	job = j;
	wasSet = false;
	processedTime = 0;
	biggestSoFar = 0;
}


void vertex::betterAddActuallyNotPredecessorButTimeIfNeeded(int predBiggest)
{
	if (predBiggest > biggestSoFar) biggestSoFar = predBiggest;
}

void vertex::setProcessedTime()
{
	int biggest = 0;
	if (predecessor) biggest = predecessor->getProcessedTime();
	size_t i = predecessorList.size();
	for (size_t j = 0; j < i; j++)
	{
		if(predecessorList[j]->getProcessedTime() > biggest) biggest = predecessorList[j]->getProcessedTime();
	}
	processedTime = processingTime + biggest;
}

void vertex::betterSetProcessedTime()
{
	if (predecessor == NULL || predecessor->getProcessedTime() < biggestSoFar) 
		processedTime = biggestSoFar + processingTime; 
	else
		processedTime = predecessor->getProcessedTime() + processingTime;	
}


void vertex::speak()
{
	cout << "(" << machine << ", " << job << ")  " << "pt: " << processingTime << " ";
	for (size_t i = 0; i < predecessorList.size(); i++)
	{
		predecessorList[i]->speakingPredecessor();
	}
}

void vertex::speakingPredecessor()
{
	cout << "(" << machine << ", " << job << ") ";
}

void vertex::clear()
{
	processedTime = 0;
	wasSet = false;
	//predecessorList.clear();
	biggestSoFar = 0;
}

vertex::~vertex()
{
}
