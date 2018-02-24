#include "jobsData.h"
#include <iostream>
#include <fstream>
#include <string>

void jobsData::load(char** argv)
{
	int originalNumberOfJobs = 0;
	string firstJobsS;
	int firstJobsI = 0;
	if (argv[3])
	{
		firstJobsS = argv[3];
		firstJobsI = stoi(firstJobsS);
	}
	ifstream file;
	if (*(argv[2]) == 'o')
	{
		file.open(argv[1], ios::out);
		file >> numberOFJobs >> numberOfMachines;
		int a, b;
		if (firstJobsI > 0)
		{
			originalNumberOfJobs = numberOFJobs;
			numberOFJobs = firstJobsI;
		}
		for (int i = 0; i < numberOFJobs; i++)
		{
			times.push_back(0);
		}
		for (int i = 0; i < numberOFJobs; i++)
		{
			vector<pair<int, int>> row;
			for (int j = 0; j < numberOfMachines; j++)
			{
				file >> a >> b;
				times[i] += b;
				row.push_back({ a, b });
			}
			data.push_back(row);
		}
		file.close();
	}
	if (*(argv[2]) == 't')
	{
		file.open(argv[1], ios::out);
		file >> numberOFJobs >> numberOfMachines;
		if (firstJobsI > 0)
		{
			originalNumberOfJobs = numberOFJobs;
			numberOFJobs = firstJobsI;
		}
		for (int i = 0; i < numberOFJobs; i++)
		{
			times.push_back(0);
		}
		file.ignore(1024, '\n');
		file.ignore(1024, '\n');
		int a;
		for (int i = 0; i < numberOFJobs; i++)
		{
			vector<pair<int, int>> row;
			for (int j = 0; j < numberOfMachines; j++)
			{
				file >> a;
				row.push_back({ 0, a });
				times[i] += a;
			}
			data.push_back(row);
		}
		for(int i = 0; i < originalNumberOfJobs - numberOFJobs; i++) file.ignore(1024, '\n');
		file.ignore(1024, '\n');
		file.ignore(1024, '\n');
		for (int i = 0; i < numberOFJobs; i++)
		{
			for (int j = 0; j < numberOfMachines; j++)
			{
				file >> a;
				data[i][j].first = a - 1;
			}
		}
		file.close();
	}
}

int jobsData::getMachine(int i, int j)
{
	return (data[i][j]).first;
}

int jobsData::getTime(int i, int j)
{
	return (data[i][j]).second;
}

jobsData::jobsData()
{
}


jobsData::~jobsData()
{
}
