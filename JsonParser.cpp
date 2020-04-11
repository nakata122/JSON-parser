#include <fstream>
#include <cstring>
#include <string>
#include <iostream>

#include "JSONParser.h"

JSON::JSON() : jsonFA(12, 128), stringFA(2, 128), root(jsonFA, stringFA)
{
    jsonFA.addTransition(1, 2, '{');
    jsonFA.addTransition(1, 1, ' ');
    jsonFA.addTransition(1, 1, '\n');

    jsonFA.addTransition(2, 6, '}');
    jsonFA.addTransition(2, 3, '\"');
    jsonFA.addTransition(2, 2, ' ');
    jsonFA.addTransition(2, 2, '\n');

    jsonFA.addTransition(3, 4, '\"');

    jsonFA.addTransition(4, 5, ':');
    jsonFA.addTransition(4, 4, ' ');
    jsonFA.addTransition(4, 4, '\n');

    jsonFA.addTransition(5, 8, '\"');
    jsonFA.addTransition(5, 9, '{');
    jsonFA.addTransition(5, 6, '}');
    jsonFA.addTransition(5, 2, ',');
    jsonFA.addTransition(5, 5, ' ');
    jsonFA.addTransition(5, 5, '\n');
    for(int i=0; i<=9; i++) jsonFA.addTransition(5, 10, i + '0');

    jsonFA.addTransition(8, 5, '\"');

    jsonFA.addTransition(9, 5, '}');

    stringFA.addTransition(0, 2, '\"');
    stringFA.addTransition(0, 1, '\\');

}

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