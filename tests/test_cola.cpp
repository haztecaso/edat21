#include <iostream>
#include "cola.hpp"

using namespace std;


template<class T> void imprimir_cola(cola<T> cola);
template<class T> void imprimir_pedir_vez(cola<T> &cola, T v);
template<class T> void imprimir_avanzar(cola<T> &cola);

int main(){
    cout << "cola<char> cola = *(new cola<char>); " << endl;
    cola<char> c= *(new cola<char>);
    imprimir_cola(c);

    imprimir_pedir_vez(c, 'A');
    imprimir_pedir_vez(c, 'B');
    imprimir_pedir_vez(c, 'C');

    imprimir_avanzar(c);
    imprimir_avanzar(c);
    imprimir_avanzar(c);

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

template<class T> void imprimir_pedir_vez(cola<T> &c, T v)
{
    pedir_vez(c, v);
    cout << "pedir_vez(c, " << v << ")" << endl;
    imprimir_cola(c);
}

template<class T> void imprimir_avanzar(cola<T> &c)
{
    avanzar(c);
    cout << "avanzar(c)" << endl;
    imprimir_cola(c);
}
