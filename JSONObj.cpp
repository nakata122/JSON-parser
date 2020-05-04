#include <iostream>
#include <cstring>

#include "Pair.h"
#include "JSONObj.h"

JSONObj::JSONObj(int _depth) : depth(_depth)
{

}

JSONObj::JSONObj(const JSONObj &obj)
{
    if(children.size() != 0) children.clear();
    for(int i=0; i<obj.children.size(); i++) children.push_back(obj.children[i]);
}

JSONObj::~JSONObj() 
{
    for(int i=0; i<children.size(); i++) delete children[i];
};

std::string JSONObj::getString(std::istream& iss)
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

bool JSONObj::search(std::istream& iss)
{
    std::string key;
    while(FiniteAutomata.search(iss))
    {
        char ch;
        while(iss.peek() == ' ' || iss.peek() == '\n' || iss.peek() == '\t') iss.get(); 

        if(key.empty())
        {
            if(iss.get() != '"') 
            {
                std::cout << "String expected for key at " << iss.tellg() << std::endl;
                return false;
            }

            key = getString(iss);

            if(key.empty()) 
            {
                std::cout << "Key cannot be empty" << std::endl;
                return false;
            }
        }
        else
        {
            double doubleNum;
            ch = iss.peek();

            if (ch >= '0' && ch <= '9') //Double
            {
                iss >> doubleNum;
                children.push_back(new TypedPair<double>(key, doubleNum));
            }
            else if(ch == '"') //String
            {
                iss.get(); //Ignore "

                std::string value = getString(iss);

                children.push_back(new TypedPair<std::string>(key, value));
            }
            else if(ch == '{') //Object
            {
                JSONObj *value = new JSONObj(depth + 1);
                value->search(iss);
                children.push_back(new NodePair(key, value));
            }
            else if(ch == '[') //Array
            {
                //TODO
            }
            else if(ch == 't')
            {
                char value[4];
                iss.getline(value, 4);
                if(strcmp(value, "true") == 0) 
                    children.push_back(new TypedPair<bool>(key, true));
            }
            else if(ch == 'f')
            {
                char value[5];
                iss.getline(value, 5);
                if(strcmp(value, "false") == 0) 
                    children.push_back(new TypedPair<bool>(key, false));
            }
            
            key.clear();
        }
        
        while(iss.peek() == ' ' || iss.peek() == '\n' || iss.peek() == '\t') iss.get(); 
        //std::cout << (char)iss.peek() << std::endl; 
    }
    
    return true;
}

std::ostream& JSONObj::print(std::ostream& stream) const
{ 
    stream << "{ \n";
    for(int i=0; i < children.size(); i++)
    {
        for(int j=0; j<depth + 1; j++) stream << "   ";
        stream << *children[i] << std::endl;
    }
    for(int j=0; j<depth; j++) stream << "   ";
    stream << "} \n";
    return stream;
}

bool JSONObj::findNext(const std::string &key, std::vector<int> &path)
{ 
    if(path.size() <= depth) path.push_back(0);

    for(int i=path[depth]; i < children.size(); i++)
    {
        if(children[i]->key == key)
        {
            path[depth] = i;
            return true;
        }

        while(children[i]->findNext(key, path))
        {
            path[depth] = i;
            return true;
        }
    }
    path[depth] = 0;
    return false;
}

Pair *JSONObj::get(std::vector<int> &path) 
{
    if(path.size() - 1 == depth) 
        return children[path.back()];
    else 
        return children[path[depth]]->get(path);
}

std::ostream& operator << (std::ostream& stream, JSONObj& node)
{
    return node.print(stream);
}