#ifndef _JSON_H
#define _JSON_H

#include "JSONObj.h"

class JSON
{
private:
    bool valid = true;
    JSONObj root;

public:
    JSON();
    void read(const char *path);
    void close();
    void parse(std::ifstream& iss);
    bool validate();
    void print();
    void search(std::string &key);
    void edit(std::string &path, std::string &value);
    void erase(std::string &path);
    void help();
};

#endif