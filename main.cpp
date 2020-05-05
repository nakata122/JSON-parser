#include <iostream>
#include <string>

#include "JsonParser.h"

int main()
{
    std::string command;
    JSON file;

    while(command != "exit")
    {
        std::cin >> command;
        if(command.compare("open") == 0)
        {
            char path[256];
            std::cin.ignore();
            std::cin.getline(path, 256);
            
            file.read(path);
        }
        else if(command.compare("close") == 0)
        {
            file.close();
        }
        else if(command.compare("print") == 0)
        {
            file.print();
        }
        else if(command.compare("search") == 0)
        {
            std::string key;
            std::cin >> key;

            file.search(key);
        }
        else if(command.compare("set") == 0)
        {
            std::string path, value;
            std::cin >> path;
            getline(std::cin, value);
            
            file.edit(path, value);
        }
        else if(command.compare("delete") == 0)
        {
            std::string path;
            std::cin >> path;

            file.erase(path);
        }
        else if(command.compare("save") == 0)
        {
            
        }
        else if(command.compare("saveas") == 0)
        {

        }
        else if(command.compare("help") == 0)
        {
            std::cout << "The following commands are supported: \n"
                      << "open <file>	opens <file> \n"
                      << "close			closes currently opened file \n"
                      << "save			saves the currently open file \n"
                      << "saveas <file>	saves the currently open file in <file> \n"
                      << "help			prints this information \n" 
                      << "exit			exists the program \n";
            
            file.help();
        }
    }

    std::cout << "Exiting the program" << std::endl;

    return 0;
}