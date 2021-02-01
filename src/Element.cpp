/**
    \file Element.cpp
    \brief Element interface class and wrapper class TElement
*/
#include <string>
#include <memory>
#include <stdexcept>
#include "Element.h"

std::ostream& operator<<(std::ostream& os, Element& e){
     os << e.toString();
     return os;
}

bool operator==(const Element& e1,const Element& e2)
{
    return e1.toString()==e2.toString();
}

bool operator!=(const Element& e1,const Element& e2)
{
    return e1.toString()!=e2.toString();
}


// DIFFERENT EVALUATE-METHODS FOR INT AND CHAR TYPES
template<>
int TElement<int>::evaluate(const Valuation& v){
    return val;
}

template<>
int TElement<char>::evaluate(const Valuation& v){
    try{
        return v.at(val);
    }
    catch ( std::exception& e ){
        throw std::out_of_range("No Value for Key");
    }
}
