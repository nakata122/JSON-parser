#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <iostream>

#include "Pair.h"
#include "JsonFA.h"
#include "JSONParser.h"

JSON::JSON() : root(0) 
{
    JsonFA::init();
}

void JSON::read(const char *path)
{
    std::ifstream file;
    file.open(path, std::ios::in);
    if (file.is_open())
    {
        valid = root.search(file);
        
        file.close();
    }
    else
    {
        std::cout << "File not found" << std::endl;
    }
}

void JSON::search(std::string &key)
{

    std::vector<int> path;
    while(root.findNext(key, path))
    {
        std::cout << *root.get(path) << std::endl;
        path.back()++;
    }
}

void JSON::edit(std::string &path, std::string &value)
{
    Pair *obj;

    std::vector<int> rawPath;
    
    if(root.find(path, rawPath))
    {
        std::stringstream iss(value);
        iss >> std::ws;
        obj = root.parseValue(iss, root.get(rawPath)->key);
        int lastIndex = rawPath.back();

        JSONObj *parent = root.getObj(rawPath);

        if(parent != nullptr)
        {
            parent->edit(obj, lastIndex);
        }
    }
    else
    {
        std::cout << "Path not found" << std::endl;
    }
}

void JSON::erase(std::string &path)
{

    std::vector<int> rawPath;
    while(root.find(path, rawPath))
    {
        JSONObj *parent = root.getObj(rawPath);

        if(parent != nullptr)
        {
            parent->erase(rawPath.back());
        }
    }
}

void JSON::print()
{
    std::cout << root;
}

void JSON::close()
{
    
}

bool JSON::validate() 
{
    return true;
}

void JSON::help()
{
    std::cout << "validate	            checks if file is JSON \n"
              << "print			        prints JSON \n"
              << "search <key>      	returns a list of data associated with the key \n"
              << "set <key> <string>	changes value of key in the object \n"
              << "create <path> <string>creates a new key value pair \n" 
              << "delete <path>			deletes the object \n"
              << "move <from> <to>		moves object \n";
}