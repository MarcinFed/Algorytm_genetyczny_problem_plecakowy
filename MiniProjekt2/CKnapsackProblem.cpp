#include"CKnapsackProblem.h"

CKnapsackProblem::CKnapsackProblem()
{
	i_length = 0;
	d_space = 0;
    d_v_size;
    d_v_value;

}

CKnapsackProblem::~CKnapsackProblem() {}

double CKnapsackProblem::dScore(std::vector<int>* ivGenotype)
{
    double d_size = 0;
    double d_value = 0;
    for (int ii = 0; ii < i_length; ii++)
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

void CKnapsackProblem::vSetCodeLength(int iLength)
{
    i_length = iLength;
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

int CKnapsackProblem::iGetCodeLength()
{
    return i_length;
}

bool CKnapsackProblem::bRead(std::string sFileName)
{
	std::ifstream file(sFileName);
    if (file.is_open())
    {
        int iLength;
        double dSpace;
        std::vector<double> vSize;
        std::vector<double> vValue;
        double dTemporary;
        file >> iLength;
        file >> dSpace;
        while (!file.eof())
        {
            file >> dTemporary;
            vSize.push_back(dTemporary);
            file >> dTemporary;
            vValue.push_back(dTemporary);
        }
        if (bCheckAtributes(iLength,dSpace,vSize,vValue))
        {
            vSetCodeLength(iLength);
            vSetSpace(dSpace);
            vSetSizeVector(vSize);
            vSetValueVector(vValue);
        }
        else
            return false;
        return true;
	}
	else 
    {
        std::cout << "Zla nazwa pliku, lub nie znaleziono pliku" << std::endl;
        return false;
	}
}

bool CKnapsackProblem::bCheckAtributes(int iLength, double dSpace, std::vector<double> vSize, std::vector<double> vValue)
{
    if (iLength <= 0)
    {
        std::cout << "Ujemna liczba przedmiotow" << std::endl;
        return false;
    }
    if (dSpace <= 0)
    {
        std::cout << "Ujemna pojemnosc plecaka" << std::endl;
        return false;
    }
    for (int ii = 0; ii < vSize.size(); ii++)
    {
        if (vSize.at(ii) < 0)
        {
            std::cout << "Ujemny rozmiar przedmiotu" << std::endl;
            return false;
        }
        if (vValue.at(ii) < 0)
        {
            std::cout << "Ujemna wartosc przedmiotu" << std::endl;
            return false;
        }
    }
    if (vValue.size() > iLength)
    {
        std::cout << "Ilosc przedmiotow nieodpowiada ilosci podanych wartosci" << std::endl;
        return false;
    }
    if (vSize.size() > iLength)
    {
        std::cout << "Ilosc przedmiotow nieodpowiada ilosci podanych wartosci" << std::endl;
        return false;
    }
}

