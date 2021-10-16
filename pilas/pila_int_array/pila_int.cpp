#include <string>
#include <sstream>
#include "pila_int.hpp"

using namespace std;

bool es_vacia(Pila_Int pila)
{
    return pila->tamano == 0;
}

Pila_Int crear_pila()
{
    Pila_Int pila = new Pila_Int_Struct;
    return pila;
}

Pila_Int crear_pila(int valor)
{
    Pila_Int pila = new Pila_Int_Struct;
    pila->tamano = 1;
    pila->contenido[0] = valor;
    return pila;
}

void aumentar_capacidad(Pila_Int pila)
{
    int *contenido = new int[pila->capacidad * 2];
    for(int i; i < pila->capacidad; i++)
        contenido[i] = pila->contenido[i]; // Hay alguna manera mejor de hacer esta copia?
    delete pila->contenido;
    pila->contenido = contenido;
    pila->capacidad *= 2;
}

void apilar(Pila_Int pila, int valor)
{
    if(pila->tamano == pila->capacidad)
        aumentar_capacidad(pila);
    pila->contenido[pila->tamano - 1] = valor;
    pila->tamano++;
}

void desapilar(Pila_Int pila)
{
    if(!es_vacia(pila))
        pila->tamano--;
    else
        throw PilaVaciaUndef();
}

int cima(Pila_Int pila)
{
    if(!es_vacia(pila))
        return pila->contenido[pila->tamano - 1];
    else
        throw PilaVaciaUndef();
}

int cima_y_desapilar(Pila_Int pila)
{
    int result = cima(pila);
    desapilar(pila);
    return result;
}

int tamano(Pila_Int pila)
{
    return pila->tamano;
}

void liberar(Pila_Int &pila)
{
    delete pila;
}

ostream& operator<<(ostream& os, Pila_Int pila)
{
    for(int i = 1; i <= pila->tamano; i++)
        os << pila->contenido[pila->tamano - 1 - i] << " ";
    return os;
}
