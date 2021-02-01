/**
    \file ElementaryMatrix_tests.cpp
    \brief Catch tests for wrapper class ElementarySquareMatrix
*/

#include <iostream>
#include "catch.hpp"
#include "ElementaryMatrix.h"

using namespace std;
using Valuation = std::map<char,int>;

TEST_CASE("ElementarySquareMatrix<IntElement> Invalid String Form", "[ElementarySquareMatrix<IntElement>_InvalidStringForm"){
    CHECK_NOTHROW(ConcreteSquareMatrix{});
    CHECK_NOTHROW(ConcreteSquareMatrix{"[[]]"});
    CHECK_NOTHROW(ConcreteSquareMatrix{"[[1]]"});
    CHECK_NOTHROW(ConcreteSquareMatrix{"[[1,2][1,2]]"});
    CHECK_NOTHROW(ConcreteSquareMatrix{"[[1,2,3][4,5,6][7,8,9]]"});
    CHECK_NOTHROW(ConcreteSquareMatrix{"[[1,2,3,1][4,5,6,4][7,8,9,7][1,2,3,4]]"});


    CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][2]]"});
    CHECK_THROWS_AS((ConcreteSquareMatrix{ "[[1,2][2,3]" }),std::invalid_argument);
    CHECK_THROWS_WITH((ConcreteSquareMatrix{ "[[1,2][2,3]" }),"Invalid String");
}

TEST_CASE("ElementarySquareMatrix<IntElement> Copy Constructor", "[ElementarySquareMatrix<IntElement>_CopyConstructor"){
    ConcreteSquareMatrix sq{"[[1,2][1,2]]"};
    ConcreteSquareMatrix sq2{sq};
    CHECK(sq.toString() == sq2.toString());
}

TEST_CASE("ElementarySquareMatrix<IntElement> operator=", "[ElementarySquareMatrix<IntElement>_operator="){
    ConcreteSquareMatrix sq{"[[2,4][2,4]]"};
    ConcreteSquareMatrix sq2 = sq;

    CHECK(sq2.toString() == "[[2,4][2,4]]");
}

TEST_CASE("ElementarySquareMatrix<IntElement> operator+=", "[ElementarySquareMatrix<IntElement>_operator+="){
    ConcreteSquareMatrix sq{"[[1,2][3,4]]"};
    sq += ConcreteSquareMatrix{"[[1,2][3,4]]"};

    CHECK(sq.toString() == "[[2,4][6,8]]");
    CHECK_THROWS_AS(( sq+=ConcreteSquareMatrix{"[[1,2,-2][2,3,2][1,2,3]]"} ),std::out_of_range);
    CHECK_THROWS_WITH((sq+=ConcreteSquareMatrix{"[[]]"}),"Different Size Matrixes");
}

TEST_CASE("ElementarySquareMatrix<IntElement> operator-=", "[ElementarySquareMatrix<IntElement>_operator-="){
    ConcreteSquareMatrix sq{"[[0,0][0,0]]"};
    sq -= ConcreteSquareMatrix{"[[2,4][6,8]]"};

    CHECK(sq.toString() == "[[-2,-4][-6,-8]]");
    CHECK_THROWS_AS(( sq-=ConcreteSquareMatrix{"[[1,2,-2][2,3,2][1,2,3]]"} ),std::out_of_range);
}

TEST_CASE("ElementarySquareMatrix<IntElement> operator*=", "[ElementarySquareMatrix<IntElement>_operator*="){
    ConcreteSquareMatrix sq{"[[2,3][4,5]]"};
    sq *= ConcreteSquareMatrix{"[[8,6][4,2]]"};
    CHECK(sq.toString() == "[[28,18][52,34]]");
    CHECK_THROWS_AS(( sq*=ConcreteSquareMatrix{"[[1,2,-2][2,3,2][1,2,3]]"} ),std::out_of_range);

    sq = ConcreteSquareMatrix{"[[-1,-2][1,2]]"};
    sq *= ConcreteSquareMatrix{"[[-4,5][6,7]]"};
    CHECK(sq.toString() == "[[-8,-19][8,19]]");
    CHECK_THROWS_AS(( sq*=ConcreteSquareMatrix{"[[]]"} ),std::out_of_range);
}

