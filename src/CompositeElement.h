/**
    \file CompositeElement.h
    \brief Header for CompositeElement class
*/
#ifndef COMPOSITEELEMENT_H
#define COMPOSITEELEMENT_H
#include <string>
#include <memory>
#include <map>
#include <functional>
#include "Element.h"

using Valuation = std::map<char,int>;
using IntElement = TElement<int>;
using VariableElement = TElement<char>;


/**
    \class CompositeElement
    \brief A class that is composite of Element classes
*/
class CompositeElement : public Element
{
private:
    std::shared_ptr<Element> oprnd1;
    std::shared_ptr<Element> oprnd2;
    std::function<int(int,int)> op_fun;
    char op_ch;


public:
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // CONSTRUCTORS  |
    // - - - - - - - -
    /**
    \brief Default constructor
    */
    CompositeElement(const Element& e1,
                     const Element& e2,
                     const std::function<int(int,int)>& op_fun,
                     char opc);


    /**
    \brief Copy constructor
    \param CompositeElement class that is copied
    */
    CompositeElement(const CompositeElement& ce) = default;


    /**
    \brief Move constructor
    \param CompositeElement object to move
    */
    CompositeElement(CompositeElement&&);


    /**
    \brief Default destructor
    */
    ~CompositeElement();


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // OPERATOR OVERLOADS  |
    // - - - - - - - - - - -
    /**
    \brief Operator to copy
    \param CompositeElement which values are copied
    \return CompositeElement of values equal to CompositeElement in parameter
    */
    CompositeElement& operator=(const CompositeElement&);


    /**
    \brief Move assignment operator
    \param CompositeElement which values are moved to
    \return CompositeElement of moved values equal to CompositeElement in parameter
    */
    CompositeElement& operator=(CompositeElement&&);


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // METHODS/FUNCTIONS |
    // - - - - - - - - - -
    /**
    \brief Clones CompositeElement
    \return std::shared_ptr pointer to CompositeElement clone
    */
    virtual std::shared_ptr<Element> clone() const override;


    /**
    \brief Makes a string representation of CompositeElement
    \return The string representation
    */
    virtual std::string toString() const override;


    /**
    \brief Returns value of CompositeElement
    \param Reference to Valuation class
    \return Integer val
    \throw std::out_of_range if key(variable) doesn't exists in a Valuation map class
    */
    virtual int evaluate(const Valuation& v) override;



}; // class CompositeElement


#endif // COMPOSITEELEMENT_H
