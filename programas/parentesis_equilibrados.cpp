#include <iostream>
#include <string>
#include "pila.hpp"

using namespace std;

bool parentesis_equilibrados(string str);

int main(){
    parentesis_equilibrados("((()()))((()())(()())())");
    parentesis_equilibrados("((()())(()(((())()())())");
    return 0;
}

bool parentesis_equilibrados(string str)
{
    pila<char> *p = new pila<char>;
    stringstream s(str);
    char c;
    bool result = true;
    while(s>>c && result)
    {
        if(c == '(')
        {
            apilar(*p, c);
        }
        else if (es_vacia(*p))
        {
            result = false;
        }
        else
        {
            desapilar(*p);
        }
    }
    result = result && es_vacia(*p);
    cout << str;
    if (!result)
        cout << " no" ;
    cout << " están equilibrados" << endl;
    return result;
}

