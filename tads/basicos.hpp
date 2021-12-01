/*
 * TADS Básicos - Útiles para definir nuevos TADS
 *
 * Jorge González Gutiérrez
 * Adrián Lattes Grassi
 * Fernando Montero Erustes
 *
 */

#pragma once
#include <exception>

using namespace std;

// Constantes
const int CAP_INIC = 16;
const int MULT_CRECIMIENTO = 2;

// Excepción que lanzan las operaciones parciales que no están definidas para estructuras de datos vacías
struct VaciaUndef: public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para estructuras vacías.";
    }
};

// Nodos simples
template<class T>
struct nodo_simple {
    T dato;
    nodo_simple<T> * siguiente = nullptr;
};

// Nodos dobles (enlazados)
template<class T>
struct nodo_doble {
    T dato;
    nodo_doble<T> * iz = nullptr;
    nodo_doble<T> * dr = nullptr;
};

// Crear e inicializa un nuevo nodo simple dado un dato y un nodo siguiente.
template <class T> nodo_simple<T> * crear_nodo_simple(T d, nodo_simple<T> * s);

// Crea e inicializa un nuevo nodo doble dado un dato y los punteros a los nodos iz y dr.
template <class T> nodo_doble<T> * crear_nodo_doble(T d, nodo_doble<T>* iz, nodo_doble<T>* dr);

// Intercambia los valores de dos nodos simples
template <class T> void intercambiar(nodo_simple<T> *a, nodo_simple<T> *b);

// Intercambia los valores de dos nodos dobles
template <class T> void intercambiar(nodo_doble<T> *a, nodo_doble<T> *b);

/*
 * IMPLEMENTACIONES
 */

template <class T> nodo_simple<T> * crear_nodo_simple(T d, nodo_simple<T> * s)
{
    nodo_simple<T> *nodo = new nodo_simple<T>;
    nodo->dato = d;
    nodo->siguiente = s;
    return nodo;
}

template <class T> nodo_doble<T> * crear_nodo_doble(T d, nodo_doble<T>* iz, nodo_doble<T>* dr)
{
    nodo_doble<T> *nodo = new nodo_doble<T>;
    nodo->dato = d;
    nodo->iz = iz;
    nodo->dr = dr;
    return nodo;
}

template <class T> void intercambiar(nodo_simple<T> *a, nodo_simple<T> *b)
{
    const T tmp = a->dato;
    a->dato = b->dato;
    b->dato = tmp;
}

template <class T> void intercambiar(nodo_doble<T> *a, nodo_doble<T> *b)
{
    const T tmp = a->dato;
    a->dato = b->dato;
    b->dato = tmp;
}
