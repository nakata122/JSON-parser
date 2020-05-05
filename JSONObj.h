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

    std::string parseString(std::istream& iss);
public:
    JSONObj(int _depth = 0);
    JSONObj(const JSONObj &obj);
    ~JSONObj();
    bool search(std::istream &iss);
    Pair *parseValue(std::istream &iss, const std::string &key);
    std::ostream& print(std::ostream& stream) const;
    bool findNext(const std::string &key, std::vector<int> &path);
    bool find(const std::string &key, std::vector<int> &path);
    bool erase(const int index);
    bool edit(Pair *obj, int index);

    Pair *get(std::vector<int> &path); //Get pointer to the child
    JSONObj *getObj(std::vector<int> &path); //Get pointer to the object
    

    friend std::ostream& operator << (std::ostream& stream, JSONObj& node);
};

#endif