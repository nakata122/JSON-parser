#include <iostream>

#include "JSONObj.h"

JSONObj::JSONObj(FiniteAutomata &_jsonFA, FiniteAutomata &_stringFA) : jsonFA(_jsonFA), stringFA(_stringFA)
{

}

JSONObj::JSONObj(const JSONObj &obj): jsonFA(obj.jsonFA), stringFA(obj.stringFA) 
{
    if(children.size() != 0) children.clear();
    for(int i=0; i<obj.children.size(); i++) children.push_back(obj.children[i]);
}

JSONObj::~JSONObj() 
{
    for(int i=0; i<children.size(); i++) delete children[i];
};

void JSONObj::search(std::istream& iss)
{
    int state = 1;
    char ch;
    std::string key;
    while(state != 6 && (iss >> ch))
    {
        jsonFA.search(state, ch);

        if(state == 0)
        {
            //std::cout << "ERROR: " << std::endl;
        }
        else if(state == 3) 
        {
            stringFA.reset(0);
            stringFA.search(iss, key);
            jsonFA.search(state, '\"');
        }
        else if(state == 8)
        {
            std::string *temp = new std::string();
            stringFA.search(iss, *temp);

            children.push_back( new TypedPair<std::string> (key, temp));
            jsonFA.search(state, '\"');
        }
        else if(state == 9)
        {
            JSONObj *obj = new JSONObj(jsonFA, stringFA);
            children.push_back( new TypedPair<JSONObj> (key, obj));
            key = "";

            iss.putback(ch);
            obj->search(iss);

            jsonFA.search(state, '}');
        }
        else if(state == 10)
        {
            double *temp = new double();
            iss.putback(ch);
            iss >> *temp;
            children.push_back( new TypedPair<double> (key, temp));
            key = "";

            state = 5;
        }
    }
}

std::ostream& JSONObj::print(std::ostream& stream) 
{ 
    stream << "{ \n";
    for(int i=0; i < children.size(); i++)
    {
        for(int j=0; j<depth; j++) stream << "   ";
        stream << *children[i] << std::endl;
    }
    stream << "} \n";
    return stream;
}