#include <iostream>
#include <string>
#include "pila.hpp"

using namespace std;

typedef string El;
typedef pila<pila<El> *> super_pila;

bool parentesis_equilibrados(string str);
void superpilas();

int main(){
    superpilas();

    parentesis_equilibrados("((()()))((()())(()())())");
    parentesis_equilibrados("((()())(()(((())()())())");

    return 0;
}

void superpilas()
{
    super_pila *sp = new super_pila;
    pila<El> *p1 = new pila<El>;
    pila<El> *p2 = new pila<El>;

    apilar(*sp, p1);
    apilar(*sp, p2);

    apilar(*p1, string("D"));
    apilar(*p2, string("B"));
    apilar(*p1, string("B"));
    apilar(*p2, string("A"));
    apilar(*p1, string("C"));
    apilar(*p2, string("C"));

    apilar(*sp, p1);
    apilar(*sp, p1);
    apilar(*sp, p2);
    apilar(*sp, p2);

    desapilar(*p2);
    apilar(*p2, string("D"));

    cout << *sp << endl;
    liberar(*sp);
    liberar(*p1);
    liberar(*p2);
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

