#include <iostream>
#include"CGeneticAlgorithm.h"
#include"CKnapsackProblem.h"

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    CKnapsackProblem problem;
    problem.vSetItemsNumber(4);
    problem.vSetSpace(5);
    std::vector<double> size;
    std::vector<double> value;
    size.push_back(4);
    size.push_back(1);
    size.push_back(3);
    size.push_back(2);
    value.push_back(5);
    value.push_back(1);
    value.push_back(4);
    value.push_back(3);
    problem.vSetSizeVector(size);
    problem.vSetValueVector(value);

    CGeneticAlgorithm AG = CGeneticAlgorithm(4,0.50,0.20,1,&problem);
    AG.vRunAlgorithm();
    AG.vPrintBestGenotype();
}

