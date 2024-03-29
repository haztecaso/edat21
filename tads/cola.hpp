/*
 * Colas - Implementación dinámica
 *
 * Jorge González Gutiérrez
 * Adrián Lattes Grassi
 * Fernando Montero Erustes
 *
 */

#pragma once
#include <sstream>
#include "basicos.hpp"

// Definición del tipo para las colas
// Los valores por defecto corresponden con la representación de una cola vacía
template<class T>
struct cola {
    nodo_simple<T> *primero = nullptr;
    nodo_simple<T> *ultimo  = nullptr;
    int tamano = 0;
};

// Determina si una cola es vacía
template <class T> bool es_vacia(cola<T> c);

// Devuelve el tamaño de una cola
template <class T> int tamano(cola<T> c);

// Añade un elemento al final de una cola
template <class T> void encolar(cola<T> &c, T d);

// Elimina el primer elemento de una cola
// Función parcial: lanza una excepción VaciaUndef si la cola es vacía 
template <class T> void desencolar(cola<T> &c);

// Devuelve el primer elemento de una cola (sin sacarlo de la cola)
// Función parcial: lanza una excepción VaciaUndef si la cola es vacía 
template <class T> T primero(cola<T> c);

// Libera la memoria de una cola
template <class T> void liberar(cola<T> &c);

// Sobrecarga del operador << para imprimir una cola
template <class T> std::ostream& operator<<(std::ostream& os, cola<T> c);

// Sobrecarga del operador << para imprimir un puntero a una cola
template <class T> std::ostream& operator<<(std::ostream& os, cola<T> *c);

/*
 * IMPLEMENTACIONES
 */

template <class T> bool es_vacia(cola<T> c)
{
    return tamano(c) == 0;
}

template <class T> int tamano(cola<T> c)
{
    return c.tamano;
}

template <class T> void encolar(cola<T> &c, T d)
{
    nodo_simple<T> *nodo_null = nullptr;
    nodo_simple<T> *nodo = crear_nodo_simple(d, nodo_null);
    if (es_vacia(c))
    {
        c.primero = nodo;
    }
    else
    {
        c.ultimo->siguiente = nodo;
    }
    c.ultimo = nodo;
    c.tamano++;
}

template <class T> void desencolar(cola<T> &c)
{
    if(es_vacia(c)) throw VaciaUndef();
    nodo_simple<T> *nodo_antiguo = c.primero;
    c.primero = c.primero->siguiente;
    if (c.primero == nullptr) c.ultimo = nullptr;
    delete nodo_antiguo;
    c.tamano--;
}

template <class T> T primero(cola<T> c)
{
    if(es_vacia(c)) throw VaciaUndef();
    return c.primero->dato;
}

template <class T> void liberar(cola<T> &c)
{
    while(!es_vacia(c)) desencolar(c);
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