TEST_CASE("ElementarySquareMatrix<IntElement> operator== operator!=", "[ElementarySquareMatrix<IntElement>_operator==_operator!="){
    CHECK( (ConcreteSquareMatrix{"[[1,2][3,4]]"})!=(ConcreteSquareMatrix{"[[-1,-2][-3,-4]]"}) );
    CHECK( (ConcreteSquareMatrix{"[[1,2][3,4]]"})==(ConcreteSquareMatrix{"[[1,2][3,4]]"}) );
    CHECK( (ConcreteSquareMatrix{"[[1,2][3,4]]"})!=(ConcreteSquareMatrix{"[[1,2,2][3,4,4][3,4,4]]"}) );
    CHECK( (ConcreteSquareMatrix{"[[-1,2,2][3,-4,4][3,4,-4]]"})==(ConcreteSquareMatrix{"[[-1,2,2][3,-4,4][3,4,-4]]"}) );
}

TEST_CASE("ElementarySquareMatrix<IntElement> operator+", "[ElementarySquareMatrix<IntElement>_operator+"){
    ConcreteSquareMatrix sq{"[[1,2][3,4]]"};
    sq = sq + ConcreteSquareMatrix{"[[4,3][2,1]]"};
    CHECK(sq.toString() == "[[5,5][5,5]]");
    CHECK_THROWS_AS(( sq=sq+ConcreteSquareMatrix{"[[1,2,-2][2,3,2][1,2,3]]"} ),std::out_of_range);
}

TEST_CASE("ElementarySquareMatrix<IntElement> operator-", "[ElementarySquareMatrix<IntElement>_operator-"){
    ConcreteSquareMatrix sq{"[[1,2][3,4]]"};
    sq = sq - ConcreteSquareMatrix{"[[4,-3][2,-1]]"};
    CHECK(sq.toString() == "[[-3,5][1,5]]");
    CHECK_THROWS_AS(( sq=sq-ConcreteSquareMatrix{"[[1,2,-2][2,3,2][1,2,3]]"} ),std::out_of_range);
}

TEST_CASE("ElementarySquareMatrix<IntElement> operator*", "[ElementarySquareMatrix<IntElement>_operator*"){
    ConcreteSquareMatrix sq{"[[1,2][3,4]]"};
    sq = sq * ConcreteSquareMatrix{"[[4,3][2,1]]"};
    CHECK(sq.toString() == "[[8,5][20,13]]");
    CHECK_THROWS_AS(( sq=sq*ConcreteSquareMatrix{"[[1,2,-2][2,3,2][1,2,3]]"} ),std::out_of_range);

    sq = ConcreteSquareMatrix{"[[1,2][3,4]]"};
    sq = sq * ConcreteSquareMatrix{"[[-4,-3][2,-1]]"};
    CHECK(sq.toString() == "[[0,-5][-4,-13]]");
}

TEST_CASE("ElementarySquareMatrix<IntElement> transpose()", "[ElementarySquareMatrix<IntElement>_transpose]")
{
    ConcreteSquareMatrix sq{"[[1,2,3][-4,-5,-6][7,8,9]]"};
    sq = sq.transpose();
    CHECK(sq.toString() == "[[1,-4,7][2,-5,8][3,-6,9]]");
}

TEST_CASE("ElementarySquareMatrix<IntElement> print()", "[ElementarySquareMatrix<IntElement>_print]")
{
    ConcreteSquareMatrix sq{"[[1,2,3][-4,-5,-6][7,8,9]]"};
    cout <<"ConcreteSquareMatrix prints: ";
    sq.print(cout);
    cout << endl;

    sq = ConcreteSquareMatrix{"[[1,2][3,4]]"};
    cout << "ConcreteSquareMatrix: " << sq << endl;
}

