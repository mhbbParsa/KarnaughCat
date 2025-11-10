#pragma once

struct SubString{
public:
    int start;
    int end;
    char *array;
    bool malloced = false;

public:
    SubString subString(const int s,const int e) const;
    unsigned int countVars() const;
    SubString getVars() const;
    void checkAllowedChar(const char* allowed);
    int length() const;

    SubString();
    SubString(unsigned int s, int e, char *a);
    SubString(unsigned int length);
    ~SubString();
    // Copy constructor: shallow copy. Copies do not own memory;
    // they are read-only views into the original array.

    SubString(const SubString &s);
    SubString& operator=(const SubString &s);

    SubString(SubString&& s);
    SubString& operator=(SubString&& s);



    const char operator[](const unsigned int n) const;
};

SubString mergeStrings(int argc, char *argv[]);