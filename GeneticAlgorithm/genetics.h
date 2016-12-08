#pragma once

#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
protected:
	double score = -1.0;
	//unsigned int age = 0;

public:
	virtual Solution* breed(Solution* a) = 0;
	virtual double fitness() = 0;

	friend class GeneticAlgorithm;
};

struct GeneticAlgorithm
{
	vector<Solution*> genepool;
	void breed();
};

bool comp(Solution* a, Solution* b)
{
	return a->fitness() > b->fitness();
}

void GeneticAlgorithm::breed()
{
	vector<Solution*> nextgen;
	sort(genepool.begin(), genepool.end(), comp);

	double best = genepool.front()->fitness();
	double worst = genepool.back()->fitness();
	double range = best - worst;

	for (vector<Solution*>::iterator a = genepool.begin(); a != genepool.end(); ++a)
	{
		for (vector<Solution*>::iterator b = a + 1; b != genepool.end(); ++b)
		{
			int x = rand() % 100;
			int y = ((*a)->fitness() + (*b)->fitness() - 2 * worst) / range * 50;

			if (x < y)
				nextgen.push_back((*a)->breed((*b)));
		}
	}

	/*for (Solution* s : genepool)
	{
		delete s;
	}

	genepool = nextgen;*/

	genepool.reserve(nextgen.size());
	genepool.insert(genepool.begin(), nextgen.begin(), nextgen.end());

	sort(genepool.begin(), genepool.end(), comp); //RM
}