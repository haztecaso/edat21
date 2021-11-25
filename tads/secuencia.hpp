#include <sstream>
#include "basicos.hpp"

using namespace std;

const string FLECHA = "↓";

template <typename T>
struct secuencia {
    nodo_simple<T> * primero;
    nodo_simple<T> * anterior; //puntero al anterior al actual
};

template <typename T> secuencia<T> crear();
template <typename T> void insertar(secuencia<T>& s, T e);
template <typename T> void eliminar(secuencia<T>& s);
template <typename T> T actual(const secuencia<T>& s);
template <typename T> void avanzar(secuencia<T>& s);
template <typename T> void reiniciar(secuencia<T>& s);
template <typename T> bool fin(secuencia<T> s);
template <typename T> ostream& operator<<(ostream& os, secuencia<T> s);

/*
 * IMPLEMENTACIONES
 */

template <typename T> secuencia<T> crear()
{
    secuencia<T> s;
    s.primero = new nodo_simple<T>;
    s.anterior = s.primero;
    return s;
}

template <typename T> void insertar(secuencia<T>& s, T e)
{
    nodo_simple<T> * new_node = new nodo_simple<T>;
    new_node->dato = e;
    new_node->siguiente = s.anterior->siguiente;
    s.anterior->siguiente = new_node;
    s.anterior = new_node;
}

template <typename T> void eliminar(secuencia<T>& s)
{
    if(!fin(s)){
        nodo_simple<T> * aux = s.anterior->siguiente;
        s.anterior->siguiente = aux->siguiente;
        delete aux;
    }
    else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> T actual(const secuencia<T>& s)
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
