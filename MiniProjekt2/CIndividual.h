#pragma once

#include<bits/bits-stdc.h>
#include<random>
#include"CProblem.h"

class CIndividual
{
private:
	std::vector<int>* i_v_genotype;
	CProblem* c_problem;
public:
	CIndividual();
	CIndividual(CProblem* cProblem);
	CIndividual(std::vector<int>* ivGenotype ,CProblem* cProblem);
	~CIndividual();
	double dFitness();
	CIndividual(const CIndividual& pcOther);
	CIndividual* pcClone();
	std::vector<CIndividual*> cvCrossover(CIndividual& pcOther, int iCutPlace, double dCrossoverProbability, double dProbability);
	void vMutate(double dMutationProbability, CIndividual* pcOther);
	std::vector<int>* ivGetGenotype();

};
