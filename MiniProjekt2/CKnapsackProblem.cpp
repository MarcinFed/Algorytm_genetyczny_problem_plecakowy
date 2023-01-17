#include"CKnapsackProblem.h"

CKnapsackProblem::CKnapsackProblem()
{
	i_items = 0;
	d_space = 0;
    d_v_size;
    d_v_value;

}

CKnapsackProblem::~CKnapsackProblem() {}

double CKnapsackProblem::dScore(std::vector<int>* ivGenotype)
{
    double d_size = 0;
    double d_value = 0;
    for (int ii = 0; ii < i_items; ii++)
    {
        if (ivGenotype->at(ii) == 1)
        {
            d_size += d_v_size[ii];
            d_value += d_v_value[ii];
        }
    }
    if (d_size > d_space)
        return 0;
    else
        return d_value;
}

void CKnapsackProblem::vSetItemsNumber(int iNumber)
{
    i_items = iNumber;
}

void CKnapsackProblem::vSetSizeVector(std::vector<double> dvSize)
{
    d_v_size = dvSize;
}

void CKnapsackProblem::vSetValueVector(std::vector<double> dvValue)
{
    d_v_value = dvValue;
}

void CKnapsackProblem::vSetSpace(double dSpace)
{
    d_space = dSpace;
}

int CKnapsackProblem::iGetItemsNumber()
{
    return i_items;
}

