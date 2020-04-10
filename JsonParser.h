#ifndef _JSON_H
#define _JSON_H

#include "JSONObj.h"

class JSON
{
private:
    JSONObj root;

public:
    void read(const char *path);
    void close();
    void parse(std::ifstream& iss);
    bool validate();
    void print();
    std::string search(std::string key);
    void help();
};

#endif