/*
 * TADS Básicos - Útiles para definir nuevos TADS
 *
 * Jorge González Gutiérrez
 * Adrián Lattes Grassi
 * Fernando Montero Erustes
 *
 */

#pragma once

using namespace std;

// Constantes
const int CAP_INIC = 16;
const int MULT_CRECIMIENTO = 2;

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
    nodo_doble<T> * siguiente = nullptr;
    nodo_doble<T> *  anterior = nullptr;
};

// Función para crear e inicializar un nuevo nodo simple dado un dato y un nodo siguiente.
template <class T> nodo_simple<T> * crear_nodo_simple(T d, nodo_simple<T> * s);

// Función para crear e inicializar un nuevo nodo simple dado un dato y sin un
// nodo siguiente (inicializado con nullptr)
template <class T> nodo_simple<T> * crear_nodo_simple(T d);

/*
 * IMPLEMENTACIONES
 */

template <class T> nodo_simple<T> * crear_nodo_simple(T d, nodo_simple<T> * s)
{
    nodo_simple<T> *nodo = new nodo_simple<T>;
    nodo->dato = d;
    nodo->siguiente= s;
    return nodo;
}

template <class T> nodo_simple<T> * crear_nodo_simple(T d)
{
    nodo_simple<T> *nodo = new nodo_simple<T>;
    nodo->dato = d;
    return nodo;
}
