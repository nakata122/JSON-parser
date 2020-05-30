#ifndef _PAIRFACTORY_H
#define _PAIRFACTORY_H

#include <string>
#include "Pair.h"

///<Represents a factory class to create Pair
class PairFactory
{
public:
    static std::string parseString(std::istream& iss); ///<Helper function with logic to parse a string
    static Pair *make(std::istream &iss, const std::string &_key, const int depth = 1); ///<Creates a new pointer to Pair. Does not take care of memory after
}; 

#endif