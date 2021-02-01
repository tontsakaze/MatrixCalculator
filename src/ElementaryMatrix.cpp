/**
    \file ElementaryMatrix.cpp
    \brief Wrapper class for ConcreteSquareMatrix and SymbolicSquareMatrix
*/
#include <memory>
#include <vector>
#include "ElementaryMatrix.h"

using namespace std;

template<>
string ElementarySquareMatrix<IntElement>::toString() const
{
    stringstream strm;
    strm << "[";

    // GO THROUGH VECTOR OF VECTOR OF IntElements
    vector< vector< shared_ptr<IntElement> >>::const_iterator it;
    for(it=elements.begin(); it!=elements.end();it++){
        strm << "[";
        bool first=true;

        // GO THROUGH VECTOR OF IntElements
        vector< shared_ptr<IntElement> > elem = *it;
        vector< shared_ptr<IntElement> >::const_iterator it2;

        for(it2=elem.begin(); it2!=elem.end();it2++){
            if (!first)
                strm << ",";
            strm << (**it2).toString();
            first = false;
        }

        strm << "]";
    }

    strm << "]";
    return strm.str();
}


template<>
string ElementarySquareMatrix<Element>::toString() const
{
    stringstream strm;
    strm << "[";

    // GO THROUGH VECTOR OF VECTOR OF Elements
    vector< vector< shared_ptr<Element> >>::const_iterator it;
    for(it=elements.begin(); it!=elements.end();it++){
        strm << "[";
        bool first=true;

        // GO THROUGH VECTOR OF Elements
        vector< shared_ptr<Element> > elem = *it;
        vector< shared_ptr<Element> >::const_iterator it2;

        for(it2=elem.begin(); it2!=elem.end();it2++){
            if (!first)
                strm << ",";
            strm << (**it2).toString();
            first = false;
        }

        strm << "]";
    }

    strm << "]";
    return strm.str();
}


template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::transpose()
{
    if (n>1){
        vector< vector< shared_ptr<IntElement> >> trans_vec(elements[0].size(), vector< shared_ptr<IntElement>>());

        for(unsigned int i=0; i<elements[0].size(); i++){
            for(unsigned int j=0; j<elements[i].size(); j++)
                trans_vec[j].push_back(move(elements[i][j]));
        }

        elements = trans_vec;
    }

    return *this;
}


template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::transpose()
{
    if (n>1){
        vector< vector< shared_ptr<Element> >> trans_vec(elements[0].size(), vector< shared_ptr<Element>>());

        for(unsigned int i=0; i<elements[0].size(); i++){
            for(unsigned int j=0; j<elements[i].size(); j++)
                trans_vec[j].push_back(move(elements[i][j]));
        }

        elements = trans_vec;
    }

    return *this;
}


template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator+=(const ElementarySquareMatrix<IntElement>& T)
{
    if (n==T.n){
        vector< vector< shared_ptr<IntElement> >> new_elements;

        // GO THROUGH VECTOR OF VECTOR OF IntElements-POINTERS
        vector< vector< shared_ptr<IntElement> >>::const_iterator it = elements.begin();
        vector< vector< shared_ptr<IntElement> >>::const_iterator it2 = T.elements.begin();

        while(it!=elements.end() && it2!=T.elements.end()){
            vector< shared_ptr<IntElement> > new_elems;

            vector< shared_ptr<IntElement> > elems = *it;
            vector< shared_ptr<IntElement> > elems2 = *it2;
            vector< shared_ptr<IntElement> >::const_iterator it3 = elems.begin();
            vector< shared_ptr<IntElement> >::const_iterator it4 = elems2.begin();

            // GO THROUGH VECTOR OF IntElements-POINTERS
            // ADD NEW IntElement SMARTPOINTER TO NEW VECTOR
            while(it3!=elems.end() && it4!=elems2.end()){
                auto s_sptr = make_shared<IntElement>(**it3+**it4);
                new_elems.push_back(move(s_sptr));
                it3++; it4++;
            }

            // ADD NEW VECTOR OF IntElements-POINTERS TO A NEW VECTOR
            new_elements.push_back(new_elems);
            it++; it2++;
        }

        // SET NEW VECTOR TO VECTOR OF VECTOR OF NEW IntElement-POINTERS
        elements = new_elements;

    }
    else{
        throw std::out_of_range("Different Size Matrixes");
    }

    return *this;
}


