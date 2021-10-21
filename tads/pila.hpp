#include <string>
#include <sstream>
#include <exception>

#include "./basicos.hpp"

#pragma once

using namespace std;

template<class T>
struct pila {
    nodo_simple<T> *nodo = nullptr;
    int tamano = 0;
};

template <class T> bool es_vacia(pila<T> p);
template <class T> void apilar(pila<T> &p, T d);
template <class T> void desapilar(pila<T> &p);
template <class T> T cima(pila<T> p);
template <class T> int tamano(pila<T> p);
template <class T> T cima_y_desapilar(pila<T> &p);
template <class T> std::ostream& operator<<(std::ostream& os, pila<T> p);
template <class T> std::ostream& operator<<(std::ostream& os, pila<T> *p);

// Implementaciones

struct PilaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las pilas vacías.";
    }
};

template <class T> bool es_vacia(pila<T> p)
{
    return p.tamano == 0;
}

template <class T> void apilar(pila<T> &p, T d)
{
    if (es_vacia(p))
    {
        p = *(new pila<T>);
        p.nodo = new nodo_simple<T>;
    }
    else
    {
        nodo_simple<T> *nodo_nuevo = new nodo_simple<T>;
        nodo_nuevo->siguiente = p.nodo;
        p.nodo = nodo_nuevo;
    }
        p.nodo->dato = d;
        p.tamano++;
}

template <class T> void desapilar(pila<T> &p)
{
    if(!es_vacia(p))
    {
        nodo_simple<T> *nodo_antiguo = p.nodo;
        p.nodo = p.nodo->siguiente;
        delete nodo_antiguo;
        p.tamano--;
    }
    else
        throw PilaVaciaUndef();
}

template <class T> T cima(pila<T> p)
{
    if(!es_vacia(p))
        return p.nodo->dato;
    else
        throw PilaVaciaUndef();
}

template <class T> int tamano(pila<T> p)
{
    return p.tamano;
}

template <class T> T cima_y_desapilar(pila<T> &p)
{
    T result = cima(p);
    desapilar(p);
    return result;
}

template <class T> std::ostream& operator<<(std::ostream& os, pila<T> p)
{
    nodo_simple<T> *nodo_actual = p.nodo;
    os << "[";
    while (nodo_actual != nullptr)
    {
        os << nodo_actual->dato;
        if(nodo_actual->siguiente != nullptr)
            os << " ";
            nodo_actual = nodo_actual->siguiente;
    }
    os << "]";
    return os;
}

template <class T> std::ostream& operator<<(std::ostream& os, pila<T> *p)
{
    os << *p;
    return os;
}
