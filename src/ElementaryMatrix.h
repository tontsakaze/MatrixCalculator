/**
    \file ElementaryMatrix.h
    \brief Header for wrapper class ElementarySquareMatrix
*/
#ifndef ELEMENTARYMATRIX_H
#define ELEMENTARYMATRIX_H
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>

#include "Element.h"
#include "CompositeElement.h"

using Valuation = std::map<char,int>;
using IntElement = TElement<int>;
using VariableElement = TElement<char>;


/**
    \class ElementarySquareMatrix
    \brief A class that works as an wrapper class for SymbolicSquareMatrix and ConcreteSquareMatrix classes
*/
template<class Type>
class ElementarySquareMatrix
{
private:
    unsigned int n;
    std::vector< std::vector< std::shared_ptr<Type> >> elements;

public:
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // CONSTRUCTORS  |
    // - - - - - - - -
    /**
    \brief Default constructor
    */
    ElementarySquareMatrix(){ n=0; }


    /**
    \brief Parametric constructor
    \param String of the matrix that is created
    \throw std::invalid_argument if string is invalid
    */
    ElementarySquareMatrix(const std::string&);


    /**
    \brief Copy constructor for ElementarySquareMatrix<Type>
    \tparam Type of ElementarySquareMatrix object
    \param T object that is copied
    */
    ElementarySquareMatrix(const ElementarySquareMatrix<Type>& T)
    :n(T.n), elements(T.elements){}


    /**
    \brief Move constructor
    \param ElementarySquareMatrix<Type> object to move
    \tparam Type of ElementarySquareMatrix object
    */
    ElementarySquareMatrix(ElementarySquareMatrix<Type>&& T)
    :elements(move(T.elements)){
        n = T.n;
        T.elements.clear();
        T.n=0;
    }


    /**
    \brief Default destructor
    */
    virtual ~ElementarySquareMatrix(){elements.clear();}


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // OPERATOR OVERLOADS  |
    // - - - - - - - - - - -
    /**
    \brief Operator to copy
    \param ElementarySquareMatrix<Type> which values are copied
    \tparam Type of ElementarySquareMatrix object
    \return ElementarySquareMatrix of values equal to ElementarySquareMatrix<Type> in parameter
    */
    ElementarySquareMatrix& operator=(const ElementarySquareMatrix<Type>& T){
        n = T.n;
        elements = T.elements;

        return *this;
    }


    /**
    \brief Move assignment operator
    \param ElementarySquareMatrix<Type> which values are moved to
    \tparam Type of ElementarySquareMatrix object
    \return ElementarySquareMatrix of moved values equal to ElementarySquareMatrix in parameter
    */
    ElementarySquareMatrix& operator=(ElementarySquareMatrix<Type>&& T){
        if (this != &T){
            elements = move(T.elements);
            n = T.n;

            T.elements.clear();
            T.n=0;
        }

        return *this;
    }


    /**
    \brief Operator for addition
    \param ConcreteSquareMatrix that is added
    \return The addition of ConcreteSquareMatrix s
    \throw std::out_of_range if ConcreteSquareMatrixes are different sizes
    */
    ElementarySquareMatrix& operator+=(const ElementarySquareMatrix<Type>&);


    /**
    \brief Operator for subtraction
    \param ConcreteSquareMatrix that is subtracted
    \return The subtraction of ConcreteSquareMatrix s
    \throw std::out_of_range if ConcreteSquareMatrixes are different sizes
    */
    ElementarySquareMatrix& operator-=(const ElementarySquareMatrix<Type>&);


    /**
    \brief Operator for multiplication
    \param ConcreteSquareMatrix to multiply with
    \return The product of ConcreteSquareMatrix s
    \throw std::out_of_range if ConcreteSquareMatrixes are different sizes
    */
    ElementarySquareMatrix& operator*=(const ElementarySquareMatrix<Type>&);


    /**
    \brief Addition operator
    \param ElementarySquareMatrix<Type> which value is added
    \tparam Type of ElementarySquareMatrix object
    \return New ElementarySquareMatrix that is addition of ElementarySquareMatrixs
    \throw std::out_of_range if ElementarySquareMatrixes are different sizes
    */
    ElementarySquareMatrix operator+(const ElementarySquareMatrix<Type>&);


