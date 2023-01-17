#include"CGeneticAlgorithm.h"

CGeneticAlgorithm::CGeneticAlgorithm()
{
	i_population_size = i_population_size_const;
	d_crossover_probability = d_crossover_probability_const;
	d_mutation_probability = d_mutation_probability_const;
	i_maximum_generations = i_maximum_generations_const;
	c_best_individual = NULL;
	c_knapsack_problem = NULL;
	v_present_population = new std::vector<CIndividual*>;
	v_next_population = new std::vector<CIndividual*>;
}

CGeneticAlgorithm::CGeneticAlgorithm(int iPopulationSize, double dCrossoverProbability, double dMutationProbability, int iMaximumGenerations, CKnapsackProblem* cKnapsackProblem)
{
	i_population_size = iPopulationSize;
	d_crossover_probability = dCrossoverProbability;
	d_mutation_probability = dMutationProbability;
	i_maximum_generations = iMaximumGenerations;
	c_best_individual = NULL;
	c_knapsack_problem = cKnapsackProblem;
	v_present_population = new std::vector<CIndividual*>;
	v_next_population = new std::vector<CIndividual*>;
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
	for (int ii = 0; ii < v_present_population->size(); ii++)
	{
		delete v_present_population->at(ii);
	}
	delete v_present_population;
	for (int ii = 0; ii < v_next_population->size(); ii++)
	{
		delete v_next_population->at(ii);
	}
	delete v_next_population;
	delete c_best_individual;
}

void CGeneticAlgorithm::vRunAlgorithm()
{
	vGenerateFirstPopulation();
	for (int ii = 0; ii < i_maximum_generations; ii++)
	{
		std::cout << "Generacja: " << (ii) << std::endl;
		vFindBestYet(); //poszukiwanie najlepszego rozwi¹zania
		vGenerateNewPopulation(); //krzy¿owanie + mutowanie
		vSwapPopulations(); //przenoszenie next_population do present_population oraz usuwanie starej
	}
}

void CGeneticAlgorithm::vGenerateFirstPopulation()
{
	for (int ii = 0; ii < i_population_size; ii++)
	{
		std::vector<int>* vIndividual = new std::vector<int>;
		for (int ij = 0; ij < c_knapsack_problem->iGetItemsNumber(); ij++)
		{
			vIndividual->push_back(iGetRandomNumber(1));
		}
		v_present_population->push_back(new CIndividual(vIndividual, c_knapsack_problem));
	}
}

void CGeneticAlgorithm::vFindBestYet()
{
	if (c_best_individual == NULL)
	{
		c_best_individual = (*v_present_population)[0]->pcClone();
	}
	for (int ii = 0; ii < i_population_size; ii++)
	{
		if (c_best_individual->dFitness() < (*v_present_population)[ii]->dFitness())
		{
			delete c_best_individual;
			c_best_individual = (*v_present_population)[ii]->pcClone();
		}
	}
	std::cout << "BestYet" << std::endl;
}

void CGeneticAlgorithm::vGenerateNewPopulation()
{
	vCrossovers();
	vMutations();
}

void CGeneticAlgorithm::vSwapPopulations()
{
	for (int ii = 0; ii < v_present_population->size(); ii++)
	{
		delete v_present_population->at(ii);
	}
	delete v_present_population;
	v_present_population = new std::vector<CIndividual*>;
	v_present_population=v_next_population;
	v_next_population = new std::vector<CIndividual*>;
}

void CGeneticAlgorithm::vCrossovers()
{
	std::vector<CIndividual*>* v_children = new std::vector<CIndividual*>;
	while (v_present_population->size() > v_next_population->size())
	{
		v_children = pcBetterIndividual(v_present_population->at(iGetRandomNumber(v_present_population->size() - 1)), v_present_population->at(iGetRandomNumber(v_present_population->size() - 1)))->cvCrossover(*pcBetterIndividual(v_present_population->at(iGetRandomNumber(v_present_population->size() - 1)), v_present_population->at(iGetRandomNumber(v_present_population->size() - 1))), iGetRandomNumber(c_knapsack_problem->iGetItemsNumber()), d_crossover_probability, dGetRandomNumber());
		v_next_population->push_back((*v_children)[0]);
		v_next_population->push_back((*v_children)[1]);
		v_children = NULL;
	}
	if (i_population_size % 2 != 0)
	{
		v_next_population->pop_back();
	}
	delete v_children;
	std::cout << "Krzyzowanie" << std::endl;
}

void CGeneticAlgorithm::vMutations()
{
	for (int ii = 0; ii < v_next_population->size(); ii++)
	{
		(*v_next_population)[ii]->vMutate(d_mutation_probability);
	}
	std::cout << "mutowanie" << std::endl;
}

CIndividual* CGeneticAlgorithm::pcGetBestIndividual()
{
	return c_best_individual;
}

int CGeneticAlgorithm::iGetRandomNumber(int iBound)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, iBound);
	return distrib(gen);
}

double CGeneticAlgorithm::dGetRandomNumber()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distrib(0.0, 1.0);
	return distrib(gen);
}


CIndividual* CGeneticAlgorithm::pcBetterIndividual(CIndividual* cIndividualFirst, CIndividual* cIndividualSecond)
{
	if (cIndividualFirst->dFitness() > cIndividualSecond->dFitness())
		return cIndividualFirst;
	else
		return cIndividualSecond;
}

void CGeneticAlgorithm::vPrintBestGenotype()
{
	for (int ii = 0; ii < c_best_individual->ivGetGenotype()->size(); ii++)
	{
		std::cout << c_best_individual->ivGetGenotype()->at(ii);
	}
	std::cout << std::endl;
}
