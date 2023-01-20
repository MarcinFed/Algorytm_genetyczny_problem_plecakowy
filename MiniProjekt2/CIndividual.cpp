#include"CIndividual.h"

CIndividual::CIndividual()
{
	c_problem = NULL;
}

CIndividual::CIndividual(CProblem* cProblem)
{
	i_v_genotype = new std::vector<int>;
	for (int ii = 0; ii < cProblem->iGetCodeLength(); ii++)
	{
		i_v_genotype->push_back(rand() % 2);
	}
	c_problem = cProblem;
}

CIndividual::CIndividual(std::vector<int>* ivGenotype, CProblem* cProblem)
{
	i_v_genotype = ivGenotype;
	c_problem = cProblem;
}

CIndividual::~CIndividual()
{
	delete i_v_genotype;
}

double CIndividual::dFitness()
{
	return c_problem->dScore(i_v_genotype);
}

CIndividual::CIndividual(const CIndividual& pcOther)
{
	i_v_genotype = new std::vector<int>;
	for (int ii = 0; ii < pcOther.i_v_genotype->size(); ii++)
	{
		i_v_genotype->push_back(pcOther.i_v_genotype->at(ii));
	}
	c_problem = pcOther.c_problem;
}

CIndividual* CIndividual::pcClone()
{
	return new CIndividual(*this);
}

std::vector<CIndividual*> CIndividual::cvCrossover(CIndividual& pcOther, int iCutPlace, double dCrossoverProbability, double dProbability)
{
	std::vector<CIndividual*> c_v_children;
	if (dProbability < dCrossoverProbability)
	{
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
		c_v_children.push_back(new CIndividual(i_v_firstChild, c_problem));
		c_v_children.push_back(new CIndividual(i_v_secondChild, c_problem));
		i_v_firstChild = NULL;
		i_v_secondChild = NULL;
		delete i_v_firstChild;
		delete i_v_secondChild;
	}
	else
	{
		c_v_children.push_back(this->pcClone());
		c_v_children.push_back(pcOther.pcClone());
	}
	return c_v_children;
}

void CIndividual::vMutate(double dMutationProbability,CIndividual* pcOther)
{
	for (int ii = 0; ii < i_v_genotype->size(); ii++)
	{
		if (pcOther->i_v_genotype->at(ii) != i_v_genotype->at(ii))
		{
			if (((double)rand() / (double)RAND_MAX) < dMutationProbability)
			{
				if (i_v_genotype->at(ii) == 1)
					(*i_v_genotype)[ii] = 0;
				else
					(*i_v_genotype)[ii] = 1;
			}
		}
	}
}

std::vector<int>* CIndividual::ivGetGenotype()
{
	return i_v_genotype;
}




