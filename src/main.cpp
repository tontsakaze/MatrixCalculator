/**
    \file main.cpp
    \brief Main file for int main and catch tests
*/
#define CATCH_CONFIG_RUNNER
#include <sstream>
#include "catch.hpp"
#include "Element.h"
#include "ElementaryMatrix.h"

using namespace std;
using Valuation = std::map<char,int>;

Valuation v;
stack<SymbolicSquareMatrix> mstack;
//string s_shift = "                    ";
string s_shift = "\t\t";



void printCommandList(void){
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" <<endl;
    cout << "Matrix Calculator by Toni \"tontsakaze\" Torvela" << endl;
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" <<endl;
    cout << "LIST OF COMMANDS: " << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" <<endl;
    cout << "[[#1,#2][#3,#4]]\t" << "Adds 2x2 matrix to the stack that has given values" << endl;
    cout << "\t\t\t" << "   e.g. [[1,2][3,4]]" << endl;
    cout << "[[x,y][y,x]]\t\t" << "Adds 2x2 matrix to the stack that has given variables. (Here x and y)" << endl;

    cout << "x=#\t\t\t" << "Sets value(#) for the given variable. (Here x)" << endl;
    cout << "\t\t\t" <<    "   e.g. x=10" << endl << endl;

    cout << "+\t\t\t" <<   "Adds together the top two matrices in the stack creating a new one" << endl;
    cout << "\t\t\t" <<    "   that is added on the top of the stack." << endl;

    cout << "-\t\t\t" <<   "Subtracts from the top-most matrix in the stack the second most top" << endl;
    cout << "\t\t\t" <<    "   matrix creating a new one that is added on the top of the stack." << endl;

    cout << "*\t\t\t" <<   "Multiplies together the top two matrices in the stack creating a new one" << endl;
    cout << "\t\t\t" <<    "   that is added on the top of the stack." << endl;

    cout << "=\t\t\t" <<   "Solves the top-most matrix in the stack and then clears the whole stack." << endl << endl;

    cout << "transpose\t\t" << "Transposes the top-most matrix in the stack creating a new one" << endl;
    cout << "\t\t\t" <<    "   that is added on the top of the stack." << endl;
    cout << "clear\t\t\t" << "Clears the stack." << endl << endl;

    cout << "help\t\t\t" << "Shows the list of commands." << endl;
    cout << "quit\t\t\t" << "Exits the program." << endl;
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" <<endl;
}


void checkCommand(const string& s){
    // FOR OPERATIONS
    if(s=="+" || s=="-" || s=="*"){
        if(mstack.size() < 2){
            cout << "ERR: Couldn't perform operation(" << s << ")!"<<endl<<
                    "     Not enough matrixes in stack!" << endl<<endl;
            return;
        }

        SymbolicSquareMatrix sqm1 = mstack.top();
        mstack.pop();
        SymbolicSquareMatrix sqm2 = mstack.top();
        mstack.push(sqm1);

        SymbolicSquareMatrix new_sqm;
        try{
            if(s=="+")
                new_sqm = sqm1 + sqm2;
            if(s=="-")
                new_sqm = sqm1 - sqm2;
            if(s=="*")
                new_sqm = sqm1 * sqm2;

        }catch (const exception& e){
            cout << "ERR: Couldn't perform operation(" << s << ")!" << endl;
            cout << "      "<< e.what() << endl<<endl;
            return;
        }


        mstack.push(new_sqm);
        cout << s_shift << new_sqm.toString() << endl;
    }


    // FOR EVALUATION
    else if(s=="="){
        if(mstack.size() == 0){
            cout << "ERR: Couldn't perform operation(" << s << ")!"<<endl<<
                    "     Not enough matrixes in stack!" << endl<<endl;
            return;
        }


        SymbolicSquareMatrix sqm = mstack.top();

        try{
            cout << s_shift << sqm.evaluate(v).toString() << endl;
            checkCommand("clear");
        }catch (const exception& e){
            cout << "ERR: Couldn't evaluate matrix!" << endl;
            cout << "      "<< e.what() << endl<<endl;
        }
    }

    // PRINT COMMAND LIST
    else if(s=="help"){
        printCommandList();
    }

    // CLEAR STACK
    else if(s=="clear"){
        while( !mstack.empty() )
            mstack.pop();
        cout << s_shift << "Matrix stack cleared!" << endl;
    }


    // TRANSPOSE LAST MATRIX AND ADD TO STACK
    else if(s=="transpose"){
        SymbolicSquareMatrix sqm = mstack.top().transpose();
        mstack.push(sqm);
        cout << s_shift << mstack.top().toString() << endl;
    }


    // `FOR VARIABLES TO VALUATION
    else if( isalpha(s[0]) && s[1]=='=' ){
        char key;
        int value;
        bool err=false;

        key=s[0];
        stringstream ss;
        for(unsigned int i=2; i<s.length(); i++)
            ss<<s[i];
        ss >> value;

        string str;
        ss >> str;

        if (str!="")
            err = true;
        if ( !isdigit(s[2]) )
            err = true;

        if(!err){
            v[key]=value;
            cout << s_shift << key << " has now value " << value << endl;
        }
        else{
            cout << "ERR: Couldn't assign value for variable!" << endl;
            cout << "     Invalid assignment!"<< endl;
            cout << "     E.g. Correct form: x=0"<< endl<<endl;
        }

    }


    // CREATING MATRIX
    else if(s[0]=='['){
        try{
            SymbolicSquareMatrix sqm{s};
            mstack.push(sqm);
        }catch (const exception& e){
            cout << "ERR: Couldn't create matrix!" << endl;
            cout << "      "<< e.what() << endl<<endl;
        }
    }

    else if (s!="quit")
        cout << "ERR: Invalid command!" << endl;

}




int main(int argc, char** argv){
    if( argc > 1 ){
        string arg = argv[1];
        if( arg=="-tests" ){
            cout << "===============================================================================" << endl;
            cout << "Begins running tests..." << endl;
            cout << "===============================================================================" << endl;
            int result = Catch::Session().run(1,argv);
            cout << result << " failed test cases " << endl << endl << endl;
        }
    }

    cout << endl << endl;
    printCommandList();


// THE TEXT-BASED USER INTERFACE PART
    string cmd = "";
    while(cmd!="quit"){
        cmd = "";
        cout << "> ";
        getline(cin, cmd);

        checkCommand(cmd);
    }

    return 0;
}
