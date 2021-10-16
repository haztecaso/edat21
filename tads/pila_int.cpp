#include <string>
#include <sstream>
#include "pila_int.hpp"

using namespace std;

bool es_vacia(Pila_Int pila)
{
    return pila == pila_vacia;
}

Pila_Int crear_pila()
{
    return pila_vacia;
}

Pila_Int crear_pila(int valor)
{
    Pila_Int pila = new Nodo_Pila_Int;
    pila->valor = valor;
    pila->siguiente = pila_vacia;
    return pila;
}

void apilar(Pila_Int &pila, int valor)
{
    if (es_vacia(pila))
        pila = crear_pila(valor);
    else
    {
        Pila_Int nueva = new Nodo_Pila_Int;
        nueva->valor = valor;
        nueva->siguiente = pila;
        pila = nueva;
    }
}

void desapilar(Pila_Int &pila)
{
    if(!es_vacia(pila))
    {
        Pila_Int old = pila;
        pila = pila->siguiente;
        delete old;
    }
    else
        throw PilaVaciaUndef();
}

int cima(Pila_Int pila)
{
    if(!es_vacia(pila))
    {
        return pila->valor;
    }
    else
        throw PilaVaciaUndef();
}

int cima_y_desapilar(Pila_Int &pila){
    int result = cima(pila);
    desapilar(pila);
    return result;
}

int tamano(Pila_Int pila)
{
    int result = 0;
    Pila_Int actual = pila;
    while (!es_vacia(actual))
    {
        actual = actual->siguiente;
        result++;
    }
    return result;
}

void liberar(Pila_Int &pila)
{
    while (!es_vacia(pila))
        desapilar(pila);
    delete pila;
}

ostream& operator<<(ostream& os, Pila_Int obj)
{
    Pila_Int actual = obj;
    while (!es_vacia(actual))
    {
        os << actual->valor << " ";
        actual = actual->siguiente;
    }
    return os;
}
