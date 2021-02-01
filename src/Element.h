/**
    \file Element.h
    \brief Element interface class header and wrapper class TElement
*/
#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include <sstream>
#include <memory>
#include <map>

using Valuation = std::map<char,int>;

/**
    \class Element
    \brief A class that works as an interface class for VariableElement and IntElement classes
*/
class Element{
    public:
        /**
        \brief Virtual destructor
        */
        virtual ~Element(){};


        // HAD TO REMOVE SO I CAN CONTINUE
        /**
        \brief Virtual clone method
        \return Pointer to Element class
        */
        virtual std::shared_ptr<Element> clone() const=0;


        /**
        \brief Virtual toString method
        \return String
        */
        virtual std::string toString() const=0;


        /**
        \brief Virtual evaluate method
        \return Integer
        */
        virtual int evaluate(const Valuation&)=0;

};

/**
\brief Output operator
\param Osstream to print in
\param Reference to an Element object
*/
std::ostream& operator<<(std::ostream& os, Element& e);


/**
\brief Comparison operator
\param Reference to first Element class that is compared
\param Reference to second Element class that is compared
\return boolean true if both Elements have the same value
*/
bool operator==(const Element& e1, const Element& e2);


/**
\brief Comparison operator
\param Reference to first Element class that is compared
\param Reference to second Element class that is compared
\return boolean true if both Elements have different values
*/
bool operator!=(const Element& e1, const Element& e2);



/**
    \class TElement
    \brief A class that works as an wrapper class for VariableElement and IntElement classes
*/
template<typename Type>
class TElement : public Element{

private:
    Type val;

public:
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // CONSTRUCTORS  |
    // - - - - - - - -
    /**
    \brief Default constructor
    */
    TElement(){}


    /**
    \brief Copy constructor for TElement<Type>
    \tparam Type of TElement object
    \param T object that is copied
    */
    TElement(const TElement<Type>& T):val(T.val){}


    /**TElement<Type> operator+(const TElement<Type>& T1, const TElement<Type>& T2)
    \brief Constructor that sets val as v
    \param Type v that is type of TElement object
    */
    TElement(Type v):val(v){}


    /**
    \brief Default destructor
    */
    virtual ~TElement(){ }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // OPERATOR OVERLOADING |
    // - - - - - - - - - - _
    /**
    \brief Operator for comparison of TElement<Type>s
    \tparam Type of TElement object
    \param T object which value is compared with
    \return True if TElements' values are the same
    */
    bool operator==(const TElement& T) const{ return val==T.val; }


    /**
    \brief Operator for addition of TElement<Type>s
    \tparam Type of TElement object
    \param T object that is added
    \return The addition of TElements
    */
    TElement<Type>& operator+=(const TElement<Type>& T){ val+=T.val; return *this; }


    /**
    \brief Operator for subtraction of TElement<Type>s
    \tparam Type of TElement object
    \param T object that is subtracted
    \return The subtraction of TElements
    */
    TElement<Type>& operator-=(const TElement<Type>& T){ val-=T.val; return *this; }


    /**
    \brief Operator for multiplication of TElement<Type>s
    \tparam Type of TElement object
    \param T object to multiply with
    \return The product of TElements
    */
    TElement<Type>& operator*=(const TElement<Type>& T){ val*=T.val; return *this; }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // METHODS/FUNCTIONS |
    // - - - - - - - - - -
    /**
    \brief Getter of val-attribute
    \return The value of val-attribute
    */
    Type getVal(){ return val; }


    /**
    \brief Setter of val-attribute
    \param Value of type v
    */
    void setVal(Type v){ val=v; }


    /**
    \brief Clones object
    \return std::shared_ptr pointer to TElement clone
    */
    std::shared_ptr<Element> clone() const{
        std::shared_ptr<Element> ptr = std::make_shared< TElement<Type> >(*this);
        return move(ptr);
    }


    /**
    \brief Makes a string representation of TElement object
    \return The string representation
    */
    std::string toString() const{
        std::stringstream ss;
        ss << val;
        return ss.str();
    }


    /**
    \brief Returns a value from Valuation class using val as a key
    \param Reference to Valuation class
    \return Integer value for val keyType
    \throw std::out_of_range if key(variable) doesn't exists in a Valuation map class
    */
    int evaluate(const Valuation& v);


}; //class TElement

/**
\brief Operator for addition
\param TElement<Type> that is added
\param TElement<Type> that is added
\tparam Type of TElement object
\return The addition of TElements
*/
template <typename Type>
TElement<Type> operator+(const TElement<Type>& T1, const TElement<Type>& T2){
    TElement<Type> te{T1};
    te+=T2;
    return te;
}

/**
\brief Operator for subtraction
\param TElement<Type> that is subtracted
\param TElement<Type> that is subtracted
\tparam Type of TElement object
\return The subtraction of TElements
*/
template <typename Type>
TElement<Type> operator-(const TElement<Type>& T1, const TElement<Type>& T2){
    TElement<Type> te{T1};
    te-=T2;
    return te;
}

/**
\brief Operator for multiplication
\param TElement<Type> that is multiplied
\param TElement<Type> that is multiplied
\tparam Type of TElement object
\return The product of TElements
*/
template <typename Type>
TElement<Type> operator*(const TElement<Type>& T1, const TElement<Type>& T2){
    TElement<Type> te{T1};
    te*=T2;
    return te;
}



#endif // ELEMENT_H
