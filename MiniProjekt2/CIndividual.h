#pragma once

#include<bits/bits-stdc.h>
#include<random>
#include"CKnapsackProblem.h"

class CIndividual
{
private:
	std::vector<int>* i_v_genotype;
	CKnapsackProblem* c_knapsack_problem;
public:
	CIndividual();
	CIndividual(std::vector<int>* ivGenotype, CKnapsackProblem* cKnapsackProblem);
	~CIndividual();
	double dFitness();
	CIndividual(const CIndividual& pcOther);
	CIndividual* pcClone();
	std::vector<CIndividual*>* cvCrossover(CIndividual& pcOther, int iCutPlace, double dCrossoverProbability, double dProbability);
	void vMutate(double dMutationProbability);
	std::vector<int>* ivGetGenotype();

};