TEST_CASE("ElementarySquareMatrix<Element> Invalid String Form", "[ElementarySquareMatrix<Element>_InvalidStringForm"){
    CHECK_NOTHROW(SymbolicSquareMatrix{});
    CHECK_NOTHROW(SymbolicSquareMatrix{"[[1]]"});
    CHECK_NOTHROW(SymbolicSquareMatrix{"[[x]]"});
    CHECK_NOTHROW(SymbolicSquareMatrix{"[[1,2][1,2]]"});
    CHECK_NOTHROW(SymbolicSquareMatrix{"[[1,x][y,2]]"});
    CHECK_NOTHROW(SymbolicSquareMatrix{"[[1,-2,3][-4,5,6][7,8,-9]]"});
    CHECK_NOTHROW(SymbolicSquareMatrix{"[[1,2,x][x,y,6][7,z,9]]"});
    CHECK_NOTHROW(SymbolicSquareMatrix{"[[1,2,3,1][4,5,6,4][7,8,9,7][1,2,3,4]]"});
    CHECK_NOTHROW(SymbolicSquareMatrix{"[[a,2,3,b][4,5,c,4][7,d,9,7][e,2,3,f]]"});


    CHECK_THROWS(SymbolicSquareMatrix{"[[]]"});
    CHECK_THROWS(SymbolicSquareMatrix{"[[1,2][2]]"});
    CHECK_THROWS(SymbolicSquareMatrix{"[[1,2][-x,2]]"});
    CHECK_THROWS(SymbolicSquareMatrix{"[[1,x][+,2]]"});
    CHECK_THROWS_AS((SymbolicSquareMatrix{ "[[1,2][2,-y]]" }),std::invalid_argument);
    CHECK_THROWS_WITH((SymbolicSquareMatrix{ "[[1,z][2,3]" }),"Invalid String");
}

TEST_CASE("ElementarySquareMatrix<Element> Copy Constructor", "[ElementarySquareMatrix<Element>_CopyConstructor"){
    SymbolicSquareMatrix sq{"[[1,x][y,2]]"};
    SymbolicSquareMatrix sq2{sq};
    CHECK(sq.toString() == sq2.toString());
}

TEST_CASE("ElementarySquareMatrix<Element> operator=", "[ElementarySquareMatrix<Element>_operator="){
    SymbolicSquareMatrix sq{"[[2,x][2,z]]"};
    SymbolicSquareMatrix sq2 = sq;

    CHECK(sq2.toString() == "[[2,x][2,z]]");
}

TEST_CASE("ElementarySquareMatrix<Element> operator== operator!=", "[ElementarySquareMatrix<Element>_operator==_operator!="){
    CHECK( (SymbolicSquareMatrix{"[[1,x][3,4]]"})!=(SymbolicSquareMatrix{"[[-1,-2][x,-4]]"}) );
    CHECK( (SymbolicSquareMatrix{"[[1,2][z,4]]"})==(SymbolicSquareMatrix{"[[1,2][z,4]]"}) );
    CHECK( (SymbolicSquareMatrix{"[[1,2][3,z]]"})!=(SymbolicSquareMatrix{"[[1,2,2][3,4,4][3,4,4]]"}) );
    CHECK( (SymbolicSquareMatrix{"[[-1,2,2][a,-4,4][b,4,-4]]"})==(SymbolicSquareMatrix{"[[-1,2,2][a,-4,4][b,4,-4]]"}) );
}


TEST_CASE("ElementarySquareMatrix<Element> operator+", "[ElementarySquareMatrix<Element>_operator+]")
{
    std::map<char,int> v;

    CHECK_THROWS_WITH((SymbolicSquareMatrix{"[[1,2,1][3,4,3][1,2,3]]"} +
                       SymbolicSquareMatrix{"[[4,3][2,1]]"}),"Different Size Matrixes");

    SymbolicSquareMatrix ssm = SymbolicSquareMatrix{"[[1,2][3,4]]"} + SymbolicSquareMatrix{"[[4,3][2,1]]"};
    CHECK( ssm.toString()== "[[(1+4),(2+3)][(3+2),(4+1)]]");
    CHECK( ssm.evaluate(v).toString()== "[[5,5][5,5]]");

    ssm = SymbolicSquareMatrix{"[[1,2][3,4]]"} + SymbolicSquareMatrix{"[[x,y][x,y]]"};
    CHECK( ssm.toString()== "[[(1+x),(2+y)][(3+x),(4+y)]]");

    CHECK_THROWS_WITH(( ssm.evaluate(v) ),"No Values for Every Variable");

    v['x']=-2;
    v['y']=4;
    CHECK_NOTHROW(ssm.evaluate(v));
    CHECK( ssm.evaluate(v).toString()== "[[-1,6][1,8]]");

    cout << "x=-2 y=4" <<endl;
    cout << ssm.toString() << " -> " << ssm.evaluate(v).toString() << endl;
}


