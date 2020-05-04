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

bool NodePair::findNext(const std::string &key, std::vector<int> &path)
{
    return data->findNext(key, path);
}

Pair *NodePair::get(std::vector<int> &path)
{
    return data->get(path);
}