#include <iostream>
#include <string>
#include "pila_static.hpp"

using namespace std;

typedef string el;
typedef pila<pila<el> *> super_pila;

int main(){
    super_pila sp;
    pila<el> *p1 = new pila<el>;
    pila<el> *p2 = new pila<el>;

    apilar(*p1, string("A"));
    apilar(*p2, string("B"));


    apilar(sp, p1);
    apilar(sp, p2);

    apilar(*p1, string("B"));
    apilar(*p2, string("A"));

    cout << sp << endl;

    apilar(*p1, string("B"));
    apilar(*p2, string("A"));
    apilar(*p1, string("C"));
    apilar(*p2, string("C"));
    apilar(sp, p1);
    apilar(sp, p1);
    apilar(sp, p2);
    apilar(sp, p2);

    cout << sp << endl;

    return 0;
}