TEST_CASE("ElementarySquareMatrix<Element> operator-", "[ElementarySquareMatrix<Element>_operator-]")
{
    std::map<char,int> v;

    CHECK_THROWS_WITH((SymbolicSquareMatrix{"[[1,2,1][3,4,3][1,2,3]]"} -
                       SymbolicSquareMatrix{"[[4,3][2,1]]"}),"Different Size Matrixes");

    SymbolicSquareMatrix ssm = SymbolicSquareMatrix{"[[1,2][3,4]]"} - SymbolicSquareMatrix{"[[4,3][2,1]]"};
    CHECK( ssm.toString()== "[[(1-4),(2-3)][(3-2),(4-1)]]");
    CHECK( ssm.evaluate(v).toString()== "[[-3,-1][1,3]]");

    ssm = SymbolicSquareMatrix{"[[1,2][3,4]]"} - SymbolicSquareMatrix{"[[x,y][x,y]]"};
    CHECK( ssm.toString()== "[[(1-x),(2-y)][(3-x),(4-y)]]");

    CHECK_THROWS_WITH(( ssm.evaluate(v) ),"No Values for Every Variable");

    v['x']=-2;
    v['y']=4;
    CHECK_NOTHROW(ssm.evaluate(v));
    CHECK( ssm.evaluate(v).toString()== "[[3,-2][5,0]]");

    cout << ssm.toString() << " -> " << ssm.evaluate(v).toString() << endl;
}


TEST_CASE("ElementarySquareMatrix<Element> operator*", "[ElementarySquareMatrix<Element>_operator*]")
{
    std::map<char,int> v;

    CHECK_THROWS_WITH((SymbolicSquareMatrix{"[[1,2,1][3,4,3][1,2,3]]"} *
                       SymbolicSquareMatrix{"[[4,3][2,1]]"}),"Different Size Matrixes");

    SymbolicSquareMatrix ssm = SymbolicSquareMatrix{"[[1,2][3,4]]"} * SymbolicSquareMatrix{"[[2,4][6,8]]"};
    CHECK( ssm.evaluate(v).toString()== "[[14,20][30,44]]");

    ssm = SymbolicSquareMatrix{"[[1,2][3,4]]"} * SymbolicSquareMatrix{"[[x,y][1,2]]"};
    CHECK( ssm.toString()== "[[((1*x)+(2*1)),((1*y)+(2*2))][((3*x)+(4*1)),((3*y)+(4*2))]]");

    CHECK_THROWS_WITH(( ssm.evaluate(v) ),"No Values for Every Variable");

    v['x']=-2;
    v['y']=4;
    CHECK_NOTHROW(ssm.evaluate(v));
    CHECK( ssm.evaluate(v).toString()== "[[0,8][-2,20]]");

    cout << ssm.toString() << " -> " << ssm.evaluate(v).toString() << endl <<endl;
}


TEST_CASE("ElementarySquareMatrix<Element> transpose()", "[ElementarySquareMatrix<Element>_transpose]")
{
    SymbolicSquareMatrix sq{"[[1,2,z][x,-5,-6][7,y,9]]"};
    sq = sq.transpose();
    CHECK(sq.toString() == "[[1,x,7][2,-5,y][z,-6,9]]");
}

TEST_CASE("SymbolicSquareMatrix print()", "[ElementarySquareMatrix<Element>_print]")
{
    SymbolicSquareMatrix sq{"[[x,2,3][-4,y,-6][7,8,z]]"};
    cout <<"SymbolicSquareMatrix prints: ";
    sq.print(cout);
    cout << endl;

    sq = SymbolicSquareMatrix{"[[1,a][b,4]]"};
    cout << "SymbolicSquareMatrix: " << sq << endl;
}

TEST_CASE("ElementarySquareMatrix<Element> evaluate()", "[ElementarySquareMatrix<Element>_evaluate]")
{
    Valuation v;
    SymbolicSquareMatrix sq{"[[x,2,3][4,y,6][7,8,z]]"};

    CHECK_THROWS(sq.evaluate(v));

    v['x'] = 1;
    CHECK_THROWS_AS(sq.evaluate(v),std::invalid_argument);

    v['y']=5;
    v['z']=9;

    CHECK_NOTHROW(sq.evaluate(v));

    ConcreteSquareMatrix csm = sq.evaluate(v);

    cout << "Constructed from " << sq << " new ConcreteSquareMatrix: " << csm << endl;
}
