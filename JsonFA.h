#ifndef _JSONFA_H
#define _JSONFA_H

#include <fstream>

class JsonFA
{
private:
    static short table[7][128];
    bool valid = true;
    int state = 1, finalState = 6;
    int line = 0;

public:
    JsonFA();
    static void init();
    void reset(int start);
    bool search(std::istream& iss);
    
};

#endif