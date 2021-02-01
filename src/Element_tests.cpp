/**
    \file Element_tests.cpp
    \brief Catch tests for Element interface, TElement wrapper and CompositeElement classes
*/

#include <string>
#include <memory>
#include <iostream>
#include "catch.hpp"
#include "Element.h"
#include "CompositeElement.h"


using namespace std;
using Valuation = std::map<char,int>;


const IntElement IE{1337};
const VariableElement VE{'x'};
const function<int(int,int)> func = [](int x, int y){return x + y;};
const function<int(int,int)> func2 = [](int x, int y){return x - y;};


TEST_CASE("TElement<char> setVal() & getVal()", "[TElement<char>_setVal_getVal]")
{
    VariableElement ve1{'x'};
    VariableElement ve2{'y'};
    CHECK(ve1.getVal() == 'x');
    CHECK(ve2.getVal() == 'y');

    ve1.setVal('a');
    ve2.setVal('b');
    CHECK(ve1.getVal() == 'a');
    CHECK(ve2.getVal() == 'b');

}

TEST_CASE("TElement<char> clone()","[TElement<char>_clone]"){
    // clone();
    shared_ptr<VariableElement> ptr1 = make_shared<VariableElement>('x');
    shared_ptr<Element> ptr2 = ptr1->clone();
    shared_ptr<VariableElement> ptr3 = ptr1;

    CHECK(ptr2 != ptr1);
    CHECK(ptr3 == ptr1);
}

TEST_CASE("TElement<char> toString()","[TElement<char>_toString]"){
    VariableElement ve{'x'};
    CHECK(ve.toString() == "x");
    ve.setVal('y');
    CHECK(ve.toString() == "y");

    cout << "VariableElement's value: " << ve << endl;
}

TEST_CASE("TElement<char> evaluate()","[TElement<char>_evaluate]"){
    Valuation v;
    VariableElement ve{'x'};

    CHECK_THROWS(ve.evaluate(v));

    v['x']=1337;

    CHECK_NOTHROW(ve.evaluate(v));
    CHECK(ve.evaluate(v) == 1337);
}

TEST_CASE("TElement<char> operator==","[TElement<char>_operator==]"){
    VariableElement ve{'x'};
    VariableElement ve2{'y'};

    CHECK( (ve==ve2) == false);

    ve2.setVal('x');
    CHECK(ve==ve2);
}


TEST_CASE("TElement<int> setVal() & getVal()", "[TElement<int>_setVal_getVal]")
{
    IntElement ie1{5};
    IntElement ie2{10};
    CHECK(ie1.getVal() == 5);
    CHECK(ie2.getVal() == 10);

    ie1.setVal(-5);
    ie2.setVal(15);
    CHECK(ie1.getVal() == -5);
    CHECK(ie2.getVal() == 15);

}

TEST_CASE("TElement<int> clone()","[TElement<int>_clone]"){
    // clone();
    shared_ptr<IntElement> ptr1 = make_shared<IntElement>(10);
    shared_ptr<Element> ptr2 = ptr1->clone();
    shared_ptr<IntElement> ptr3 = ptr1;

    CHECK(ptr2 != ptr1);
    CHECK(ptr3 == ptr1);
}

TEST_CASE("TElement<int> toString()","[TElement<int>_toString]"){
    IntElement ie{1337};
    CHECK(ie.toString() == "1337");
    ie.setVal(-50);
    CHECK(ie.toString() == "-50");

    cout << "IntElement's value: " << ie << endl;
}

TEST_CASE("TElement<int> evaluate()","[TElement<int>_evaluate]"){
    Valuation v;

    IntElement ie{1010};
    CHECK(ie.evaluate(v) == 1010);
    ie.setVal(-50);
    CHECK(ie.evaluate(v) == -50);
}

