#ifndef _Pair_H
#define _Pair_H

#include <string>
#include <vector>

class JSONObj;
struct Pair
{
    std::string key;

    Pair(const std::string &_key) : key(_key) {}
    virtual std::ostream& print(std::ostream& stream) const = 0;
    virtual JSONObj *getObject() = 0;

    
    friend std::ostream& operator << (std::ostream& stream, const Pair& pair)
    {
        return pair.print(stream);
    }
};

template< typename T >
class TypedPair : public Pair
{
private:
    T data;
public:
    TypedPair (const std::string &key, const T &_data) : Pair(key), data(_data) {};
    virtual std::ostream& print(std::ostream& stream) const { return stream << std::boolalpha << key << " : " << data; } //boolalpha is to print bool as true or false
    virtual JSONObj *getObject() { return nullptr; }
};

class NodePair : public Pair
{
private:
    JSONObj *data;
public:
    NodePair (const std::string &key, JSONObj *_data) : Pair(key), data(_data) {};
    ~NodePair();
    virtual std::ostream& print(std::ostream& stream) const;
    virtual JSONObj *getObject();
};
#endif