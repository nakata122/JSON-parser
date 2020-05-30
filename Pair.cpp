#include <iostream>

#include "Pair.h"

template< typename T >
TypedPair<T>::TypedPair (const std::string &key, const T &_data) : Pair(key), data(_data) 
{

}

template< typename T >
Pair *TypedPair<T>::clone ()
{
    return new TypedPair(*this);
}

template< typename T >
std::ostream& TypedPair<T>::print(std::ostream& stream) const 
{ 
    return stream << std::boolalpha << data; //boolalpha is to print bool as true or false
} 

template<>
std::ostream& TypedPair<std::string>::print(std::ostream& stream) const 
{ 
    return stream << "\"" << data << "\""; 
} 

template< typename T >
void TypedPair<T>::printAll(const std::string &_key) const
{ 
    if(key == _key) std::cout << data << std::endl; 
}

template< typename T >
bool TypedPair<T>::edit(const std::string &path, Pair *obj) 
{ 
    return false; 
}

template< typename T >
bool TypedPair<T>::erase(const std::string &path) 
{ 
    return false; 
}

template< typename T >
bool TypedPair<T>::create(const std::string &path, Pair *obj) 
{ 
    return false; 
}

template< typename T >
Pair *TypedPair<T>::cutContent(const std::string &path) 
{ 
    return nullptr; 
}

template< typename T >
void TypedPair<T>::save(const std::string &path, std::ostream& stream)
{
    if(path.empty()) print(stream);
}


template class TypedPair<double>;
template class TypedPair<std::string>;
template class TypedPair<bool>;