#include <string>
#include <sstream>
#include <exception>

#pragma once
#include "./basicos.hpp"

using namespace std;

template<class T>
struct Pila {
    Nodo_Simple<T> *nodo = nullptr;
    int tamano = 0;
};

template <class T> bool es_vacia(Pila<T> pila);
template <class T> void apilar(Pila<T> &pila, T valor);
template <class T> void desapilar(Pila<T> &pila);
template <class T> T cima(Pila<T> pila);
template <class T> int tamano(Pila<T> pila);
template <class T> T cima_y_desapilar(Pila<T> &pila);
template <class T> std::ostream& operator<<(std::ostream& os, Pila<T> pila);
template <class T> std::ostream& operator<<(std::ostream& os, Pila<T> *pila);

// Implementaciones

struct PilaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las pilas vacías.";
    }
};

template <class T> bool es_vacia(Pila<T> pila)
{
    return pila.tamano == 0;
}

template <class T> void apilar(Pila<T> &pila, T valor)
{
    if (es_vacia(pila))
    {
        pila = *(new Pila<T>);
        pila.nodo = new Nodo_Simple<T>;
    }
    else
    {
        Nodo_Simple<T> *nodo_nuevo = new Nodo_Simple<T>;
        nodo_nuevo->siguiente = pila.nodo;
        pila.nodo = nodo_nuevo;
    }
        pila.nodo->valor = valor;
        pila.tamano++;
}

template <class T> void desapilar(Pila<T> &pila)
{
    if(!es_vacia(pila))
    {
        Nodo_Simple<T> *nodo_antiguo = pila.nodo;
        pila.nodo = pila.nodo->siguiente;
        delete nodo_antiguo;
        pila.tamano--;
    }
    else
        throw PilaVaciaUndef();
}

template <class T> T cima(Pila<T> pila)
{
    if(!es_vacia(pila))
        return pila.nodo->valor;
    else
        throw PilaVaciaUndef();
}

template <class T> int tamano(Pila<T> pila)
{
    return pila.tamano;
}

template <class T> T cima_y_desapilar(Pila<T> &pila)
{
    T result = cima(pila);
    desapilar(pila);
    return result;
}

template <class T> std::ostream& operator<<(std::ostream& os, Pila<T> pila)
{
    Nodo_Simple<T> *nodo_actual = pila.nodo;
    os << "[";
    while (nodo_actual != nullptr)
    {
        os << nodo_actual->valor;
        if(nodo_actual->siguiente != nullptr)
            os << " ";
            nodo_actual = nodo_actual->siguiente;
    }
    os << "]";
    return os;
}

template <class T> std::ostream& operator<<(std::ostream& os, Pila<T> *pila)
{
    os << *pila;
    return os;
}
