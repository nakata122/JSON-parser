#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Pair.h"
#include "JsonFA.h"
#include "JSONParser.h"
#include "PairFactory.h"

JSON::JSON() : root("", 0) 
{
    JsonFA::init();
}

void JSON::read(const std::string &path)
{
    std::ifstream file;
    file.open(path, std::ios::in);
    if (file.is_open())
    {
        valid = root.search(file);
        fileName = path;
        
        file.close();

        std::cout << "File successfully opened \n";
    }
    else
    {
        std::cerr << "File not found \n";
    }
}

void JSON::search(std::string &key)
{
    root.printAll(key);
}

void JSON::edit(std::string &path, std::string &value)
{
    int end = path.find_last_of('.'), depth = std::count(path.begin(), path.end(), '.') + 1;
    if(end == std::string::npos) end = -1;

    std::stringstream iss(value);
    iss >> std::ws;
    Pair *obj = PairFactory::make(iss, path.substr(end + 1), depth);

    if(obj != nullptr && root.edit(path, obj))
    {
        std::cout << "Successfully set \n";
    }
    else
    {
        std::cerr << "Path not found \n";
    }
}

void JSON::create(std::string &path, std::string &value)
{
    int end = path.find_last_of('.'), depth = std::count(path.begin(), path.end(), '.') + 1;
    if(end == std::string::npos) end = -1;

    std::stringstream iss(value);
    iss >> std::ws;
    Pair *obj = PairFactory::make(iss, path.substr(end + 1), depth);

    if(obj != nullptr && root.create(path, obj))
    {
        std::cout << "Successfully created \n";
    }
    else
    {
        std::cerr << "Path already exists \n";
    }
}

void JSON::erase(std::string &path)
{
    if(root.erase(path))
    {
        std::cout << "Successfully erased \n";
    }
    else
    {
        std::cerr << "Path not found \n";
    }
}

void JSON::move(std::string &from, std::string &to)
{
    int end = to.find_last_of('.');
    if(end == std::string::npos) end = -1;

    Pair *fromPair = root.cutContent(from);
    fromPair->key = to.substr(end + 1);

    if(fromPair != nullptr && root.edit(to, fromPair))
    {
        std::cout << "Successfully moved \n";
    }
    else
    {
        std::cerr << "Wrong path \n";
    }
}

void JSON::print()
{
    std::cout << root;
}

void JSON::close()
{
    root.clear();
    valid = false;
}

bool JSON::validate() 
{
    return valid;
}

void JSON::save(std::string &path)
{
    std::ofstream file;
    file.open(fileName);

    if (file.is_open())
    {
        root.save(path, file);
        
        file.close();

        std::cout << "File successfully saved \n";
    }
    else
    {
        std::cerr << "File could not be saved \n";
    }
}

void JSON::saveAs(std::string &fileLocation, std::string &path)
{
    std::ofstream file;
    file.open(fileLocation);

    if (file.is_open())
    {
        root.save(path, file);
        
        file.close();

        std::cout << "File successfully saved \n";
    }
    else
    {
        std::cerr << "File could not be saved \n";
    }
}

void JSON::help()
{
    std::cout << "validate              checks if file is JSON \n"
              << "print                 prints JSON \n"
              << "search <key>          returns a list of data associated with the key \n"
              << "set <key> <string>    changes value of key in the object \n"
              << "create <path> <string>creates a new key value pair \n" 
              << "delete <path>         deletes the object \n"
              << "move <from> <to>      moves object \n";
}