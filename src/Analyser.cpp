#include "Analyser.h"
#include "SubString.h"
#include "LogicTable.h"
#include <vector>
#include <iostream>



enum brackettype{
    normal = 1,
    square = 2,
    curly  = 3
};
#define NofOperations 4
enum operate{
    OR=0,
    XOR=1,
    AND=2,
    NOT=3
};


bool evaluateExpression(const LogicTable &table, const SubString &expression)
{
    int zero=0, one=0;
    int firstBracket = -1 ,lastBracket = -1, nonClosedBracket = 0 , majorBracket=0;
    brackettype Btype;
    for(int operation=0; operation < NofOperations; operation++)
    {
        zero =0;
        one =0;
        majorBracket=0;
        nonClosedBracket = 0;
        
        for(int i=expression.start; i<expression.end ;i++)
        {

           
            switch (expression[i])
            {
                case '|':
                {
                    if(nonClosedBracket==0 && operation==OR)
                    {
                        return evaluateExpression(table, expression.subString(expression.start, i)) || evaluateExpression(table, expression.subString(i+1, expression.end));
                    }
                    break;
                }
                case '^':
                {
                    if(nonClosedBracket==0 && operation==XOR)
                    {
                        return evaluateExpression(table, expression.subString(expression.start, i)) ^ evaluateExpression(table, expression.subString(i+1, expression.end));
                    }
                    break;
                }
                case '&':
                {
                    if(nonClosedBracket==0 && operation==AND)
                    {
                        return evaluateExpression(table, expression.subString(expression.start, i)) && evaluateExpression(table, expression.subString(i+1, expression.end));
                    }
                    break;
                }
                case '!':
                case '~':
                {
                    if(nonClosedBracket==0 && operation==NOT)
                    {
                        for(int k=i-1; k>=expression.start ;k--)
                            if(!isspace(expression[k]))
                            {
                                std::cout << "\nerror:[wrong NOT format]\nget help with -h\n";
                                exit(1);
                            }
                        
                            return !evaluateExpression(table, expression.subString(i+1, expression.end));
                    }
                    break;
                }
                
                
                case '\'':
                {
                    if(nonClosedBracket==0 && operation==NOT)
                    {
                        for(int k=i+1; k<expression.end ;k++)
                            if(!isspace(expression[k]))
                            {
                                std::cout << "\nerror:[wrong NOT format]\nget help with -h\n";
                                exit(1);
                            }
                        
                            return !evaluateExpression(table, expression.subString(expression.start, i));
                    }
                    break;
                }
                case '[':
                case '{':
                case '(':
                {
                    if(nonClosedBracket==0)
                    {
                        firstBracket=i;
                        if (majorBracket==1)
                        {
                            std::cout << "\nerror:[wrong bracket format]\nget help with -h\n";
                            exit(1);
                        }
                        majorBracket++;   
                    }
                    nonClosedBracket++;
                    break;
                }
                case ']':
                case '}':
                case ')':
                {
                    if(nonClosedBracket==1)
                    {
                        lastBracket=i;
                        
                    }
                    else if(nonClosedBracket==0)
                    {
                        std::cout << "\nerror:[wrong bracket format]\nget help with -h\n";
                        exit(1);
                    }
                    nonClosedBracket--;
                    break;
                }
                case '0':
                {
                    zero++;
                    break;
                }
                case '1':
                {
                    one++;
                    break;
                }
                default:
                {
                    break;
                }
                

            }
            //std::cout<<expression[i];
            
        }
        //std::cout<<"\nj: "<<operation<<std::endl;
    }

    if(nonClosedBracket!=0)
    {
        std::cout << "\nerror:[wrong bracket format]\nget help with -h\n";
        exit(1);
    }
    if(majorBracket==1)
    {
        return evaluateExpression(table, expression.subString(firstBracket+1, lastBracket));
    }
    
    SubString vars = expression.getVars();
    if(vars.length()==0 && (zero+one)==1)
    {
        if (zero == 1)
            return false;
        else
            return true;
    }
    if(vars.length()==1)
    {
        int i;
        //std::cout << "\n" << vars.array[0] << '\n';
        for(i=0; vars[0]!=table.character[i] ;i++);
        return table.boolian[i];
    }
    

    std::cout << "\nerror:[wrong format]\nget help with -h\n";
    exit(1);
}



