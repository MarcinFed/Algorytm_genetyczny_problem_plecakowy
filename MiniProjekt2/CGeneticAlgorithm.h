#pragma once

#include<bits/bits-stdc.h>
#include<random>
#include"CIndividual.h"
#include"CProblem.h"
class CGeneticAlgorithm
{
private:
	std::vector<CIndividual*>* v_present_population;
	std::vector<CIndividual*>* v_next_population;
	int i_population_size;
	double d_crossover_probability;
	double d_mutation_probability;
	int i_maximum_generations;
	CIndividual* c_best_individual;
	CProblem* c_problem;

	int i_population_size_const = 0;
	double d_crossover_probability_const = 0;
	double d_mutation_probability_const = 0;
	int i_maximum_generations_const = 0;
public:
	CGeneticAlgorithm();
	~CGeneticAlgorithm();
	CGeneticAlgorithm(int iPopulationSize, double dCrossoverProbability, double dMutationProbability, int iMaximumGenerations, CProblem* cProblem);
	void vRunAlgorithm();
	CIndividual* pcGetBestIndividual();
	void vPrintBestGenotype();
	void vGenerateFirstPopulation();
	void vFindBestYet();
	int iGetRandomNumber(int iBound);
	double dGetRandomNumber();
	void vGenerateNewPopulation();
	void vSwapPopulations();
	void vMutations();
	void vCrossovers();
	CIndividual* pcBetterIndividual(CIndividual* cIndividualFirst, CIndividual* cIndividualSecond);
};
