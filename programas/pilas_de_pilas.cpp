#include <iostream>
#include <string>
#include "../tads/pila.hpp"

using namespace std;

typedef string el;
typedef pila<pila<el> *> super_pila;

int main(){
    super_pila *sp = new super_pila;
    pila<el> *p1 = new pila<el>;
    pila<el> *p2 = new pila<el>;

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
    return 0;
}
