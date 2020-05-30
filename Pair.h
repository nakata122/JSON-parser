#ifndef _PAIR_H
#define _PAIR_H

#include <string>

///Represents an abstract class holding a key value pairs
struct Pair
{
    std::string key;

    Pair(const std::string &_key) : key(_key) {};
    virtual ~Pair() {};
    virtual std::ostream& print(std::ostream& stream) const = 0;
    virtual void printAll(const std::string &_key) const = 0;
    virtual bool edit(const std::string &path, Pair *obj) = 0;
    virtual bool erase(const std::string &path) = 0;
    virtual bool create(const std::string &path, Pair *obj) = 0;
    virtual Pair *cutContent(const std::string &path) = 0;
    virtual void save(const std::string &path, std::ostream& stream) = 0;

    
    friend std::ostream& operator << (std::ostream& stream, const Pair& pair)
    {
        return pair.print(stream);
    }
};

///Template class for all generic types
template< typename T >
class TypedPair : public Pair
{
private:
    T data;
public:
    TypedPair (const std::string &key, const T &_data);
    virtual std::ostream& print(std::ostream& stream) const;
    virtual void printAll(const std::string &_key) const;
    virtual bool edit(const std::string &path, Pair *obj);
    virtual bool erase(const std::string &path);
    virtual bool create(const std::string &path, Pair *obj);
    virtual Pair *cutContent(const std::string &path);
    virtual void save(const std::string &path, std::ostream& stream);
};
#endif