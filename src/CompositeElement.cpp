/**
    \file CompositeElement.cpp
    \brief CompositeElement class
*/
#include <string>
#include <memory>
#include <sstream>
#include "CompositeElement.h"
#include "Element.h"

using namespace std;
using namespace std::placeholders;
using IntElement = TElement<int>;
using VariableElement = TElement<char>;


CompositeElement::CompositeElement(const Element& e1, const Element& e2,
                                   const std::function<int(int,int)>& op_fun,
                                   char opc){

    oprnd1 = move(e1.clone());
    oprnd2 = move(e2.clone());
    this->op_fun=op_fun;
    op_ch=opc;

}

CompositeElement::CompositeElement(CompositeElement&& ce)
: oprnd1(move(ce.oprnd1)), oprnd2(move(ce.oprnd2))
{
    op_ch=ce.op_ch;
    op_fun=ce.op_fun;

    ce.oprnd1 = nullptr;
    ce.oprnd2 = nullptr;
    ce.op_fun = 0;
    ce.op_ch='\n';
}

CompositeElement::~CompositeElement(void){}

CompositeElement& CompositeElement::operator=(const CompositeElement& ce)
{
    oprnd1 = ce.oprnd1;
    oprnd2 = ce.oprnd2;
    op_ch=ce.op_ch;
    op_fun=ce.op_fun;

    return *this;
}

CompositeElement& CompositeElement::operator=(CompositeElement&& ce)
{
    if (this != &ce){
        oprnd1 = move(ce.oprnd1);
        oprnd2 = move(ce.oprnd2);
        op_ch=ce.op_ch;
        op_fun=ce.op_fun;

        ce.oprnd1 = nullptr;
        ce.oprnd2 = nullptr;
        ce.op_fun = 0;
        ce.op_ch='\n';
    }

    return *this;
}

shared_ptr<Element> CompositeElement::clone() const
{
    shared_ptr<Element> ptr = make_shared<CompositeElement>(*this);
    return ptr;
}

string CompositeElement::toString() const {
    stringstream strm;
    strm << "(" << oprnd1->toString() << op_ch << oprnd2->toString() << ")";
    return strm.str();
}


int CompositeElement::evaluate(const Valuation& v){
    auto g = bind(op_fun, _1, _2);
    return g(oprnd1->evaluate(v),oprnd2->evaluate(v));
}
