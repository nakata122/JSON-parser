#ifndef _FA_H
#define _FA_H

class FiniteAutomata
{
private:
    int **table;
    int col, row;
    int state, startState = 0, endState = 2;

public:
    FiniteAutomata(const int _col, const int _row);
    ~FiniteAutomata();
    void addTransition(int from, int to, char symbol);
    void reset(int start);
    int search(char ch);
    void search(int &state, char ch);
    void search(std::istream& iss, std::string &data);

};

#endif