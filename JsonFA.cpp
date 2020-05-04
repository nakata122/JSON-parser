#include <iostream>
#include "JsonFA.h"

short JsonFA::table[7][128] = {0};

JsonFA::JsonFA()
{
    
}

void JsonFA::init()
{
    table[1]['{'] =  2;
    table[1][' '] =  1;
    table[1]['\n'] =  1;

    table[2][0] =  3;
    table[2]['}'] =  6;

    table[3][':'] =  4;
    
    table[4][0] =  5;

    table[5][','] =  2;
    table[5]['}'] =  6;
}

bool JsonFA::search(std::istream& iss)
{
    char ch;
    while(state != 0 && state != finalState && iss >> ch)
    {
        
        state = table[state][ch];
        if(state == 0) 
        {
            valid = false;
            std::cout << "Undexpected symbol at " << iss.tellg() << std::endl;
            return false;
        }
        if(table[state][0] != 0) 
        {
            state = table[state][0];
            return true;
        }
    }
    return false;
}