    /**
    \brief Subtraction operator
    \param ElementarySquareMatrix<Type> which value is subtracted
    \tparam Type of ElementarySquareMatrix object
    \return New ElementarySquareMatrix that is subtraction of ElementarySquareMatrixes
    \throw std::out_of_range if ElementarySquareMatrixes are different sizes
    */
    ElementarySquareMatrix operator-(const ElementarySquareMatrix<Type>&);


    /**
    \brief Multiplication operator
    \param ElementarySquareMatrix<Type> which value is multiplied
    \tparam Type of ElementarySquareMatrix object
    \return New ElementarySquareMatrix that is Multiplication of ElementarySquareMatrixes
    \throw std::out_of_range if ElementarySquareMatrixes are different sizes
    */
    ElementarySquareMatrix operator*(const ElementarySquareMatrix<Type>&);


    /**
    \brief Operator for comparison
    \param ElementarySquareMatrix<Type> that is compared
    \tparam Type of ElementarySquareMatrix object
    \return True if all ElementarySquareMatrixes' elements are the same
    */
    bool operator==(const ElementarySquareMatrix<Type>& T) const{
        if (toString()==T.toString())
            return true;

        return false;
    }



    /**
    \brief Operator for comparison negation
    \param ElementarySquareMatrix<Type> that is compared
    \tparam Type of ElementarySquareMatrix object
    \return True if all ElementarySquareMatrixes' elements are not the same
    */
    bool operator!=(const ElementarySquareMatrix<Type>& T) const{
        if (toString()!=T.toString())
            return true;

        return false;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // METHODS/FUNCTIONS |
    // - - - - - - - - - -
    /**
    \brief Adds string presentation of ElementarySquareMatrix to osstream
    \param Osstream to print in
    */
    void print(std::ostream& os){ os << toString(); }


    /**
    \brief Makes a string representation of ElementarySquareMatrix
    \return The string representation
    */
    std::string toString() const;


    /**
    \brief Transposes ElementarySquareMatrix
    \return A new transposed ElementarySquareMatrix
    */
    ElementarySquareMatrix transpose();


    /**
    \brief Creates ElementarySquareMatrix from TElements with the help of Valuation map class
    \param Reference to Valuation class
    \return A new created ElementarySquareMatrix
    \throw std::invalid_argument if there is even one variable that has no value in Valuation map class
    */
    ElementarySquareMatrix<IntElement> evaluate(const Valuation& v);



}; // class ElementarySquareMatrix


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// OUTSIDE CLASS FUNCTIONS |
// - - - - - - - - - - - - -
/**
\brief Output operator
\param Osstream to print in
\param ElementarySquareMatrix<Type> ref to an ElementarySquareMatrix object
\tparam Type of ElementarySquareMatrix object
\return osstream
*/
template <typename Type>
std::ostream& operator<<(std::ostream& os,const ElementarySquareMatrix<Type>& T){
    os << T.toString();
    return os;
}


/**
\brief Operator for addition
\param ElementarySquareMatrix<Type> which elements are added
\param ElementarySquareMatrix<Type> which elements are added
\tparam Type of ElementarySquareMatrix object
\return The addition of ElementarySquareMatrixes' elements
*/
template <typename Type>
ElementarySquareMatrix<Type> operator+(const ElementarySquareMatrix<Type>& T1,
                                       const ElementarySquareMatrix<Type>& T2){
    ElementarySquareMatrix<Type> esm{T1};
    esm+=T2;
    return esm;
}


/**
\brief Operator for subtraction
\param ElementarySquareMatrix<Type> which elements are subtracted
\param ElementarySquareMatrix<Type> which elements are subtracted
\tparam Type of ElementarySquareMatrix object
\return The subtraction of ElementarySquareMatrixes' elements
*/
template <typename Type>
ElementarySquareMatrix<Type> operator-(const ElementarySquareMatrix<Type>& T1,
                                       const ElementarySquareMatrix<Type>& T2){
    ElementarySquareMatrix<Type> esm{T1};
    esm-=T2;
    return esm;
}


/**
\brief Operator for multiplication
\param ElementarySquareMatrix<Type> which elements are multiplied
\param ElementarySquareMatrix<Type> which elements are multiplied
\tparam Type of ElementarySquareMatrix object
\return The multiplication of ElementarySquareMatrixes' elements
*/
template <typename Type>
ElementarySquareMatrix<Type> operator*(const ElementarySquareMatrix<Type>& T1,
                                       const ElementarySquareMatrix<Type>& T2){
    ElementarySquareMatrix<Type> esm{T1};
    esm*=T2;
    return esm;
}


using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;


#endif // ELEMENTARYMATRIX_H

