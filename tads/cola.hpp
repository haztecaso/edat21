#include <string>
#include <sstream>
#include <exception>

#include "./basicos.hpp"

#pragma once

using namespace std;

template<class T>
struct Cola {
    Nodo_Simple<T> *primero = nullptr;
    Nodo_Simple<T> *ultimo  = nullptr;
    int tamano = 0;
};

template <class T> bool es_vacia(Cola<T> cola);
template <class T> void pedir_vez(Cola<T> &cola, T valor);
template <class T> void avanzar(Cola<T> &cola);
template <class T> T primero(Cola<T> cola);
template <class T> int tamano(Cola<T> cola);
template <class T> std::ostream& operator<<(std::ostream& os, Cola<T> cola);
template <class T> std::ostream& operator<<(std::ostream& os, Cola<T> *cola);

struct ColaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las colas vacías.";
    }
};

// Implementaciones

template <class T> bool es_vacia(Cola<T> cola)
{
    return cola.tamano == 0;
}

template <class T> void pedir_vez(Cola<T> &cola, T valor)
{
    if (es_vacia(cola))
    {
        cola = *(new Cola<T>);
        cola.primero = new Nodo_Simple<T>;
        cola.ultimo = cola.primero;
    }
    else
    {
        Nodo_Simple<T> *nodo_nuevo = new Nodo_Simple<T>;
        cola.ultimo->siguiente = nodo_nuevo;
        cola.ultimo = nodo_nuevo;
    }
        cola.ultimo->valor = valor;
        cola.tamano++;
}

template <class T> void avanzar(Cola<T> &cola)
{
    if(!es_vacia(cola))
    {
        Nodo_Simple<T> *nodo_antiguo = cola.primero;
        cola.primero = cola.primero->siguiente;
        delete nodo_antiguo;
        cola.tamano--;
    }
    else
        throw ColaVaciaUndef();
}

template <class T> T primero(Cola<T> cola)
{
    if(!es_vacia(cola))
        return cola.primero->valor;
    else
        throw ColaVaciaUndef();
}

template <class T> int tamano(Cola<T> cola)
{
    return cola.tamano;
}

template <class T> std::ostream& operator<<(std::ostream& os, Cola<T> cola)
{
    os << "[";
    Nodo_Simple<T> *nodo_actual = cola.primero;
    while (nodo_actual != nullptr)
    {
        os << nodo_actual->valor;
        if (nodo_actual != cola.ultimo)
            os << " ";
        nodo_actual = nodo_actual->siguiente;
    }
    os << "]";
    return os;
}

template <class T> std::ostream& operator<<(std::ostream& os, Cola<T> *cola)
{
    os << *cola;
    return os;
}
