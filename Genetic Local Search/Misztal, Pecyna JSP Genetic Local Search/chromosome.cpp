#include "iostream"
#include "chromosome.h"
#include <algorithm>

int chromosome::exchange()
{
	int toReturn;
	int length = sequence.size();
	int a, b, tmp;
	for (int i = 0; 0 < 1000; i++)
	{
		a = rand() % length;
		b = rand() % length;
		if (a != b) break;
	}
	if (a > b) toReturn = b;
	else toReturn = a;
	tmp = sequence[a];
	sequence[a] = sequence[b];
	sequence[b] = tmp;
	return toReturn;
}

void chromosome::showSequence()
{
	for (size_t i = 0; i < sequence.size(); i++)
	{
		cout << sequence[i];
	}
}


void chromosome::giveMeGenesFromMommyAndDaddy(chromosome * mommy, chromosome * daddy, size_t size, int jobs)
{
	vector <pair<int, int>> betterMommy;
	vector <pair<int, int>> betterDaddy;
	vector <pair<int, int>> betterChild;
	
	betterMommy.reserve(size);
	betterMommy.resize(size);
	betterChild.resize(size);

	betterDaddy.reserve(size);
	betterDaddy.resize(size);
	betterDaddy.resize(size);

	int* progressMommy = new int[jobs];
	int* progressDaddy = new int[jobs];
	for (int i = 0; i < jobs; i++)
	{
		progressMommy[i] = 0;
		progressDaddy[i] = 0;
	}

	int job;

	for (size_t i = 0; i < size; i++)
	{
		job = mommy->getGenom(i);
		betterMommy[i].first = job;
		betterMommy[i].second = progressMommy[job];
		progressMommy[job]++;

		job = daddy->getGenom(i);
		betterDaddy[i].first = job;
		betterDaddy[i].second = progressDaddy[job];
		progressDaddy[job]++;
		betterChild[i].second = -1;
	}

	pair <int, int> currentGene;
	pair <int, int> geneToPlace;

	for (int i = 0; i < size / 2; i++)
	{
		betterChild[i] = betterMommy[i];
	}

	int position;
	bool isAlready;

	//mama juz oddala swoja pierwsza czesc genu dziecku, wiec...
	//...dla pierwszej polowy genow taty
	for (int i = 0; i < size / 2; i++)
	{
		currentGene = betterDaddy[i];
		isAlready = false;
		//... sprawdzamy czy jest w dziecku juz ten gen...
		for (int j = 0; j < size / 2; j++)
		{
			//... i jesli jest
			if (currentGene == betterChild[j])
			{
				//to sie cieszymy i przerywamy szukanie dla tego genu
				isAlready = true;
				break;
			}
		}
		//...jesli jednak tego genu nie ma...
		if (!isAlready)
		{
			//...to musimy go w jakims rozsadnym miejscu umiescic
			geneToPlace = currentGene;
			position = i;
			currentGene = betterMommy[position];
			//szukamy miejca tak dlugo az nie wyjdziemy poza sciane dzialowa exchange'u
			while (position < size / 2)
			{
				//szuka po calym chromosomie
				for (int k = 0; k < size; k++)
				{
					//zapetlone mapowanie, szukamy w mamie gdzie by sobie pojsc
					if (currentGene == betterDaddy[k])
					{
						//mapowanie leci dalej petla jesli znajdzie przed sciana
						if (k < size / 2)
						{
							position = k;
							k = 0;
							currentGene = betterMommy[position];
						}
						// jesli znajdzie za sciana dzialowa to na tej pozycji wstawiamy u dziecka 
						//i konczymy mapowanie dla danego elementu
						else
						{
							position = k;
							betterChild[position] = geneToPlace;
							break;
						}
					}
				}
			}

		}
	}
	//jesli wszystko przebieglo bezpiecznie mozemy wstawic geny z taty ktore zostaly
	for (int i = size/2; i < size; i++)
	{
		if (betterChild[i].second == -1)
		{
			betterChild[i] = betterDaddy[i];
		}
	}
	for (int i = 0; i < size; i++)
	{
		sequence.push_back(betterChild[i].first);
	}
	delete[] progressDaddy;
	delete[] progressMommy;
}

chromosome::chromosome()
{
}


chromosome::~chromosome()
{
}

void chromosome::loadAndMix(jobsData *data)
{
	for (int i = 0; i < data->getNumberOfJobs(); i++)
	{
		for (int j = 0; j < data->getNumberOfMachines(); j++)
		{
			sequence.push_back(i);
		}
	}
	random_shuffle(sequence.begin(), sequence.end());
	random_shuffle(sequence.begin(), sequence.end());
}