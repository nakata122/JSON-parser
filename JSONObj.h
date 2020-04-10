#ifndef _JSONObj_H
#define _JSONObj_H

#include <vector>
#include <string>

#include "Pair.h"

class JSONObj
{
private:
    std::vector< Pair* > children;

public:
    void search(std::istream& iss);
    std::ostream& print(std::ostream& stream);

    friend std::ostream& operator << (std::ostream& stream, JSONObj& node)
    {
        return node.print(stream);
    }
};

#endif