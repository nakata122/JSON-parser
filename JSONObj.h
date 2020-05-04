#ifndef _JSONObj_H
#define _JSONObj_H

#include <vector>
#include <string>

#include "JsonFA.h"

class Pair;
class JSONObj
{
private:
    std::vector< Pair* > children;
    JsonFA FiniteAutomata;
    int depth;

    std::string getString(std::istream& iss);
public:
    JSONObj(int _depth = 0);
    JSONObj(const JSONObj &obj);
    ~JSONObj();
    bool search(std::istream& iss);
    std::ostream& print(std::ostream& stream) const;
    bool findNext(const std::string &key, std::vector<int> &path);

    Pair *get(std::vector<int> &path);
    

    friend std::ostream& operator << (std::ostream& stream, JSONObj& node);
};

#endif