#include <iostream>
#include "cola_static.hpp"

using namespace std;


template<class T> void imprimir_cola(cola<T> cola);
template<class T> void imprimir_encolar(cola<T> &cola, T v);
template<class T> void imprimir_desencolar(cola<T> &cola);

int main(){
    cout << "cola<char> cola = *(new cola<char>); " << endl;
    cola<char> c;
    imprimir_cola(c);

    imprimir_encolar(c, 'A');
    imprimir_encolar(c, 'B');
    imprimir_encolar(c, 'C');

    imprimir_desencolar(c);
    imprimir_desencolar(c);
    imprimir_desencolar(c);

    return 0;
}

const char *sep = "  ";

template<class T> void imprimir_cola(cola<T> c)
{
    cout << sep << "cola = " << c << endl;
    cout << sep << "tamano(c) = " << tamano(c);
    if (!es_vacia(c))
        cout << ", " << "primero(c) = " << primero(c) << endl;
    else
        cout << endl;
    cout << endl;
}

template<class T> void imprimir_encolar(cola<T> &c, T v)
{
    encolar(c, v);
    cout << "encolar(c, " << v << ")" << endl;
    imprimir_cola(c);
}

template<class T> void imprimir_desencolar(cola<T> &c)
{
    desencolar(c);
    cout << "desencolar(c)" << endl;
    imprimir_cola(c);
}
