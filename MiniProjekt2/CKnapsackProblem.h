#pragma once

#include<bits/bits-stdc.h>
#include"CProblem.h"

class CKnapsackProblem : public CProblem
{
private:
	std::vector<double> d_v_size;
	std::vector<double> d_v_value;
	int i_length;
	double d_space;
public:
	CKnapsackProblem();
	~CKnapsackProblem();
	bool bRead(std::string sFileName);
	double dScore(std::vector<int>* ivGenotype);
	void vSetCodeLength(int iLength);
	void vSetSizeVector(std::vector<double> dvSize);
	void vSetValueVector(std::vector<double> dvValue);
	void vSetSpace(double iSpace);
	int iGetCodeLength();
	bool bCheckAtributes(int iItems, double dSpace, std::vector<double> vSize, std::vector<double> vValue);
};

