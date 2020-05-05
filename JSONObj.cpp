#include <iostream>
#include <cstring>
#include <sstream>

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

std::string JSONObj::parseString(std::istream& iss)
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

Pair *JSONObj::parseValue(std::istream &iss, const std::string &key)
{
    double doubleNum;
    char ch = iss.peek();

    if (ch >= '0' && ch <= '9') //Double
    {
        iss >> doubleNum;
        return new TypedPair<double>(key, doubleNum);
    }
    else if(ch == '"') //String
    {
        iss.get(); //Ignore "

        std::string value = parseString(iss);

        return new TypedPair<std::string>(key, value);
    }
    else if(ch == '{') //Object
    {
        JSONObj *value = new JSONObj(depth + 1);
        value->search(iss);
        return new NodePair(key, value);
    }
    else if(ch == '[') //Array
    {
        //TODO
    }
    else if(ch == 't')
    {
        char value[5];
        iss.getline(value, 5);
        std::cout << value << std::endl;
        if(strcmp(value, "true") == 0) 
            return new TypedPair<bool>(key, true);
    }
    else if(ch == 'f')
    {
        char value[6];
        iss.getline(value, 6);
        if(strcmp(value, "false") == 0) 
            return new TypedPair<bool>(key, false);
    }

    return nullptr;
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

            key = parseString(iss);

            if(key.empty()) 
            {
                std::cout << "Key cannot be empty" << std::endl;
                return false;
            }
        }
        else
        {
            Pair *pair = parseValue(iss, key);
            if(pair != nullptr) children.push_back(pair);

            key.clear();
        }
        
        while(iss.peek() == ' ' || iss.peek() == '\n' || iss.peek() == '\t') iss.get();
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

        while(children[i]->getObject() != nullptr && children[i]->getObject()->findNext(key, path))
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
    else if(children[path[depth]]->getObject() != nullptr)
        return children[path[depth]]->getObject()->get(path);
    else return nullptr;
}

JSONObj *JSONObj::getObj(std::vector<int> &path) 
{
    if(path.size() - 1 == depth) 
        return this;
    else if(children[path[depth]]->getObject() != nullptr)
        return children[path[depth]]->getObject()->getObj(path);
    else return nullptr;
}

bool JSONObj::find(const std::string &key, std::vector<int> &path)
{
    if(key.empty()) return true;

    std::stringstream iss(key);
    std::string part;
    getline(iss, part, '.');

    for(int i=0; i < children.size(); i++)
    {
        if(children[i]->key == part) 
        {
            path.push_back(i);
            if(children[i]->getObject() != nullptr && key.size() > part.size() + 1)
            {
                return children[i]->getObject()->find(key.substr(part.size() + 1), path);
            }
            else return true;
        }
    }
    
    return false;
}

bool JSONObj::erase(const int index)
{
    if(index >= 0 && index < children.size())
    {
        delete children[index];

        children.erase(children.begin() + index);
        return true;
    }
    
    return false;
}

bool JSONObj::edit(Pair *obj, int index) 
{
    std::cout << *obj << std::endl;
    if(index >= 0 && index < children.size())
    {
        delete children[index];
        children[index] = obj;
        return true;
    }

    return false;
}

std::ostream& operator << (std::ostream& stream, JSONObj& node)
{
    return node.print(stream);
}