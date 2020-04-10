#include <iostream>

#include "JSONObj.h"

void JSONObj::search(std::istream& iss)
{

}

std::ostream& JSONObj::print(std::ostream& stream) 
{ 
    stream << "{ \n";
    for(int i=0; i < children.size(); i++)
    {
        stream << *children[i] << std::endl;
    }
    stream << "} \n";
    return stream;
}