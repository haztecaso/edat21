#include <string>
#include <exception>

#include "./basicos.hpp"

#pragma once

using namespace std;

template<class T>
struct cola {
    nodo_simple<T> *primero = nullptr;
    nodo_simple<T> *ultimo  = nullptr;
    int tamano = 0;
};

template <class T> bool es_vacia(cola<T> c);
template <class T> void encolar(cola<T> &c, T d);
template <class T> void desencolar(cola<T> &c);
template <class T> T primero(cola<T> c);
template <class T> int tamano(cola<T> c);
template <class T> std::ostream& operator<<(std::ostream& os, cola<T> c);
template <class T> std::ostream& operator<<(std::ostream& os, cola<T> *c);

// Excepción que lanzan las operaciones parciales que no están definidas para
// las pilas vacías
struct ColaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las colas vacías.";
    }
};

// Implementaciones

template <class T> bool es_vacia(cola<T> c)
{
    return c.tamano == 0;
}

template <class T> void encolar(cola<T> &c, T d)
{
    if (es_vacia(c))
    {
        c.ultimo = new nodo_simple<T>;
        c.primero = c.ultimo;
    }
    else
    {
        nodo_simple<T> *nodo_nuevo = new nodo_simple<T>;
        c.ultimo->siguiente = nodo_nuevo;
        c.ultimo = nodo_nuevo;
    }
    c.ultimo->dato = d;
    c.tamano++;
}

template <class T> void desencolar(cola<T> &c)
{
    if(es_vacia(c)) throw ColaVaciaUndef();
    nodo_simple<T> *nodo_antiguo = c.primero;
    c.primero = c.primero->siguiente;
    delete nodo_antiguo;
    c.tamano--;
}

template <class T> T primero(cola<T> c)
{
    if(es_vacia(c)) throw ColaVaciaUndef();
    return c.primero->dato;
}

template <class T> int tamano(cola<T> c)
{
    return c.tamano;
}

template <class T> std::ostream& operator<<(std::ostream& os, cola<T> c)
{
    os << "[";
    nodo_simple<T> *nodo_actual = c.primero;
    while (nodo_actual != nullptr)
    {
        os << nodo_actual->dato;
        if (nodo_actual != c.ultimo)
            os << " ";
        nodo_actual = nodo_actual->siguiente;
    }
    os << "]";
    return os;
}

template <class T> std::ostream& operator<<(std::ostream& os, cola<T> *c)
{
    os << "*" << *c;
    return os;
}
