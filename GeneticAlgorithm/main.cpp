#include "genetics.h"
#include <cmath>
#include <random>
#include <time.h>

class SquareRootSolution : public Solution
{
	double ans = 1.0;
	double aim = 1.0;

public:
	SquareRootSolution(double target) : aim(target) { ans = (rand() % int(aim)); };
	SquareRootSolution(double a, double target) : ans(a), aim(target) {};

	virtual SquareRootSolution* breed(Solution* a)
	{
		SquareRootSolution* a_ = reinterpret_cast<SquareRootSolution*>(a);
		return new SquareRootSolution((ans + a_->ans) / 2 + rand() % (2 * int(aim)) - aim, aim);
	}

	virtual double fitness()
	{
		if (score < 0)
		{
			/*double x = (ans * ans) - aim;
			score = exp(-x * x);*/
			score = pow(2.0, -abs((ans*ans) - aim));
		}
		return score;
	}

	double getAns() { return ans; };
};

void main()
{
	srand(time(NULL));

	GeneticAlgorithm algo;
	for (unsigned int i = 0; i < 10; ++i)
		algo.genepool.push_back(new SquareRootSolution(100.0));

	while (algo.genepool.front()->fitness() < 0.999)
	{
		algo.breed();
		printf("Best so far: %f (%f)\n",
			reinterpret_cast<SquareRootSolution*>(algo.genepool.front())->getAns(),
			algo.genepool.front()->fitness());
	}

	sort(algo.genepool.begin(), algo.genepool.end(), comp);
	printf("Best score: %f (%f)\n",
		reinterpret_cast<SquareRootSolution*>(algo.genepool.front())->getAns(),
		algo.genepool.front()->fitness());

	system("pause");
}