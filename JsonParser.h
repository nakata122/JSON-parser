#ifndef _JSON_H
#define _JSON_H

#include <string>
#include "JSONObj.h"

///Represents a class used to work with a JSON files
class JSON
{
private:
    bool valid = false;
    std::string fileName;
    JSONObj root;

public:
    JSON();
    void read(const std::string &path); ///<Open file and load it into memory
    void close(); ///<Release file memory
    bool validate(); ///<Prints out information about the current state of the file reader
    void print(); ///<Prints the everything inside root
    void search(std::string &key); ///<Prints all occurances of objects with the same key
    void edit(std::string &path, std::string &value); ///<Changes the value of an object with a relative path
    void create(std::string &path, std::string &value); ///<Creates a new path if it doesn't exist and puts a new object
    void move(std::string &from, std::string &to); ///<Moves from one path to another path deleting the first one
    void erase(std::string &path); ///<Delete all objects after that path
    void save(std::string &path); ///<Saves currently opened file based on a relative path
    void saveAs(std::string &fileLocation, std::string &path); ///<Saves currently opened file in a new location based on a relative path
    void help(); ///<Prints additional help
};

#endif