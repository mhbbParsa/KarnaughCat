#pragma once


struct LogicTable
{
public:
 
    unsigned int length;
    char *character;
    bool *boolian;
    bool malloced = false;


    void incriment();
    void printbool();
    void printchar();


    LogicTable();
    LogicTable(unsigned int length);
    ~LogicTable();
    // Copy constructor: shallow copy. Copies do not own memory;
    // they are read-only views into the original array.

    LogicTable(const LogicTable &s);
    LogicTable& operator=(const LogicTable &s);

    LogicTable(LogicTable&& s);
    LogicTable& operator=(LogicTable&& s);



    const bool operator[](const unsigned int n) const;
};
