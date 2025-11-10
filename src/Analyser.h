#pragma once
#include "SubString.h"
#include "LogicTable.h"
#include <cstdint> 
#include <vector>






enum boolresult : uint8_t
{
    False=0,
    True=1,
    DontCare=2
};
enum flags{
    verb,
    truth,
    silent,
    dontCombine,
    DefaultState
};

bool evaluateExpression(const LogicTable &table, const SubString &expression);
void makeMinterms(std::vector< std::vector<boolresult> > &mintermList, const bool *resulttable, const unsigned int numberOfVariables);
void mergeMinterms(std::vector<std::vector< std::vector<boolresult>>> &groups, const bool *resulttable, const unsigned int numberOfVariables);
void printMinterms(std::vector<std::vector< std::vector<boolresult>>> &groups, const LogicTable& table, bool result0, flags flag);