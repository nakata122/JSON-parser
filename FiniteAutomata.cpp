#include <fstream>
#include <iostream>

#include "FiniteAutomata.h"

FiniteAutomata::FiniteAutomata(const int _col, const int _row): col(_col), row(_row) 
{
    table = new int*[col];
    for(int i=0; i < col; i++)
    {
        table[i] = new int[row];
        for(int j=0; j < row; j++)
        {
            table[i][j] = 0;
        }
    }
}

FiniteAutomata::~FiniteAutomata()
{
    for(int i=0; i < col; i++)
    {
        delete[] table[i];
    }
    delete[] table;
}

void FiniteAutomata::reset(int start)
{
    state = start;
}

void FiniteAutomata::addTransition(int from, int to, char symbol)
{
    table[from][symbol] = to;
}

int FiniteAutomata::search(char ch)
{
    state = table[state][ch];
    return state;
}

void FiniteAutomata::search(int &state, char ch)
{
    state = table[state][ch];
}

void FiniteAutomata::search(std::istream& iss, std::string &data)
{
    char ch;
    while(state != endState && (iss >> ch))
    {
        state = table[state][ch];

        if(state != endState)
            data.push_back(ch);
    }
    state = 0;
}