template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator-=(const ElementarySquareMatrix<IntElement>& T)
{
    if (n==T.n){
        vector< vector< shared_ptr<IntElement> >> new_elements;

        // GO THROUGH VECTOR OF VECTOR OF IntElements-POINTERS
        vector< vector< shared_ptr<IntElement> >>::const_iterator it = elements.begin();
        vector< vector< shared_ptr<IntElement> >>::const_iterator it2 = T.elements.begin();

        while(it!=elements.end() && it2!=T.elements.end()){
            vector< shared_ptr<IntElement> > new_elems;

            vector< shared_ptr<IntElement> > elems = *it;
            vector< shared_ptr<IntElement> > elems2 = *it2;
            vector< shared_ptr<IntElement> >::const_iterator it3 = elems.begin();
            vector< shared_ptr<IntElement> >::const_iterator it4 = elems2.begin();

            // GO THROUGH VECTOR OF IntElements-POINTERS
            // ADD NEW IntElement SMARTPOINTER TO NEW VECTOR
            while(it3!=elems.end() && it4!=elems2.end()){
                auto s_sptr = make_shared<IntElement>(**it3-**it4);
                new_elems.push_back(move(s_sptr));
                it3++; it4++;
            }

            // ADD NEW VECTOR OF IntElements-POINTERS TO A NEW VECTOR
            new_elements.push_back(new_elems);
            it++; it2++;
        }

        // SET NEW VECTOR TO VECTOR OF VECTOR OF NEW IntElement-POINTERS
        elements = new_elements;

    }
    else{
        throw std::out_of_range("Different Size Matrixes");
    }

    return *this;
}


template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator*=(const ElementarySquareMatrix<IntElement>& T)
{
    if (n==T.n){
        IntElement arr1[n][n];
        IntElement arr2[n][n];
        unsigned int i=0;


        // EXTRACT IntElements FROM FIRST ConcreteSquareMatrix's VECTOR OF VECTORS OF IntElement-POINTERS
        // ADD EXTRACTED IntElements TO 2D ARRAY
        vector< vector< shared_ptr<IntElement> >>::const_iterator it;
        for(it=elements.begin(); it!=elements.end();it++){

            vector< shared_ptr<IntElement> > elem = *it;
            vector< shared_ptr<IntElement> >::const_iterator it2;
            int j=0;

            for(it2=elem.begin();it2!=elem.end();it2++){
                arr1[i][j]=**it2;
                j++;
            }

            i++;
        }


        // EXTRACT IntElements FROM SECOND ConcreteSquareMatrix's VECTOR OF VECTORS OF IntElement-POINTERS
        // ADD EXTRACTED IntElements TO 2D ARRAY
        i=0;
        for(it=T.elements.begin(); it!=T.elements.end();it++){

            vector< shared_ptr<IntElement> > elem = *it;
            vector< shared_ptr<IntElement> >::const_iterator it2;
            int j=0;

            for(it2=elem.begin();it2!=elem.end();it2++){
                arr2[i][j]=**it2;
                j++;
            }

            i++;
        }


        // MULTIPLY FIRST ConcreteSquareMatrix's ROWS WITH
        // SECOND ConcreteSquareMatrix's COLS
        // ADD MULTIPLICATION(=SMARTPOINTER) TO A NEW VECTOR OF IntElement-POINTERS (=ROWS)
        // FINALLY, ADD NEW VECTOR OF IntElement-POINTERS TO
        // A NEW VECTOR OF VECTORs OF IntElement-POINTERS
        vector< vector< shared_ptr<IntElement> > > new_elements;
        for(unsigned int x=0;x<n;x++){
            vector< shared_ptr<IntElement> > new_elems;
            for(unsigned int y=0;y<n;y++){
                IntElement e{0};
                for(i=0;i<n;i++){
                    e += (arr1[x][i]*arr2[i][y]);
                }
                auto s_sptr = make_shared<IntElement>(e);
                new_elems.push_back(move(s_sptr));
            }
            new_elements.push_back(new_elems);
        }

        // SET NEW VECTOR OF VECTORS OF IntElement-POINTERS TO CURRENT
        elements = new_elements;
    }


    else{
        throw std::out_of_range("Different Size Matrixes");
    }

    return *this;
}


