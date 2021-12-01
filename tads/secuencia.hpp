#include <sstream>
#include "basicos.hpp"

using namespace std;

const string FLECHA = "↓";

template <typename T>
struct secuencia {
    nodo_simple<T> * primero; // puntero al anterior al primero
    nodo_simple<T> * anterior; // puntero al anterior al actual
};

// Reserva memoria para una secuencia vacia
template <typename T> secuencia<T> crear_secuencia();

// Inserta un elemento en la posición actual
template <typename T> void insertar(secuencia<T>& s, T e);

// Elimina el elemento de la posición actual
template <typename T> void eliminar(secuencia<T>& s);

// Devuelve el nodo actual
template <typename T> nodo_simple<T> * nodo_actual(const secuencia<T>& s);

// Devuelve el valor del nodo actual
template <typename T> T valor_actual(const secuencia<T>& s);

// Avanza en una posición del valor actual
template <typename T> void avanzar(secuencia<T>& s);

// Reinicia el valor actual al primero
template <typename T> void reiniciar(secuencia<T>& s);

// Devuelve el primer nodo de una secuencia
template <typename T> nodo_simple<T> *primero(secuencia<T> s);

// Devuelve el último nodo de una secuencia
template <typename T> nodo_simple<T> *ultimo(secuencia<T> s);

// Determina si se ha alcanzado el final de una secuencia
template <typename T> bool fin(secuencia<T> s);

// Sobrecarga del operador << para imprimir una secuencia
template <typename T> ostream& operator<<(ostream& os, secuencia<T> s);

/*
 * IMPLEMENTACIONES
 */

template <typename T> secuencia<T> crear_secuencia()
{
    secuencia<T> s;
    s.primero = new nodo_simple<T>;
    s.anterior = s.primero;
    return s;
}

template <typename T> void insertar(secuencia<T>& s, T e)
{
    nodo_simple<T> * nodo_nuevo = crear_nodo_simple(e, s.anterior->siguiente);
    s.anterior->siguiente = nodo_nuevo;
    s.anterior = nodo_nuevo;
}

template <typename T> void eliminar(secuencia<T>& s)
{
    if(!fin(s)){
        nodo_simple<T> * tmp = s.anterior->siguiente;
        s.anterior->siguiente = tmp->siguiente;
        delete tmp;
    }
    else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> nodo_simple<T> * nodo_actual(const secuencia<T>& s)
{
    if(!fin(s)){
        return s.anterior->siguiente;
    }
    else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> T valor_actual(const secuencia<T>& s)
{
    if(!fin(s)){
        return s.anterior->siguiente->dato;
    }
    else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> void avanzar(secuencia<T>& s)
{
    if(!fin(s)){
        s.anterior = s.anterior->siguiente;
    }
    else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> void reiniciar(secuencia<T>& s)
{
    s.anterior = s.primero;
}

template <typename T> nodo_simple<T> *primero(secuencia<T> s)
{
    return s.primero->siguiente;
}

template<class T> nodo_simple<T> *ultimo(secuencia<T> s){
    reiniciar(s);
    nodo_simple<T> *result = nullptr;
    while(!fin(s)){
        result = nodo_actual(s);
        avanzar(s);
    }
    return result;
}


template <typename T> bool fin(secuencia<T> s)
{
    return s.anterior->siguiente == NULL;
}

template <typename T> ostream& operator<<(ostream& os, secuencia<T> s)
{
    nodo_simple<T> * aux = s.primero;
    while(aux->siguiente != NULL){
        if(aux == s.anterior){
            os << FLECHA;
        }
        os << aux->siguiente->dato << " ";
        aux = aux->siguiente;
    }
    return os;
}
