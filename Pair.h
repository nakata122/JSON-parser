#ifndef _Pair_H
#define _Pair_H

#include <string>

class Pair
{
protected:
    std::string key;
public:
    Pair(std::string _key) : key(_key) {}
    virtual ~Pair() {}
    virtual std::ostream& print(std::ostream& stream) const { return stream << key << ": {}";}

    
    friend std::ostream& operator << (std::ostream& stream, const Pair& pair)
    {
        return pair.print(stream);
    }
};

template< typename T >
class TypedPair : public Pair
{
private:
    T *data;
public:
    TypedPair (const std::string key, T *_data) : Pair(key), data(_data) {} 
    ~TypedPair() { delete data; }
    virtual std::ostream& print(std::ostream& stream) const { stream << key << " : " << *data; return stream;}
    T& getData() { return data; }
};

#endif