#include <iostream>
#include <cstring>
#include <sstream>

#include "Pair.h"
#include "JSONObj.h"
#include "PairFactory.h"

JSONObj::JSONObj(const std::string &_key, int _depth, bool _isArray) : Pair(_key), depth(_depth), isArray(_isArray)
{
    
}

JSONObj::JSONObj(const JSONObj &obj): Pair(obj.key)
{
    if(children.size() != 0) children.clear();
    for(int i=0; i<obj.children.size(); i++) children.push_back(obj.children[i]);
}

JSONObj::~JSONObj() 
{
    clear();
};

void JSONObj::clear() 
{
    for(int i=0; i<children.size(); i++) delete children[i];
    children.clear();
};


bool JSONObj::search(std::istream& iss)
{
    std::string _key;
    size_t counter = 0;
    while(FiniteAutomata.search(iss))
    {
        char ch;
        while(iss.peek() == ' ' || iss.peek() == '\n' || iss.peek() == '\t'  || iss.peek() == '\r') iss.get(); 

        if(isArray) 
        {
            _key = std::to_string(counter++);
        }

        if(_key.empty())
        {
            if(iss.get() != '"') 
            {
                std::cout << "String expected for key at " << iss.tellg() << std::endl;
                return false;
            }

            _key = PairFactory::parseString(iss);

            if(_key.empty()) 
            {
                std::cout << "Key cannot be empty" << std::endl;
                return false;
            }
        }
        else
        {
            Pair *pair = PairFactory::make(iss, _key, depth);
            if(pair != nullptr) children.push_back(pair);

            _key.clear();
        }
        
        while(iss.peek() == ' ' || iss.peek() == '\n' || iss.peek() == '\t' || iss.peek() == '\r') iss.get();
    }
    
    return FiniteAutomata.isValid();
}

std::ostream& JSONObj::print(std::ostream& stream) const
{ 
    if(isArray) stream << "[ \n";
    else stream << "{ \n";
    for(int i=0; i < children.size(); i++)
    {
        for(int j=0; j<depth + 1; j++) stream << "   ";

        if(!isArray) stream << "\"" << children[i]->key << "\" : ";
        stream << *children[i];

        if(i != children.size() - 1) stream << ", ";
        stream << std::endl;
    }
    for(int j=0; j<depth; j++) stream << "   ";
    if(isArray) stream << "] \n";
    else stream << "}";
    return stream;
}

std::string JSONObj::splitPath(const std::string &path)
{
    if(path.empty()) return "";
    size_t endIndex = path.find('.',0);
    if(endIndex == std::string::npos) endIndex = path.size();

    return path.substr(0, endIndex);
}

int JSONObj::find(const std::string &_key) const
{
    for(int i = 0; i < children.size(); i++)
    {
        if(children[i]->key == _key) return i;
    }
    return -1;
}

void JSONObj::printAll(const std::string &_key) const
{
    if(_key == key) std::cout << *this << std::endl;

    for(int i=0; i < children.size(); i++)
    {
        children[i]->printAll(_key);
    }
}

bool JSONObj::create(const std::string &path, Pair *obj)
{
    std::string part = splitPath(path);
    int index = find(part);

    if(index != -1)
    {
        if(path.size() > part.size() + 1)
        {
            return children[index]->create(path.substr(part.size() + 1), obj);
        }
        else return false;
    }
    else
    {
        if(path.size() > part.size() + 1)
        {
            JSONObj *temp = new JSONObj(part, depth + 1);
            children.push_back(temp);
            return temp->create(path.substr(part.size() + 1), obj);
        }
        else 
        {
            children.push_back(obj);
            return true;
        }
    }
    return false;
}

bool JSONObj::erase(const std::string &path)
{
    std::string part = splitPath(path);
    int index = find(part);

    if(index != -1)
    {
        if(path.size() > part.size() + 1)
        {
            return children[index]->erase(path.substr(part.size() + 1));
        }
        else
        {
            delete children[index];

            children.erase(children.begin() + index);
            return true;
        }
    }
    
    return false;
}

Pair *JSONObj::cutContent(const std::string &path)
{
    std::string part = splitPath(path);
    int index = find(part);

    if(index != -1)
    {
        if(path.size() > part.size() + 1)
        {
            children[index]->cutContent(path.substr(part.size() + 1));
        }
        else
        {
            Pair *result = children[index];
            children.erase(children.begin() + index);
            return result;
        }
    }
    
    return nullptr;
}

bool JSONObj::edit(const std::string &path, Pair *obj) 
{
    std::string part = splitPath(path);
    int index = find(part);

    if(index != -1)
    {
        if(path.size() > part.size() + 1)
        {
            return children[index]->edit(path.substr(part.size() + 1), obj);
        }
        else
        {
            delete children[index];
            children[index] = obj;
            return true;
        }
    }

    return false;
}

void JSONObj::save(const std::string &path, std::ostream& stream)
{
    if(path.empty())
    {
        stream << *this << std::endl;
        return;
    } 
    
    std::string part = splitPath(path);
    int index = find(part);

    if(index != -1)
    {
        if(path.size() > part.size() + 1)
        {
            return children[index]->save(path.substr(part.size() + 1), stream);
        }
        else
        {
            stream << "{\n \"" << children[index]->key << "\" : " << *children[index] << "\n}";
        }
    }
}

std::ostream& operator << (std::ostream& stream, JSONObj& node)
{
    return node.print(stream);
}