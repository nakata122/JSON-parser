#ifndef _Pair_H
#define _Pair_H

#include <string>
#include <vector>

struct Pair
{
    std::string key;

    Pair(const std::string &_key) : key(_key) {}
    virtual std::ostream& print(std::ostream& stream) const = 0;
    virtual bool findNext(const std::string &key, std::vector<int> &path) = 0;
    virtual Pair *get(std::vector<int> &path) = 0;

    
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
    virtual std::ostream& print(std::ostream& stream) const { return stream << key << " : " << data; }
    virtual bool findNext(const std::string &key, std::vector<int> &path) { return false; }
    virtual Pair *get(std::vector<int> &path) { return nullptr; }
};

class JSONObj;
class NodePair : public Pair
{
private:
    JSONObj *data;
public:
    NodePair (const std::string &key, JSONObj *_data) : Pair(key), data(_data) {};
    ~NodePair();
    virtual std::ostream& print(std::ostream& stream) const;
    virtual bool findNext(const std::string &key, std::vector<int> &path);
    virtual Pair *get(std::vector<int> &path);
};
#endif