#include <iostream>
#include "LogicTable.h"


void LogicTable::incriment()
{
    bool carryon = 1;
    for(int i = 0; i<length;i++)
    {
        bool temp = carryon;
        carryon = boolian[i] & carryon;
        boolian[i] = boolian[i] ^ temp;
    }
}

void LogicTable::printbool()
{
    for(int i=0;i<length;i++)
    {
        std::cout<<boolian[i]<<' ';
    }
}
void LogicTable::printchar()
{
    for(int i=0;i<length;i++)
    {
        std::cout<<character[i]<<' ';
    }
}


LogicTable::LogicTable(unsigned int length) : length(length), malloced(true)
{
    character = new char[length+1];
    character[length]='\0';
    boolian = new bool[length];
    std::fill(boolian, boolian + length, false);
}
LogicTable::~LogicTable()
{
    if (malloced) 
    {
        delete[] character;
        delete[] boolian;
    }
}
// Copy constructor: shallow copy. Copies do not own memory;
// they are read-only views into the original array.

LogicTable::LogicTable(const LogicTable &s)
{
    length = s.length;
    boolian = s.boolian;
    character = s.character;
    malloced = false;
}

LogicTable& LogicTable::operator=(const LogicTable &s) {
    length = s.length;
    boolian = s.boolian;
    character = s.character;
    malloced = false;
    return *this;
}

LogicTable::LogicTable(LogicTable&& s)
{
    length = s.length;
    boolian = s.boolian;
    character = s.character;
    malloced = s.malloced;

    s.boolian = nullptr;
    s.character = nullptr;
    s.malloced = false;
}

LogicTable& LogicTable::operator=(LogicTable&& s)
{
    if (this != &s) {
        if (malloced) 
        {
            delete[] character;
            delete[] boolian;
        }
        length = s.length;
        boolian = s.boolian;
        character = s.character;
        malloced = s.malloced;

        s.boolian = nullptr;
        s.character = nullptr;
        s.malloced = false;
    }
    return *this;
}

const bool LogicTable::operator[](const unsigned int n) const
{
    return boolian[n];
}

