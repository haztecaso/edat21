/*
 * Pilas - Implementación dinámica
 *
 * Jorge González Gutiérrez
 * Adrián Lattes Grassi
 * Fernando Montero Erustes
 *
 */

#pragma once
#include <sstream>
#include "basicos.hpp"

// Definición del tipo para las pilas
// Los valores por defecto corresponden con la representación de una pila vacía
template<class T>
struct pila {
    nodo_simple<T> *cima = nullptr;
    int tamano = 0;
};

// Determina si una pila es vacía
template <class T> bool es_vacia(pila<T> p);

// Devuelve el tamaño de una pila
template <class T> int tamano(pila<T> p);

// Añade un elemento en la cima de una pila
template <class T> void apilar(pila<T> &p, T d);

// Elimina la cima de una pila
// Función parcial: lanza una excepción VaciaUndef si la pila es vacía 
template <class T> void desapilar(pila<T> &p);

// Devuelve la cima de una pila (sin sacarla de la pila)
// Función parcial: lanza una excepción VaciaUndef si la pila es vacía 
template <class T> T cima(pila<T> p);

// Devuelve y elimina la cima de una pila
// Función parcial: lanza una excepción VaciaUndef si la pila es vacía 
template <class T> T cima_y_desapilar(pila<T> &p);

// Libera la memoria de una pila
template <class T> void liberar(pila<T> &p);

// Sobrecarga del operador << para imprimir una pila
template <class T> std::ostream& operator<<(std::ostream& os, pila<T> p);

// Sobrecarga del operador << para imprimir un puntero a una pila
template <class T> std::ostream& operator<<(std::ostream& os, pila<T> *p);

/*
 * IMPLEMENTACIONES
 */

template <class T> bool es_vacia(pila<T> p)
{
    return tamano(p) == 0;
}

template <class T> int tamano(pila<T> p)
{
    return p.tamano;
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
    if(es_vacia(p)) throw VaciaUndef();
    nodo_simple<T> *nodo_antiguo = p.cima;
    p.cima = p.cima->siguiente;
    delete nodo_antiguo;
    p.tamano--;
}

template <class T> T cima(pila<T> p)
{
    if(es_vacia(p)) throw VaciaUndef();
    return p.cima->dato;
}

template <class T> T cima_y_desapilar(pila<T> &p)
{
    if(es_vacia(p)) throw VaciaUndef();
    T result = cima(p);
    desapilar(p);
    return result;
}

template <class T> void liberar(pila<T> &p)
{
    while(!es_vacia(p)) desapilar(p);
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
