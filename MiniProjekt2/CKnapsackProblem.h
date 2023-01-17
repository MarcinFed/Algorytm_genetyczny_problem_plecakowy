#pragma once

#include<bits/bits-stdc.h>

class CKnapsackProblem
{
private:
	std::vector<double> d_v_size;
	std::vector<double> d_v_value;
	int i_items;
	double d_space;
public:
	CKnapsackProblem();
	~CKnapsackProblem();
	bool bRead(std::string sFileName);
	double dScore(std::vector<int>* ivGenotype);
	void vSetItemsNumber(int iNumber);
	void vSetSizeVector(std::vector<double> dvSize);
	void vSetValueVector(std::vector<double> dvValue);
	void vSetSpace(double iSpace);
	int iGetItemsNumber();
	bool bCheckAtributes(int iItems, double dSpace, std::vector<double> vSize, std::vector<double> vValue);
};

