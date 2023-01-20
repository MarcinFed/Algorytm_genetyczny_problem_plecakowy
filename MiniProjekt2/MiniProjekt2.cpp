#include <iostream>
#include"CGeneticAlgorithm.h"
#include"CKnapsackProblem.h"

int main()
{
    srand(time(NULL));
    CKnapsackProblem problem;
    if (problem.bRead("Knapsack.txt"))
    {
        CGeneticAlgorithm AG = CGeneticAlgorithm(4, 0.75, 0.50, 1000, &problem);
        AG.vRunAlgorithm();
        AG.vPrintBestGenotype();
    }
}

