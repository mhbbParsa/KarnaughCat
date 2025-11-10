#include <iostream>
#include <cstring>
#include <ctype.h>
#include "SubString.h"

SubString SubString::subString(const int s, const int e) const
{
    return SubString(s, e, array);
}
unsigned int SubString::countVars() const
{
    int nOfVariables = 0;
    for(unsigned int i = start; i < end; i++)
        if(isalpha(array[i]))
            nOfVariables ++;
    return nOfVariables;
}

SubString SubString::getVars() const
{
    bool seenLetter[26] = {false};
    
    int nOfVariables = 0;

    for(unsigned int i=start; i < end; i++)
        if(isalpha(array[i]) && !seenLetter[ array[i] - 'A'])
        {
            seenLetter[array[i] -'A'] = true;
            nOfVariables ++;
        }

    SubString vars(nOfVariables);

    int temp=0;
    for(int i=0; i<26; i++)
        if(seenLetter[i])
        {
            vars.array[temp] = i + 'A';
            temp++;
        }
            


    return vars;
}

void SubString::checkAllowedChar(const char* allowed)
{
    for(unsigned int i=0; i < end; i++)
    {
        bool defined = false;
        for(int j=0;allowed[j];j++)
            if(isspace(array[i]) || isalpha(array[i]) || array[i] == allowed[j])
                defined = true;
        if(!defined)
        {
            std::cout << "error:[character not defined]: " << array[i] << "\nuse -h for help" << std::endl;
            exit(1);
        }
    }
        
}

int SubString::length() const
{
    return end-start;
}

SubString::SubString(unsigned int s, int e, char *a) : start(s), end(e), array(a) {}
SubString::SubString(unsigned int length) : start(0), end(length), malloced(true)
{
    array = new char[length+1];
    array[length]='\0';
}
SubString::~SubString()
{
    if(malloced)
        delete[](array);
}
// Copy constructor: shallow copy. Copies do not own memory;
// they are read-only views into the original array.

SubString::SubString(const SubString &s)
{
    start = s.start;
    end = s.end;
    array=s.array;
    malloced = false;
}

SubString& SubString::operator=(const SubString &s) {
    start = s.start;
    end = s.end;
    array=s.array;
    malloced = false;
    return *this;
}

SubString::SubString(SubString&& s)
{
    start = s.start;
    end = s.end;
    array = s.array;
    malloced = s.malloced;

    s.array = nullptr;
    s.malloced = false;
}

SubString& SubString::operator=(SubString&& s)
{
    if (this != &s) {
        if (malloced) delete[] array;

        start = s.start;
        end = s.end;
        array = s.array;
        malloced = s.malloced;

        s.array = nullptr;
        s.malloced = false;
    }
    return *this;
}

const char SubString::operator[](const unsigned int n) const
{
    return array[n];
}

SubString mergeStrings(int argc, char *argv[])
{
    int totaLength = 0;
    for(int i=1; i < argc; i++)
        if(argv[i][0] != '-' )
            totaLength += std::strlen(argv[i]);
    
    SubString String(totaLength);
    for(int i=1, k=0; i < argc; i++)
        if(argv[i][0] != '-' )
            for(int j=0; argv[i][j]; j++, k++)
                String.array[k] = toupper(argv[i][j]);
    return String;
}
