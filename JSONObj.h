#ifndef _JSONObj_H
#define _JSONObj_H

#include <vector>
#include <string>

struct Pair
{
    std::string key, value;

    Pair(std::string _key, std::string _value) : key(_key), value(_value) {}
};

class JSONObj
{
private:
    std::vector< Pair* > children;

public:
    void search(std::istream& iss);
    void print();
};

#endif