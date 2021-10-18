#include <iostream>
#include "../tads/pila.hpp"

using namespace std;

int main(){
    Pila<char> *p1 = new Pila<char>;
    apilar(*p1,'a');
    apilar(*p1,'b');
    apilar(*p1,'c');

    Pila<char> *p2 = new Pila<char>;
    apilar(*p2,'A');
    apilar(*p2,'B');
    apilar(*p2,'C');

    Pila<char> *p3 = new Pila<char>;
    apilar(*p3,'1');
    apilar(*p3,'2');
    apilar(*p3,'3');


    Pila<Pila<char> *> *pila_de_pilas = new Pila<Pila<char> *>;
    apilar(*pila_de_pilas, p1);
    apilar(*pila_de_pilas, p2);
    apilar(*pila_de_pilas, p3);

    cout << *pila_de_pilas << endl;
    cout << "tamano(p1) = " << tamano(*p1) << "; ";
    cout << "tamano(p2) = " << tamano(*p2) << "; ";
    cout << "tamano(p3) = " << tamano(*p3) << "; ";
    cout << endl;

    desapilar(*p1);
    desapilar(*p2);
    desapilar(*p3);

    cout << *pila_de_pilas << endl;
    cout << "tamano(p1) = " << tamano(*p1) << "; ";
    cout << "tamano(p2) = " << tamano(*p2) << "; ";
    cout << "tamano(p3) = " << tamano(*p3) << "; ";

    return 0;
}
