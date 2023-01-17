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

bool CKnapsackProblem::bRead(std::string sFileName)
{
	std::ifstream file(sFileName);
    if (file.is_open())
    {
        int iItems;
        double dSpace;
        std::vector<double> vSize;
        std::vector<double> vValue;
        double dTemporary;
        file >> iItems;
        file >> dSpace;
        while (!file.eof())
        {
            file >> dTemporary;
            vSize.push_back(dTemporary);
            file >> dTemporary;
            vValue.push_back(dTemporary);
        }
        if (bCheckAtributes(iItems,dSpace,vSize,vValue))
        {
            vSetItemsNumber(iItems);
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

bool CKnapsackProblem::bCheckAtributes(int iItems, double dSpace, std::vector<double> vSize, std::vector<double> vValue)
{
    if (iItems <= 0)
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
    if (vValue.size() > iItems)
    {
        std::cout << "Ilosc przedmiotow nieodpowiada ilosci podanych wartosci" << std::endl;
        return false;
    }
    if (vSize.size() > iItems)
    {
        std::cout << "Ilosc przedmiotow nieodpowiada ilosci podanych wartosci" << std::endl;
        return false;
    }
}

