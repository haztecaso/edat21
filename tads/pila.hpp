#include <string>
#include <sstream>
#include <exception>

#include "./basicos.hpp"

#pragma once

using namespace std;

template<class T>
struct pila {
    nodo_simple<T> *cima = nullptr;
    int tamano = 0;
};

template <class T> bool es_vacia(pila<T> p);
template <class T> void apilar(pila<T> &p, T d);
template <class T> void desapilar(pila<T> &p);
template <class T> void liberar(pila<T> &p);
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
    // La función crear_nodo_simple está definida en el fichero ./basicos.hpp
    nodo_simple<T> *nodo_nuevo = crear_nodo_simple(d, p.cima);
    p.cima = nodo_nuevo;
    p.tamano++;
}

template <class T> void desapilar(pila<T> &p)
{
    if(es_vacia(p)) throw PilaVaciaUndef();
    nodo_simple<T> *nodo_antiguo = p.cima;
    p.cima = p.cima->siguiente;
    delete nodo_antiguo;
    p.tamano--;
}

template <class T> void liberar(pila<T> &p)
{
    while(!es_vacia(p)) desapilar(p);
}

template <class T> T cima(pila<T> p)
{
    if(es_vacia(p)) throw PilaVaciaUndef();
    return p.cima->dato;
}

template <class T> int tamano(pila<T> p)
{
    return p.tamano;
}

template <class T> T cima_y_desapilar(pila<T> &p)
{
    if(es_vacia(p)) throw PilaVaciaUndef();
    T result = cima(p);
    desapilar(p);
    return result;
}

template <class T> std::ostream& operator<<(std::ostream& os, pila<T> p)
{
    nodo_simple<T> *nodo_actual = p.cima;
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
    os << "*" << *p;
    return os;
}
