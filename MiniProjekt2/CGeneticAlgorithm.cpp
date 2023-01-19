#include"CGeneticAlgorithm.h"

CGeneticAlgorithm::CGeneticAlgorithm()
{
	srand(time(NULL));
	i_population_size = i_population_size_const;
	d_crossover_probability = d_crossover_probability_const;
	d_mutation_probability = d_mutation_probability_const;
	i_maximum_generations = i_maximum_generations_const;
	c_best_individual = NULL;
	c_problem = NULL;
	v_present_population = new std::vector<CIndividual*>;
	v_next_population = new std::vector<CIndividual*>;
}

CGeneticAlgorithm::CGeneticAlgorithm(int iPopulationSize, double dCrossoverProbability, double dMutationProbability, int iMaximumGenerations, CProblem* cProblem)
{
	srand(time(NULL));
	i_population_size = iPopulationSize;
	d_crossover_probability = dCrossoverProbability;
	d_mutation_probability = dMutationProbability;
	i_maximum_generations = iMaximumGenerations;
	c_best_individual = NULL;
	c_problem = cProblem;
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
		vFindBestYet(); //poszukiwanie najlepszego rozwi¹zania
		vGenerateNewPopulation(); //krzy¿owanie + mutowanie
		vSwapPopulations(); //przenoszenie next_population do present_population oraz usuwanie starej
	}
}

void CGeneticAlgorithm::vGenerateFirstPopulation()
{
	for (int ii = 0; ii < i_population_size; ii++)
	{
		v_present_population->push_back(new CIndividual(c_problem));
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
	v_present_population = v_next_population;
	v_next_population = new std::vector<CIndividual*>;
}

void CGeneticAlgorithm::vCrossovers()
{
	std::vector<CIndividual*> v_children;
	while (v_present_population->size() > v_next_population->size())
	{
		v_children = pcBetterIndividual(v_present_population->at(iGetRandomNumber(v_present_population->size())), v_present_population->at(iGetRandomNumber(v_present_population->size())))->cvCrossover(*pcBetterIndividual(v_present_population->at(iGetRandomNumber(v_present_population->size())), v_present_population->at(iGetRandomNumber(v_present_population->size()))), iGetRandomNumber((c_problem->iGetCodeLength()-1)), d_crossover_probability, dGetRandomNumber());
		v_next_population->push_back((v_children)[0]);
		v_next_population->push_back((v_children)[1]);
	}
	if (i_population_size % 2 != 0)
	{
		v_next_population->pop_back();
	}
}

void CGeneticAlgorithm::vMutations()
{
	for (int ii = 0; ii < v_next_population->size(); ii++)
	{
		(*v_next_population)[ii]->vMutate(d_mutation_probability);
	}
}

CIndividual* CGeneticAlgorithm::pcGetBestIndividual()
{
	return c_best_individual;
}

int CGeneticAlgorithm::iGetRandomNumber(int iBound)
{
	int iRandom = rand() % iBound;
	return iRandom;
}

double CGeneticAlgorithm::dGetRandomNumber()
{
	double dRandom = ((double)rand() / (double)RAND_MAX);
	return dRandom;
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
