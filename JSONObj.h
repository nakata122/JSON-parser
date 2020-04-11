#ifndef _JSONObj_H
#define _JSONObj_H

#include <vector>
#include <string>

#include "FiniteAutomata.h"
#include "Pair.h"

class JSONObj
{
private:
    std::vector< Pair* > children;
    FiniteAutomata &jsonFA, &stringFA;
    int depth = 0;

public:
    JSONObj(FiniteAutomata &jsonFA, FiniteAutomata &stringFA);
    JSONObj(const JSONObj &obj);
    ~JSONObj();
    void search(std::istream& iss);
    std::ostream& print(std::ostream& stream);

    friend std::ostream& operator << (std::ostream& stream, JSONObj& node)
    {
        return node.print(stream);
    }
};

#endif