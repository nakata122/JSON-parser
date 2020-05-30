#include <iostream>
#include <string>

#include "JsonParser.h"

int main()
{
    std::string command;
    JSON file;

    while(std::cin >> command && command != "exit")
    {
        if(command.compare("open") == 0)
        {
            if(file.validate()) file.close();
            std::string path;
            std::cin >> path;

            file.read(path);
        }
        else if(command.compare("validate") == 0)
        {
            if(file.validate()) std::cout << "The opened json file is valid \n";
            else std::cerr << "The json file is invalid" << std::endl;
        }
        else if(command.compare("close") == 0 && file.validate())
        {
            file.close();
        }
        else if(command.compare("print") == 0 && file.validate())
        {
            file.print();
        }
        else if(command.compare("search") == 0 && file.validate())
        {
            std::string key;
            std::cin >> key;

            file.search(key);
        }
        else if(command.compare("set") == 0 && file.validate())
        {
            std::string path, value;
            std::cin >> path;
            getline(std::cin, value);
            
            file.edit(path, value);
        }
        else if(command.compare("move") == 0 && file.validate())
        {
            std::string from, to;
            std::cin >> from >> to;
            
            file.move(from, to);
        }
        else if(command.compare("create") == 0 && file.validate())
        {
            std::string path, value;
            std::cin >> path;
            getline(std::cin, value);
            
            file.create(path, value);
        }
        else if(command.compare("delete") == 0 && file.validate())
        {
            std::string path;
            std::cin >> path;

            file.erase(path);
        }
        else if(command.compare("save") == 0 && file.validate())
        {
            std::string path;
            std::cin.ignore();
            getline(std::cin, path);

            file.save(path);
        }
        else if(command.compare("saveas") == 0 && file.validate())
        {
            std::string path, fileLocation;
            std::cin >> fileLocation;
            std::cin.ignore();
            getline(std::cin, path);

            file.saveAs(fileLocation, path);
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
        else
        {
            std::cout << "Unknown command or invalid file \n";
        }
        
    }

    std::cout << "Exiting the program" << std::endl;

    return 0;
}