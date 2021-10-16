#include <iostream>
#include "pila.hpp"

using namespace std;

int main(){
    Pila<int> p1 = *(new Pila<int>);
    apilar(p1,1);
    apilar(p1,1);
    apilar(p1,1);
    apilar(p1,1);

    Pila<int> p2 = *(new Pila<int>);
    apilar(p2,1);
    apilar(p2,2);
    apilar(p2,3);
    apilar(p2,4);
    apilar(p2,4);

    Pila<int> p3 = *(new Pila<int>);
    apilar(p3,3);
    apilar(p3,3);

    Pila<Pila<int>> pila_de_pilas = *(new Pila<Pila<int>>);
    apilar(pila_de_pilas, p1);
    apilar(pila_de_pilas, p2);
    apilar(pila_de_pilas, p3);

    cout << pila_de_pilas << endl;
    cout << "tamano(p1) = " << tamano(p1) << "; ";
    cout << "tamano(p2) = " << tamano(p2) << "; ";
    cout << "tamano(p3) = " << tamano(p3) << "; ";
    cout << endl;

    desapilar_con_cuidado(p2);
    desapilar_con_cuidado(p1);
    desapilar_con_cuidado(p3);

    cout << pila_de_pilas << endl;
    cout << "tamano(p1) = " << tamano(p1) << "; ";
    cout << "tamano(p2) = " << tamano(p2) << "; ";
    cout << "tamano(p3) = " << tamano(p3) << "; ";

    return 0;
}
