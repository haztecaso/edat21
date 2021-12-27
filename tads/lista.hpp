/*
 * Listas - Implementación dinámica
 *
 * Jorge González Gutiérrez
 * Adrián Lattes Grassi
 * Fernando Montero Erustes
 *
 */

#pragma once
#include <sstream>
#include "basicos.hpp"

// Definición del tipo para las listas
// Los valores por defecto corresponden con la representación de una lista vacía
template<class T> struct lista {
    nodo_doble<T> *primero = nullptr;
    nodo_doble<T> *ultimo  = nullptr;
    int tamano = 0;
};

// Determina si una lista es vacía
template <class T> bool es_vacia(lista<T> l);

// Devuelve el tamaño de una lista
template <class T> int tamano(lista<T> l);

// Crea una lista con un elemento
template <class T> lista<T> unitaria(T d);

// Añade un elemento por la izquierda (al inicio) de una lista
template <class T> void insertar_inicio(lista<T> &l, T d);

// Añade un elemento por la derecha (al final) de una lista
template <class T> void insertar_final(lista<T> &l, T d);

// Elimina el elemento de la izquierda (el primero) de una lista
// Función parcial: lanza una excepción VaciaUndef si la lista es vacía
template <class T> void eliminar_inicio(lista<T> &l);

// Elimina el elemento de la derecha (el último) de una lista
// Función parcial: lanza una excepción VaciaUndef si la lista es vacía
template <class T> void eliminar_final(lista<T> &l);

// Devuelve el elemento de la izquierda (el primero) de una lista (sin sacarlo de la lista)
// Función parcial: lanza una excepción VaciaUndef si la cola es vacía
template <class T> T primero(lista<T> l);

// Devuelve el elemento de la derecha (el último) de una lista (sin sacarlo de la lista)
// Función parcial: lanza una excepción VaciaUndef si la cola es vacía
template <class T> T ultimo(lista<T> l);

// Libera la memoria de una lista
template <class T> void liberar(lista<T> &l);

// Ordena una lista utilizando un abb y el recorrido en inorden
template <class T> void treesort(lista<T> &l);

// Sobrecarga del operador << para imprimir una lista
template <class T> std::ostream& operator<<(std::ostream& os, lista<T> l);

/*
 * IMPLEMENTACIONES
 */

template <class T> bool es_vacia(lista<T> l){
    return tamano(l) == 0;
}

template <class T> int tamano(lista<T> l){
    return l.tamano;
}

template <class T> lista<T> unitaria(T d){
    nodo_doble<T> * nodo_null = nullptr;
    nodo_doble<T> * nodo = crear_nodo_doble(d, nodo_null, nodo_null);
    lista<T> l;
    l.primero = nodo;
    l.ultimo = nodo;
    l.tamano = 1;
    return l;
}

template <class T> void insertar_inicio(lista<T> &l, T d){
    nodo_doble<T> * nodo_null = nullptr;
    nodo_doble<T> * nuevo = crear_nodo_doble(d, nodo_null, l.primero);
    if(es_vacia(l)){
        l.ultimo = nuevo;
    } else {
        l.primero->iz = nuevo;
    }
    l.primero = nuevo;
    l.tamano++;
}

template <class T> void insertar_final(lista<T> &l, T d){
    nodo_doble<T> * nodo_null = nullptr;
    nodo_doble<T> * nuevo = crear_nodo_doble(d, l.ultimo, nodo_null);
    if(es_vacia(l)){
        l.primero = nuevo;
    } else {
        l.ultimo->dr = nuevo;
    }
    l.ultimo = nuevo;
    l.tamano++;
}

template <class T> void eliminar_inicio(lista<T> &l){
    if(es_vacia(l)) throw VaciaUndef();
    nodo_doble<T> * primero = l.primero;
    l.primero = l.primero->dr;
    if (l.primero == nullptr){
        l.ultimo = nullptr;
    } else {
        l.primero->iz = nullptr;
    }
    l.tamano--;
    delete primero;
}

template <class T> void eliminar_final(lista<T> &l){
    if(es_vacia(l)) throw VaciaUndef();
    nodo_doble<T> * ultimo = l.ultimo;
    l.ultimo = l.ultimo->iz;
    if (l.ultimo == nullptr){
        l.primero = nullptr;
    } else {
        l.ultimo->dr = nullptr;
    }
    l.tamano--;
    delete ultimo;
}

template <class T> T primero(lista<T> l){
    if(es_vacia(l)) throw VaciaUndef();
    return l.primero->dato;
}

template <class T> T ultimo(lista<T> l){
    if(es_vacia(l)) throw VaciaUndef();
    return l.ultimo->dato;
}

template <class T> void liberar(lista<T> &l){
    nodo_doble<T> *nodo_actual = l.primero;
    nodo_doble<T> *nodo_tmp;
    while(nodo_actual != nullptr){
        nodo_tmp = nodo_actual->dr;
        delete nodo_actual;
        nodo_actual = nodo_tmp;
    }
    l.primero = nullptr;
    l.ultimo = nullptr;
    l.tamano = 0;
}


// Necesario para que el compilador sepa lo que es un abb sin tener que incluir "abb.hpp" (y por tanto hacer inclusiones recursivas :()
template<class T> using abb = nodo_doble<T> *;

template <class T> void treesort(lista<T> &l){
    abb<T> arbol = nullptr;
    while(!es_vacia(l)){
        insertar(arbol, primero(l));
        eliminar_inicio(l);
    }
    inorden(arbol, l);
}

template <class T> std::ostream& operator<<(std::ostream& os, lista<T> l){
    os << "[";
    nodo_doble<T> *nodo_actual = l.primero;
    while (nodo_actual != nullptr)
    {
        os << nodo_actual->dato;
        if (nodo_actual != l.ultimo)
            os << " ";
        nodo_actual = nodo_actual->dr;
    }
    os << "]";
    return os;
}
