#include <fstream>
#include <cstring>
#include <string>
#include <iostream>

#include "JsonParser.h"

void JSON::read(const char *path)
{
    std::ifstream file;
    file.open(path, std::ios::in);
    if (file.is_open())
    {
        root.search(file);
        
        file.close();
    }
    else
    {
        std::cout << "File not found" << std::endl;
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