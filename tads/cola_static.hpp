/*
 * Colas - Implementación estática 
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
// Representación de las colas mediante arrays circulares.
// Los valores por defecto corresponden con la representación de una cola vacía
template<class T>
struct cola {
    T *datos = new T[CAP_INIC];
    int primero = 1;
    int ultimo = 0;
    int tamano = 0;
    int capacidad = CAP_INIC;
};

// Determina si una cola es vacía
template <class T> bool es_vacia(cola<T> c);

// Devuelve el tamaño de una cola
template <class T> int tamano(cola<T> c);

// Duplica el tamaño del array de datos de una cola 
// Para esto se copian los datos al inicio de un nuevo array y se borra el antiguo
template <class T> void ampliar_memoria(cola<T> &c);

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

// Sobrecarga del operador << para imprimir las colas
template <class T> std::ostream& operator<<(std::ostream& os, cola<T> c);

// Sobrecarga del operador << para imprimir punteros a colas
template <class T> std::ostream& operator<<(std::ostream& os, cola<T> *c);

/*
 * IMPLEMENTACIONES
 */

template<class T> bool es_vacia(cola<T> c)
{
    return tamano(c) == 0;
}

template<class T> int tamano(cola<T> c)
{
    return c.tamano;
}

template<class T> void ampliar_memoria(cola<T> &c)
{
    T *datos_nuevos = new T[c.capacidad * MULT_CRECIMIENTO];
    for(int i = 0; i < c.tamano ; i++){
       datos_nuevos[i] = c.datos[(c.primero+i) % c.capacidad];
    }
    c.primero = 0;
    c.ultimo = c.tamano - 1;
    c.capacidad *= MULT_CRECIMIENTO;
    delete[] c.datos;
    c.datos = datos_nuevos;
}

template<class T> void encolar(cola<T> &c, T e){
    if(c.tamano >= c.capacidad)
    {
        ampliar_memoria(c);
    }
    c.ultimo = (c.ultimo + 1) % c.capacidad;
    c.datos[c.ultimo] = e;
    c.tamano++;
}

template<class T> void desencolar(cola<T> & c){
    if(es_vacia(c)) throw VaciaUndef();
    c.primero = (c.primero + 1) % c.capacidad;
    c.tamano--;
}

template<class T> T primero(cola<T> c){
    if(es_vacia(c)) throw VaciaUndef();
    return c.datos[c.primero];
}

template<class T> void liberar(cola<T> &c)
{
    delete[] c.datos;
    c.tamano = 0;
    c.primero = 1;
    c.ultimo = 0;
    c.capacidad = 0;
}

template<class T> std::ostream& operator<<(std::ostream& os, cola<T> c)
{
    os << "[";
    for(int i = 0; i < c.tamano ; i++){
       os << c.datos[(c.primero+i) % c.capacidad];
       if (i < c.tamano - 1) os << " ";
       }
    os << "]";
    return os;
}

template<class T> std::ostream& operator<<(std::ostream& os, cola<T> *c)
{
    os << "*" << c;
    return os;
}
