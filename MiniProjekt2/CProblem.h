#pragma once
#include<bits/bits-stdc.h>

class CProblem 
{
public:
	virtual ~CProblem();
	virtual bool bRead(std::string sFileName);
	virtual double dScore(std::vector<int>* ivGenotype);
	virtual int iGetCodeLength();
};