TEST_CASE("TElement<int> operator==","[TElement<int>_operator==]"){
    IntElement ie{10};
    IntElement ie2{5};

    CHECK( (ie==ie2) == false);

    ie2.setVal(10);
    CHECK(ie==ie2);
}

TEST_CASE("TElement<int> operator+","[TElement<int>_operator+]"){
    IntElement ie{10};
    IntElement ie2{5};

    ie += ie2;
    CHECK(ie.getVal() == 15);

    ie2.setVal(-5);
    ie += ie2;
    CHECK(ie.getVal() == 10);
}

TEST_CASE("TElement<int> operator-","[TElement<int>_operator-]"){
    IntElement ie{10};
    IntElement ie2{5};

    ie -= ie2;
    CHECK(ie.getVal() == 5);

    ie2.setVal(-10);
    ie -= ie2;
    CHECK(ie.getVal() == 15);
}

TEST_CASE("TElement<int> operator*","[TElement<int>_operator*]"){
    IntElement ie{10};
    IntElement ie2{5};

    ie *= ie2;
    CHECK(ie.getVal() == 50);

    ie2.setVal(-2);
    ie *= ie2;
    CHECK(ie.getVal() == -100);
}


TEST_CASE("CompositeElement clone()","[CompositeElement_clone]"){
    shared_ptr<CompositeElement> ptr1 = make_shared<CompositeElement>(IE, VE, func, '+');
    shared_ptr<Element> ptr2 = ptr1->clone();
    shared_ptr<CompositeElement> ptr3 = ptr1;

    CHECK(ptr2 != ptr1);
    CHECK(ptr3 == ptr1);
}

TEST_CASE("CompositeElement toString()","[CompositeElement_toString]"){
    CompositeElement ce{IE, VE, func, '+'};
    CHECK(ce.toString() == "(1337+x)");
    ce = CompositeElement{VE, VE, func2, '-'};
    CHECK(ce.toString() == "(x-x)");

    cout << ce.toString() << endl;
}

TEST_CASE("CompositeElement evaluate()","[CompositeElement_evaluate]"){
    Valuation v;
    CompositeElement ce{IE, VE, func, '+'};

    CHECK_THROWS(ce.evaluate(v));
    CHECK_THROWS_WITH(( ce.evaluate(v) ),"No Value for Key");

    v['x']=683;

    CHECK_NOTHROW(ce.evaluate(v));
    CHECK(ce.evaluate(v) == 2020);

    cout << endl << "x=683" << endl;
    cout << ce.toString() << " -> " << ce.evaluate(v) << endl << endl;

}

TEST_CASE("Element clone()","[Element_clone]"){
    shared_ptr<IntElement> ptr1 = make_shared<IntElement>(1337);
    shared_ptr<VariableElement> ptr2 = make_shared<VariableElement>('x');

    shared_ptr<Element> ptr3 = ptr1->clone();
    shared_ptr<Element> ptr4 = ptr2->clone();

    CHECK(ptr3 != ptr1);
    CHECK(ptr4 != ptr2);
}

TEST_CASE("Element toString()","[Element_toString]"){
    IntElement ie2{1337};
    VariableElement ve2{'x'};

    Element* e1 = &ve2;
    Element* e2 = &ie2;

    CHECK(e1->toString() == "x");
    CHECK(e2->toString() == "1337");

    cout << "Element's value: " << *e1 << endl;
    cout << "Element's value: " << *e2 << endl;
}

TEST_CASE("Element evaluate()","[Element_evaluate]"){
    Valuation v;
    IntElement ie2{1337};
    VariableElement ve2{'x'};

    Element* e1 = &ve2;
    Element* e2 = &ie2;

    CHECK_THROWS(e1->evaluate(v));


    CHECK_THROWS_AS(e1->evaluate(v),std::out_of_range);


    v['x'] = 7331;

    CHECK_NOTHROW(e1->evaluate(v));
    CHECK(e1->evaluate(v) == 7331);

    CHECK(e2->evaluate(v) == 1337);
}
