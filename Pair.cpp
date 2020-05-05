#include <iostream>

#include "JSONObj.h"
#include "Pair.h"


std::ostream& NodePair::print(std::ostream& stream) const 
{ 
    stream << key << " : "  << *data; 
    return stream;
}

NodePair::~NodePair()
{
    delete data;
}


JSONObj *NodePair::getObject()
{
    return data;
}