template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator+(const ElementarySquareMatrix<Element>& ssm)
{
    SymbolicSquareMatrix new_ssm{};
    function<int(int,int)> func = [](int x, int y){return x + y;};

    if (n==ssm.n){
        vector< vector< shared_ptr<Element> >> new_elements;

        // GO THROUGH VECTOR OF VECTOR OF Element-POINTERS
        vector< vector< shared_ptr<Element> >>::const_iterator it = elements.begin();
        vector< vector< shared_ptr<Element> >>::const_iterator it2 = ssm.elements.begin();

        while(it!=elements.end() && it2!=ssm.elements.end()){
            vector< shared_ptr<Element> > new_elems;

            vector< shared_ptr<Element> > elems = *it;
            vector< shared_ptr<Element> > elems2 = *it2;
            vector< shared_ptr<Element> >::const_iterator it3 = elems.begin();
            vector< shared_ptr<Element> >::const_iterator it4 = elems2.begin();

            // GO THROUGH VECTOR OF Element-POINTERS
            // ADD NEW Element SMARTPOINTER TO NEW VECTOR
            while(it3!=elems.end() && it4!=elems2.end()){
                CompositeElement ce{**it3,**it4,func,'+'};
                auto ptr = make_shared<CompositeElement>(ce);
                new_elems.push_back(move(ptr));
                it3++; it4++;
            }

            // ADD NEW VECTOR OF Element-POINTERS TO A NEW VECTOR
            new_elements.push_back(new_elems);
            it++; it2++;
        }

        // ADD NEW VECTOR OF VECTORS OF Element-POINTERS TO NEW SymbolicSquareMatrix
        new_ssm.elements=new_elements;
        new_ssm.n=new_elements[0].size();

    }
    else{
        throw std::out_of_range("Different Size Matrixes");
    }


    return new_ssm;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator+(const ElementarySquareMatrix<IntElement>& ssm)
{
    ConcreteSquareMatrix new_ssm{*this};

    if (n==ssm.n){
        new_ssm += ssm;
    }
    else{
        throw std::out_of_range("Different Size Matrixes");
    }


    return new_ssm;
}


template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator-(const ElementarySquareMatrix<Element>& ssm)
{
    SymbolicSquareMatrix new_ssm{};
    function<int(int,int)> func = [](int x, int y){return x - y;};

    if (n==ssm.n){
        vector< vector< shared_ptr<Element> >> new_elements;

        // GO THROUGH VECTOR OF VECTOR OF Element-POINTERS
        vector< vector< shared_ptr<Element> >>::const_iterator it = elements.begin();
        vector< vector< shared_ptr<Element> >>::const_iterator it2 = ssm.elements.begin();

        while(it!=elements.end() && it2!=ssm.elements.end()){
            vector< shared_ptr<Element> > new_elems;

            vector< shared_ptr<Element> > elems = *it;
            vector< shared_ptr<Element> > elems2 = *it2;
            vector< shared_ptr<Element> >::const_iterator it3 = elems.begin();
            vector< shared_ptr<Element> >::const_iterator it4 = elems2.begin();

            // GO THROUGH VECTOR OF Element-POINTERS
            // ADD NEW Element SMARTPOINTER TO NEW VECTOR
            while(it3!=elems.end() && it4!=elems2.end()){
                CompositeElement ce{**it3,**it4,func,'-'};
                auto ptr = make_shared<CompositeElement>(ce);
                new_elems.push_back(move(ptr));
                it3++; it4++;
            }

            // ADD NEW VECTOR OF Element-POINTERS TO A NEW VECTOR
            new_elements.push_back(new_elems);
            it++; it2++;
        }

        // ADD NEW VECTOR OF VECTORS OF Element-POINTERS TO NEW SymbolicSquareMatrix
        new_ssm.elements=new_elements;
        new_ssm.n=new_elements[0].size();

    }
    else{
        throw std::out_of_range("Different Size Matrixes");
    }


    return new_ssm;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator-(const ElementarySquareMatrix<IntElement>& ssm)
{
    ConcreteSquareMatrix new_ssm{*this};

    if (n==ssm.n){
        new_ssm -= ssm;
    }
    else{
        throw std::out_of_range("Different Size Matrixes");
    }


    return new_ssm;
}


template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator*(const ElementarySquareMatrix<Element>& ssm)
{
    SymbolicSquareMatrix new_ssm{};

    if (n==ssm.n){
        function<int(int,int)> func_multi= [](int x, int y){return x * y;};
        function<int(int,int)> func_plus = [](int x, int y){return x + y;};

        shared_ptr<Element> arr1[n][n];
        shared_ptr<Element> arr2[n][n];
        unsigned int i=0;


        // EXTRACT IntElements FROM FIRST ConcreteSquareMatrix's VECTOR OF VECTORS OF IntElement-POINTERS
        // ADD EXTRACTED IntElements TO 2D ARRAY
        vector< vector< shared_ptr<Element> >>::const_iterator it;
        for(it=elements.begin(); it!=elements.end();it++){

            vector< shared_ptr<Element> > elem = *it;
            vector< shared_ptr<Element> >::const_iterator it2;
            int j=0;

            for(it2=elem.begin();it2!=elem.end();it2++){
                arr1[i][j]=*it2;
                j++;
            }

            i++;
        }


        // EXTRACT IntElements FROM SECOND ConcreteSquareMatrix's VECTOR OF VECTORS OF IntElement-POINTERS
        // ADD EXTRACTED IntElements TO 2D ARRAY
        i=0;
        for(it=ssm.elements.begin(); it!=ssm.elements.end();it++){

            vector< shared_ptr<Element> > elem = *it;
            vector< shared_ptr<Element> >::const_iterator it2;
            int j=0;

            for(it2=elem.begin();it2!=elem.end();it2++){
                arr2[i][j]=*it2;
                j++;
            }

            i++;
        }



        // DO THE SQUARE MATRIX MULTIPLICATION AS FOLLOW:
        // CREATE FIRST CompositeElement FROM MOST LEFT AND TOP ELEMENTS
        // GO THROUGH ALL ELEMENTS THAT IS NEEDED FOR THIS ONE ELEMENT
        // CREATE SECOND CompositeElement FROM NEXT ELEMENTS
        // CREATE NEW CompositeElement THAT IS COMPOSE OF ITSELF AND SECOND CompositeElement
        // ADD POINTER OF THE FINAL CompositeElement TO THE VECTOR OF Element-POINTERS
        // FINALLY, ADD NEW VECTOR OF Element-POINTERS TO
        // A NEW VECTOR OF VECTORs OF Element-POINTERS
        vector< vector< shared_ptr<Element> > > new_elements;
        for(unsigned int x=0;x<n;x++){
            vector< shared_ptr<Element> > new_elems;
            for(unsigned int y=0;y<n;y++){
                CompositeElement ce{ *arr1[x][0], *arr2[0][y], func_multi, '*' };
                for(i=1;i<n;i++){
                    CompositeElement ce2{ *arr1[x][i], *arr2[i][y], func_multi, '*' };
                    ce = CompositeElement{ ce, ce2, func_plus, '+' };
                }
                auto ptr = make_shared<CompositeElement>(ce);
                new_elems.push_back(move(ptr));
            }
            new_elements.push_back(new_elems);
        }

        // ADD NEW VECTOR OF VECTORS OF Element-POINTERS TO NEW SymbolicSquareMatrix
        new_ssm.elements=new_elements;
        new_ssm.n=new_elements[0].size();

    }
    else{
        throw std::out_of_range("Different Size Matrixes");
    }


    return new_ssm;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator*(const ElementarySquareMatrix<IntElement>& ssm)
{
    ConcreteSquareMatrix new_ssm{*this};

    if (n==ssm.n){
        new_ssm *= ssm;
    }
    else{
        throw std::out_of_range("Different Size Matrixes");
    }


    return new_ssm;
}



bool isUnvariableSquareMatrix(const string& str){
    // [[x,x][x,x]]
    // ROW: [...]
    // COL: x
    int cols=0, rows=0, j=0, brackets=0;


    if (str.empty() || str.length()<4 )
        return false;
    else if (str[0]!='[' || str[str.length()-1]!=']')
        return false;


    // [ [...] .. [...] ]
    //   ^->->->->->->^
    for ( unsigned int i=1; i<str.length()-1; i++ ){
        // IF '[' THERE HAS TO BE
        // '-', ']' OR NUMBER AFTER
        // ELSE RETURN FALSE
        if ( str[i]=='[' ){                             // [ -> '-' / # / ']'
            brackets = brackets + 1;
            if (str[i+1]!=']' && str[i+1]!='-' && !isdigit(str[i+1])){
                return false;
            }
        }




        // IF NUMBER BEFORE COMMA, ADD ONE TO j
        // ELSE RETURN FALSE
        else if ( str[i]==','){                         // # -> ,
            if ( isdigit(str[i-1]) )
                j = j + 1;
            else{
                return false;
            }
        }



        // IF ']' THERE HAS TO BE
        // '[' AFTER (EXCLUDING FINAL CHAR)
        // '[' OR NUMBER BEFORE
        // ELSE RETURN FALSE
        else if ( str[i]==']' ){
            brackets = brackets - 1;
            rows = rows + 1;

            if (i+1!=str.length()-1 && str[i+1]!='['){   // ] -> '['
                return false;
            }


            if ( isdigit(str[i-1]) ){                   // # -> ]
                if (j+1 != cols && cols>0){
                    return false;
                }
                else if (cols==0){
                    cols = j+1;
                }
            }
            else if ( str[i-1]!='[' ){                   // '[' -> ]
                return false;
            }

            j=0;
        }


        if (brackets>1 || brackets<0){
            return false;
        }
    }


    // 0x0 IS A VALID ConcreteSquareMatrix
    // -> [[]]
    if (rows==1 && cols==0)
        return true;

    //IF ALL ROWS WERE EMPTY
    else if (cols==0)
        return false;

    // IF THERE IS NOT AS MANY ROWS AS COLS
    else if (cols!=rows)
        return false;

    else
        return true;

}

bool isVariableSquareMatrix(const string& str){
    // [[x,x][x,x]]
    // ROW: [...]
    // COL: x
    int cols=0, rows=0, j=0, brackets=0;


    if (str.empty() || str.length()<4 )
        return false;
    else if (str[0]!='[' || str[str.length()-1]!=']')
        return false;


    // [ [...] .. [...] ]
    //   ^->->->->->->^
    for ( unsigned int i=1; i<str.length()-1; i++ ){
        // IF '[' THERE HAS TO BE
        // '-', ']', NUMBER OR LETTER AFTER
        // ELSE RETURN FALSE
        if ( str[i]=='[' ){                                 // [ -> '-' / # / ']' / X
            brackets = brackets + 1;
            if (str[i+1]!=']' && str[i+1]!='-' && !isdigit(str[i+1]) && !isalpha(str[i+1])){
                return false;
            }
        }




        // IF NUMBER OR LETTER BEFORE COMMA, ADD ONE TO j
        // ELSE RETURN FALSE
        else if ( str[i]==','){                             // # / X -> ,
            if ( isdigit(str[i-1]) || isalpha(str[i-1]) )
                j = j + 1;
            else{
                return false;
            }
        }


        // BEFORE LETTER THERE HAS TO BE
        // '[' OR ','
        // ELSE RETURN FALSE
        else if ( isalpha(str[i]) ){                         // [ / , -> X
            if ( str[i-1]!=',' && str[i-1]!='[' )
                return false;
        }



        // IF ']' THERE HAS TO BE
        // '[' AFTER (EXCLUDING FINAL CHAR)
        // '[', NUMBER OR LETTER BEFORE
        // ELSE RETURN FALSE
        else if ( str[i]==']' ){
            brackets = brackets - 1;
            rows = rows + 1;

            if (i+1!=str.length()-1 && str[i+1]!='['){      // ] -> '['
                return false;
            }


            if ( isdigit(str[i-1]) || isalpha(str[i-1]) ){  // # / X -> ]
                if (j+1 != cols && cols>0){
                    return false;
                }
                else if (cols==0){
                    cols = j+1;
                }
            }
            else if ( str[i-1]!='[' ){                      // '[' -> ]
                return false;
            }

            j=0;
        }


        if (brackets>1 || brackets<0){
            return false;
        }
    }


    // 0x0 IS NOT A VALID SymbolicSquareMatrix
    // -> [[]]
    if (rows==1 && cols==0)
        return false;

    //IF ALL ROWS WERE EMPTY
    else if (cols==0)
        return false;

    // IF THERE IS NOT AS MANY ROWS AS COLS
    else if (cols!=rows)
        return false;

    else
        return true;

}




template<>
ElementarySquareMatrix<IntElement>::ElementarySquareMatrix(const std::string& s)
{
    if (isUnvariableSquareMatrix(s)){
        // CALC HOW MANY ELEMENTS
        n = 0;
        for ( unsigned int i=1; i<s.length()-1; i++ ){
            if ( s[i]=='[' ) n+=1;}

        // x=BEGIN OF ELEMENT = [
        // z=END OF ELEMENT = ]
        unsigned int x = 0;
        unsigned int z = 0;
        for ( unsigned int i=1; i<s.length()-1; i++ ){
            if ( s[i]=='[' ) x=i;
            if ( s[i]==']' ) z=i;


            // IF EMPTY ELEMENT, ADD AS MANY ZEROS
            // TO IntElement-POINTERS VECTOR AS THERE IS TOTAL OF ELEMENTS
            // LASTLY, ADD THAT VECTOR(of zeros) TO VECTOR OF IntElement-POINTERS VECTORS
            if ( x>0 && z>0 && z-1==x){
                vector< shared_ptr<IntElement> > vec;

                for ( unsigned int j=0; j<n; j++ ){
                    auto s_sptr = make_shared<IntElement>(0);
                    vec.push_back(move(s_sptr));
                }

                elements.push_back(vec);
                x=0;
                z=0;
            }


            // REFORM STRING TO A NEW STRING
            // EXAMPLE: "[1,2,3]" -> "1 2 3"
            // THEN EXTRACT NUMBERS AND ADD TO IntElement-POINTERS VECTOR
            // LASTLY, ADD THAT VECTOR TO VECTOR OF IntElement-POINTERS VECTORS
            else if ( x>0 && z>0){
                stringstream ss;
                int n = 1;
                for ( unsigned int j=x+1; j<z; j++ ){
                    if (s[j]==','){
                        ss<<" ";
                        n = n + 1;
                    }
                    else
                        ss<<s[j];
                }

                vector< shared_ptr<IntElement> > vec;
                int number;

                for(int i=0; i<n; i++){
                    ss >> number;
                    auto s_sptr = make_shared<IntElement>(number);
                    vec.push_back(move(s_sptr));
                }

                elements.push_back(vec);
                x=0;
                z=0;
            }
        }
    }
    else{
        throw std::invalid_argument("Invalid String");
    }

}

template<>
ElementarySquareMatrix<Element>::ElementarySquareMatrix(const std::string& s)
{
    if (isVariableSquareMatrix(s)){
        // CALC HOW MANY ELEMENTS
        n = 0;
        for ( unsigned int i=1; i<s.length()-1; i++ ){
            if ( s[i]=='[' ) n+=1;}

        // x=BEGIN OF ELEMENT = [
        // z=END OF ELEMENT = ]
        unsigned int x = 0;
        unsigned int z = 0;
        for ( unsigned int i=1; i<s.length()-1; i++ ){
            if ( s[i]=='[' ) x=i;
            if ( s[i]==']' ) z=i;


            // IF EMPTY ELEMENT, ADD AS MANY ZEROS
            // TO Element-POINTERS VECTOR AS THERE IS TOTAL OF ELEMENTS
            // LASTLY, ADD THAT VECTOR(of zeros) TO VECTOR OF Element-POINTERS VECTORS
            if ( x>0 && z>0 && z-1==x){
                vector< shared_ptr<Element> > vec;

                for ( unsigned int j=0; j<n; j++ ){
                    auto s_sptr = make_shared<IntElement>(0);
                    vec.push_back(move(s_sptr));
                }

                elements.push_back(vec);
                x=0;
                z=0;
            }


            // REFORM STRING TO A NEW STRING
            // EXAMPLE: "[1,x,-3]" -> "1,x,-3"
            // THEN EXTRACT NUMBERS FOR IntElements AND ADD TO Element-POINTERS VECTOR
            // THEN EXTRACT LETTERS FOR VariableElements AND ADD TO Element-POINTERS VECTOR
            // LASTLY, ADD THAT VECTOR TO VECTOR OF Element-POINTERS VECTORS
            else if ( x>0 && z>0){
                stringstream ss;
                for ( unsigned int j=x+1; j<z; j++ ){
                    ss<<s[j];
                }


                vector< shared_ptr<Element> > vec;
                int number;
                char ch;
                string stemp;

                while ( getline(ss,stemp,',') ) {
                    if ( isalpha(stemp[0]) ){
                        ch = stemp[0];
                        auto s_sptr = make_shared<VariableElement>(ch);
                        vec.push_back(move(s_sptr));
                    }
                    else{
                        number = stoi(stemp);
                        auto s_sptr = make_shared<IntElement>(number);
                        vec.push_back(move(s_sptr));
                    }
                }


                elements.push_back(vec);
                x=0;
                z=0;
            }
        }
    }
    else{
        throw std::invalid_argument("Invalid String");
    }

}


template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::evaluate(const Valuation& v)
{
    return *this;
}


template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<Element>::evaluate(const Valuation& v)
{
    stringstream strm;
    strm << "[";

    // GO THROUGH VECTOR OF VECTOR OF Elements
    vector< vector< shared_ptr<Element> >>::const_iterator it;
    for(it=elements.begin(); it!=elements.end();it++){
        strm << "[";
        bool first=true;

        // GO THROUGH VECTOR OF Elements
        vector< shared_ptr<Element> > elem = *it;
        vector< shared_ptr<Element> >::const_iterator it2;

        for(it2=elem.begin(); it2!=elem.end();it2++){
            if (!first)
                strm << ",";

            try{
                strm << (**it2).evaluate(v);
            } catch( exception& e ){
                throw invalid_argument("No Values for Every Variable");
            }

            first = false;
        }

        strm << "]";
    }
    strm << "]";

    return ConcreteSquareMatrix{strm.str()};
}