void makeMinterms(std::vector< std::vector<boolresult> > &mintermList, const bool *resulttable, const unsigned int numberOfVariables)
{
    std::vector<boolresult> tempMinterm(numberOfVariables+1);
    int NofStates = 1 << numberOfVariables;
    for(int i = 0; i < NofStates; i++) {
        if(resulttable[i]) 
        {
            
            for(int j = 0; j < numberOfVariables; j++) 
                tempMinterm[j] = (boolresult)((i >> j) & 1);
            tempMinterm[numberOfVariables]=True;
            mintermList.push_back(tempMinterm);
        }
    }

}

void mergeMinterms(std::vector<std::vector< std::vector<boolresult>>> &groups, const bool *resulttable, const unsigned int numberOfVariables)
{
    std::vector<boolresult> tempMinterm(numberOfVariables+1);
    for(int i=0;i<numberOfVariables ; i++)
    {
        
        std::vector< std::vector<boolresult> > mintermList;
        for(int j=0;j<groups[i].size()-1;j++)
        {
            
            for(int k=j+1;k<groups[i].size();k++)
            {
                
                
                bool merge=false;
                int difference;

                for(int l=0;l<numberOfVariables;l++)
                {
                    
                    if(groups[i][j][l] != groups[i][k][l])
                    {
                        
                        if(groups[i][j][l] == DontCare || groups[i][k][l] == DontCare)
                        {
                            merge=false;
                            break;
                        }
                        if(merge)
                        {
                            merge=false;
                            break;
                        }
                        else
                        {
                            difference = l;
                            merge=true;
                        }   
                    }
                    

                }
                if(merge)
                {
                      tempMinterm=groups[i][j];
                      tempMinterm[difference]=DontCare;
                      mintermList.push_back(tempMinterm);
                      tempMinterm[numberOfVariables]=True;
                      groups[i][j][numberOfVariables]=False;
                      groups[i][k][numberOfVariables]=False;
                      
                }
            }
        }
        if (mintermList.size()==0)
            break;
        groups.push_back(mintermList);
    }
}

void printMinterms(std::vector<std::vector< std::vector<boolresult>>> &groups, const LogicTable& table, bool result0, flags flag)
{
    unsigned int numberOfVariable = groups[0][0].size()-1;
    bool printedAnything = false;
    int primecounter=0;
    for(auto& x : groups)
        for(auto& y : x)
            if(y[numberOfVariable] || flag==verb)
                primecounter++;
    for(auto& x : groups)
    {
        
        for(int j=0;j<x.size();j++)
        {
            
            
            bool printedOr = false;
            bool printedAnd=false;
            for(int i=0;i<numberOfVariable;i++)
            {
                if(x[j][numberOfVariable]==False && flag!=verb)
                    break;
                
                if(x[j][i]==True)
                {
                    if(printedAnd)
                    {
                        std::cout << " & " ;
                    }
                    std::cout << table.character[i] ;
                    
                    printedAnd=true;
                    printedOr=true;
                    printedAnything=true;
                    
                }
                else if(x[j][i]==False)
                {
                    if(printedAnd)
                    {
                        std::cout << " & " ;
                    }
                    std::cout << '~' << table.character[i] ;
                    
                    printedAnd=true;
                    printedOr=true;
                    printedAnything=true;
                    
                }
                
            }
            if(printedOr && primecounter > 1)
            {
                primecounter--;
                std::cout << "  |  " ;
            }
        }
    }
    if(printedAnything == false)
        std::cout << result0 ;
}
