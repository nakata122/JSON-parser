#ifndef _JSONObj_H
#define _JSONObj_H

#include <vector>
#include <string>

#include "JsonFA.h"
#include "Pair.h"

///Represents a class containing a group of Pair and manipulating them
class JSONObj: public Pair
{
private:
    std::vector< Pair* > children; ///<Holds all childred of the group
    JsonFA FiniteAutomata; ///<Used for parsing the file
    int depth; 
    bool isArray;

    std::string splitPath(const std::string &path); ///<Helper function to split a path into components
public:
    JSONObj(const std::string &_key, int _depth = 0, bool _isArray = false); ///<Initialize object
    JSONObj(const JSONObj &obj);
    ~JSONObj();
    void clear(); ///<Clear memory
    bool search(std::istream &iss); ///<Read data from a stream and parse it
    std::ostream& print(std::ostream& stream) const; ///<Prints out data (human readable)
    int find(const std::string &_key) const; ///<Find a direct child
    virtual void printAll(const std::string &_key) const; ///<Find all occurances of the key and prints them on the console
    virtual bool edit(const std::string &path, Pair *obj); ///<Changes the value of a relative or direct child
    virtual bool erase(const std::string &path); ///<Clears memory of a relative or direct child
    virtual bool create(const std::string &path, Pair *obj); ///<Creates a new path if the path doesn't exist and places a new object there
    virtual Pair *cutContent(const std::string &path); ///<Removes a relative or direct child from the group. The user takes care of it's memory after
    virtual void save(const std::string &path, std::ostream& stream); ///<Outputs on a stream based on a relative path to a child


    friend std::ostream& operator << (std::ostream& stream, JSONObj& node); ///<Prints on stream
};

#endif