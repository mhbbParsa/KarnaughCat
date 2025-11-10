#include <iostream>
#include "SubString.h"
#include "Analyser.h"
#include "LogicTable.h"

#include <chrono>
#include <vector>

const char ALLOWED[] = "[]{}01~&^()|!'";

#define GREEN "\033[32m"
#define RESET "\033[0m"


flags resolveFlags(int argc, char *argv[]);



int main(int argc, char *argv[]){
    auto start = std::chrono::high_resolution_clock::now();

    flags flag=resolveFlags(argc, argv);

    SubString expression = mergeStrings(argc, argv);
    expression.checkAllowedChar(ALLOWED);

    SubString vars = expression.getVars();

    LogicTable table(vars.length());
    for(int i=0;i<table.length;i++)
        table.character[i]=vars[i];

    int NofStates = 1 << vars.length();

    bool *resulttable = new bool[NofStates];

    if(flag != silent)
    {
        std::cout << "\n";
        table.printchar();
        std::cout<< " " << "result" << "\n" ;
        
        for(int i=0;i<table.length;i++)
            std::cout<< "__" ;
        std::cout<< "_______\n" ;
    }
    
    for(int i=0;i<NofStates;i++)
    {
        
        bool x = evaluateExpression(table, expression);
        if(flag != silent)
        {
            table.printbool();
            std::cout << GREEN;
            std::cout<< "   " << x << "\n" ;
            std::cout << RESET;
        }
        
        resulttable[i]=x;
        table.incriment();
    }


    
    
    
    
   
    
    
    
    
    if(vars.length()>=6)
    {
        std::cout << "\nNote: my algorithm is too slow for 6+ variables so I will not bother simplifying ¯\\_(ツ)_/¯\n";
    }
    else if(flag != truth)
    {
        std::vector<std::vector< std::vector<boolresult> > > groups(1);
        makeMinterms(groups[0], resulttable, vars.length());

        if(flag != dontCombine)
            mergeMinterms(groups, resulttable, vars.length());



        std::cout<<  "\nSimplified " << GREEN << expression.array << RESET <<" (minimal SOP form):\n\n" ;
        std::cout << GREEN;
        printMinterms(groups, table, resulttable[0], flag);
        std::cout << RESET;
    }
        

    




    std::cout<<  "\n" ;



    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nExecution time: " << elapsed.count() << " seconds\n";
    
    delete[](resulttable);
}






flags resolveFlags(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::cout << "\nerror:[no argument bruh] \nget help with -h\n\n";
        exit(1);
    }
    for(int i=1; i < argc; i++)
        if(argv[i][0] == '-' )
            switch (toupper(argv[i][1])) {
                case 'H':
                {
                    std::cout << "\nhelp: use quotes, e.g. ./Simplifier \"(A & B)\"\n";
                    std::cout << "variables can only be alphabetic letters (not case sensetive)\n\n";
                    std::cout << "allowed characters:\n";
                    std::cout << "                      brackets: [] {} ()\n";
                    std::cout << "                      and:      &\n";
                    std::cout << "                      or:       |\n";
                    std::cout << "                      xor:      ^\n";
                    std::cout << "                      not:      ~  '  !\n\n";
                    std::cout << "***       just use one flag at a time!       ***\n\n";
                    std::cout << "-h                    help\n";
                    std::cout << "-v                    include non-prime implicants\n";
                    std::cout << "-s                    simplified form only\n";
                    std::cout << "-t                    just get LogicTable\n";
                    std::cout << "-d                    disable combination\n";
                    std::cout << "-c                    cute cat\n\n";

                    exit(0);
                }

                  

                case 'V':
                {
                    return verb;
                }
                case 'S':
                {
                    return silent;
                }
                case 'T':
                {
                    return truth;
                }
                case 'D':
                {
                    return dontCombine;
                }
                case 'C':
                {
                    std::cout<<"\n[Art by Blazej Kozlowski]\n";
                    std::cout<<"       _                        \n       \\`*-.                    \n        )  _`-.                 \n       .  : `. .                \n       : _   '  \\               \n       ; *` _.   `*-._          \n       `-.-'          `-.       \n         ;       `       `.     \n         :.       .        \\    \n         . \\  .   :   .-'   .   \n         '  `+.;  ;  '      :   \n         :  '  |    ;       ;-. \n         ; '   : :`-:     _.`* ;\n[bug] .*' /  .*' ; .*`- +'  `*'\n       `*-*   `*-*  `*-*'\n\n";
                    exit(0);
                }
                
                default:
                {
                    break;
                }
                    
            }
    return DefaultState;
}



