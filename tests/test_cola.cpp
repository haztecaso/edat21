#include <iostream>
#include "../tads/cola.hpp"

using namespace std;


template<class T> void imprimir_cola(Cola<T> cola);
template<class T> void imprimir_pedir_vez(Cola<T> &cola, T v);
template<class T> void imprimir_avanzar(Cola<T> &cola);

int main(){
    cout << "Cola<char> cola = *(new Cola<char>); " << endl;
    Cola<char> cola = *(new Cola<char>);
    imprimir_cola(cola);

    imprimir_pedir_vez(cola, 'A');
    imprimir_pedir_vez(cola, 'B');
    imprimir_pedir_vez(cola, 'C');

    imprimir_avanzar(cola);
    imprimir_avanzar(cola);
    imprimir_avanzar(cola);

    return 0;
}

const char *sep = "  ";

template<class T> void imprimir_cola(Cola<T> cola)
{
    cout << sep << "cola = " << cola << endl;
    cout << sep << "tamano(cola) = " << tamano(cola);
    if (!es_vacia(cola))
        cout << ", " << "primero(cola) = " << primero(cola) << endl;
    else
        cout << endl;
    cout << endl;
}

template<class T> void imprimir_pedir_vez(Cola<T> &cola, T v)
{
    pedir_vez(cola, v);
    cout << "pedir_vez(cola, " << v << ")" << endl;
    imprimir_cola(cola);
}

template<class T> void imprimir_avanzar(Cola<T> &cola)
{
    avanzar(cola);
    cout << "avanzar(cola)" << endl;
    imprimir_cola(cola);
}
