#include"CIndividual.h"

CIndividual::CIndividual()
{
	i_v_genotype = new std::vector<int>;
	c_knapsack_problem = NULL;
}

CIndividual::CIndividual(std::vector<int>* ivGenotype, CKnapsackProblem* cKnapsackProblem)
{
	i_v_genotype = ivGenotype;
	c_knapsack_problem = cKnapsackProblem;
}

CIndividual::~CIndividual()
{
	delete i_v_genotype;
}

double CIndividual::dFitness()
{
	return c_knapsack_problem->dScore(i_v_genotype);
}

CIndividual::CIndividual(const CIndividual& pcOther)
{
	i_v_genotype = new std::vector<int>;
	for (int ii = 0; ii < pcOther.i_v_genotype->size(); ii++)
	{
		i_v_genotype->push_back(pcOther.i_v_genotype->at(ii));
	}
	c_knapsack_problem = pcOther.c_knapsack_problem;
}

CIndividual* CIndividual::pcClone()
{
	return new CIndividual(*this);
}

std::vector<CIndividual*>* CIndividual::cvCrossover(CIndividual& pcOther, int iCutPlace, double dCrossoverProbability, double dProbability)
{
	std::vector<CIndividual*>* c_v_children = new std::vector<CIndividual*>;
	if (dProbability < dCrossoverProbability)
	{	//------------------------------probem tutaj---------------------------------------
		std::vector<int>* i_v_firstChild = new std::vector<int>;
		std::vector<int>* i_v_secondChild = new std::vector<int>;
		for (int ii = 0; ii < i_v_genotype->size(); ii++)
		{
			if (ii <= iCutPlace)
			{
				i_v_firstChild->push_back(i_v_genotype->at(ii));
				i_v_secondChild->push_back(pcOther.i_v_genotype->at(ii));
			}
			else
			{
				i_v_firstChild->push_back(pcOther.i_v_genotype->at(ii));
				i_v_secondChild->push_back(i_v_genotype->at(ii));
			}

		}
		c_v_children->push_back(new CIndividual(i_v_firstChild, c_knapsack_problem));
		c_v_children->push_back(new CIndividual(i_v_secondChild, c_knapsack_problem));
		std::cout << c_v_children->at(0)->ivGetGenotype()->size() << std::endl;
		std::cout << c_v_children->at(1)->ivGetGenotype()->size() << std::endl;
		// ---------------------------------------------------------------------------------
	}
	else
	{
		c_v_children->push_back(this->pcClone());
		c_v_children->push_back(pcOther.pcClone());
		std::cout << "Udalo sie bez krzyzowania!" << std::endl;
	}
	return c_v_children;
}

void CIndividual::vMutate(double dMutationProbability)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distrib(0.0, 1.0);
	for (int ii = 0; ii < i_v_genotype->size(); ii++)
	{
		if (distrib(gen) < dMutationProbability)
		{
			if (i_v_genotype->at(ii) == 1)
				(*i_v_genotype)[ii] = 0;
			else
				(*i_v_genotype)[ii] = 1;
		}
	}
}

std::vector<int>* CIndividual::ivGetGenotype()
{
	return i_v_genotype;
}




