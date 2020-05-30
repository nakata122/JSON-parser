#ifndef _JSONFA_H
#define _JSONFA_H

#include <fstream>

///Represents a finite automata class used for parsing the JSON file format more easily
class JsonFA
{
private:
    static short table[9][128]; ///<Table of transitions. Initialized only once.
    bool valid = true;
    int state = 1, finalState = 6;
    int line = 0;

public:
    JsonFA();
    static void init(); ///<Initialized the finite automata
    void reset(int start); ///<Start from the first node
    bool search(std::istream& iss); ///<Move though the transition table until an input is needed or an error occurs
    bool isValid(); ///<Returns the state of the current instance of the class
};

#endif