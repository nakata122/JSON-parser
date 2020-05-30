#include <cstring>
#include <fstream>

#include "PairFactory.h"
#include "JSONObj.h"


std::string PairFactory::parseString(std::istream& iss)
{
    std::string value;

    while(iss.peek() != '"')
    {
        char ch;
        iss.get(ch);
        value += ch;
        if(ch == '\\')
        {
            iss.get(ch);
            value += ch;
        }
    }

    iss.get();

    return value;
}

Pair *PairFactory::make(std::istream &iss, const std::string &_key, const int depth)
{
    double doubleNum;
    char ch = iss.peek();

    if (ch >= '0' && ch <= '9') //Double
    {
        iss >> doubleNum;
        return new TypedPair<double>(_key, doubleNum);
    }
    else if(ch == '"') //String
    {
        iss.get(); //Ignore "

        std::string value = parseString(iss);

        return new TypedPair<std::string>(_key, value);
    }
    else if(ch == '{') //Object
    {
        JSONObj *value = new JSONObj(_key, depth + 1);
        value->search(iss);
        return value;
    }
    else if(ch == '[') //Array
    {
        JSONObj *value = new JSONObj(_key, depth + 1, true);
        value->search(iss);
        return value;
    }
    else if(ch == 't')
    {
        char value[5];
        iss.getline(value, 5);
        if(strcmp(value, "true") == 0) 
            return new TypedPair<bool>(_key, true);
    }
    else if(ch == 'f')
    {
        char value[6];
        iss.getline(value, 6);
        if(strcmp(value, "false") == 0) 
            return new TypedPair<bool>(_key, false);
    }

    return nullptr;
}