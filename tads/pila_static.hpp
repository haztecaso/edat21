/*
 * Pilas - Implementación estática
 *
 * Jorge González Gutiérrez
 * Adrián Lattes Grassi
 * Fernando Montero Erustes
 *
 */

#include <string>
#include <sstream>
#include <exception>
#include "basicos.hpp"
#pragma once

using namespace std;

// Definición del tipo para las pilas
// Los valores por defecto corresponden con la representación de una pila vacía
template<class T>
struct pila {
    int capacidad = CAP_INIC;
    int tamano = 0;
    T *datos = new T[CAP_INIC];
};

// Excepción que lanzan las operaciones parciales que no están definidas para las colas vacías
struct PilaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las pilas vacías";
    }
};

// Determina si una pila está vacía
template<class T> bool es_vacia(pila<T> p);

// Devuelve el tamaño de una pila
template <class T> int tamano(pila<T> p);

// Duplica el tamaño del array de datos de una pila
template <class T> void ampliar_memoria(pila<T> &p);

// Añade un elemento en la cima de una pila
template<class T> void apilar(pila<T> &p, T dato);

// Elimina la cima de una pila
// Función parcial: lanza una excepción PilaVaciaUndef si la pila es vacía 
template<class T> void desapilar(pila<T> &p);

// Devuelve la cima de una pila (sin sacarla de la pila)
// Función parcial: lanza una excepción PilaVaciaUndef si la pila es vacía 
template <class T> T cima(pila<T> p);

// Devuelve y elimina la cima de una pila
// Función parcial: lanza una excepción PilaVaciaUndef si la pila es vacía 
template <class T> T cima_y_desapilar(pila<T> &p);

// Libera la memoria de una pila
template <class T> void liberar(pila<T> &p);

// Sobrecarga del operador << para imprimir las pilas por pantalla
template <class T> ostream& operator<<(ostream& os, pila<T> p);

// Sobrecarga del operador << para imprimir punteros a pilas por pantalla
template <class T> ostream& operator<<(ostream& os, pila<T> *p);

/*
 * IMPLEMENTACIONES
 */

template <class T> bool es_vacia(pila<T> p)
{
    return tamano(p) == 0;
}

template <class T> void ampliar_memoria(pila<T> &p)
{
    T *datos = new T[p.capacidad * MULT_CRECIMIENTO];
    for(int i = 0; i < p.tamano; i++) // Hay alguna manera mejor de hacer esta copia?
    {
        datos[i] = p.datos[i];
    }
    delete[] p.datos;
    p.datos = datos;
    p.capacidad *= MULT_CRECIMIENTO;
}

template <class T> void apilar(pila<T> &p, T dato)
{
    if(p.tamano== p.capacidad)
        ampliar_memoria(p);
    p.datos[p.tamano] = dato;
    p.tamano++;
}

template <class T> void desapilar(pila<T> &p)
{
    if(es_vacia(p)) throw PilaVaciaUndef();
    p.tamano--;
}

template <class T> T cima(pila<T> p)
{
    if(es_vacia(p)) throw PilaVaciaUndef();
    return p.datos[p.tamano - 1];
}

template <class T> T cima_y_desapilar(pila<T> &p)
{
    if(es_vacia(p)) throw PilaVaciaUndef();
    T result = cima(p);
    desapilar(p);
    return result;
}

template <class T> int tamano(pila<T> p)
{
    return p.tamano;
}

template <class T> void liberar(pila<T> &p)
{
    if(p.datos) delete[] p.datos;
    pila<T> nueva;
    p = nueva;;
}

template <class T> ostream& operator<<(ostream& os, pila<T> p)
{
    os << "[";
    for(int i = p.tamano - 1; i >= 0; i--)
    {
        os << p.datos[i];
        if (i > 0) os << " ";
    }
    os << "]";
    return os;
}

template <class T> ostream& operator<<(ostream& os, pila<T> *p)
{
    os << "*" << *p;
    return os;
}
