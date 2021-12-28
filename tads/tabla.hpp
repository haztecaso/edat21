/*
 * Tabla
 */

#pragma once
#include <sstream>
#include <cstddef>
#include <vector>
#include <fstream>
#include "abb.hpp"

/* STRUCTS Y TIPOS */

// Definición del tipo para las entradas de las tablas
// - El tipo K debe tener definidos los operadores == y <=
// - El tipo V debe tener definida una función V combinar(V v1, V v2)
template <class K, class V> struct entrada {
    K clave;
    V valor;
};

// Definición del tipo de las tablas (mediante árboles binarios)
template <class K, class V> using tabla = abb<entrada<K,V>>;

// Tabla de frecuencias (valores de tipo int)
template <class K> using tabla_frecuencias = tabla<K,int>;

// Excepción para ser lanzada cuando no se ha encontrado una clave en una tabla
struct ClaveNoEncontrada: public std::exception {
    const char * what () const throw ()
    {
        return "La clave no ha sido encontrada en la tabla";
    }
};

/* CABECERAS (SIGNATURAS) */

// Compara (menor o igual) dos entradas por claves
template <class K, class V> bool operator<=(entrada<K,V> e1, entrada<K,V> e2);

// Compara (igualdad) dos entradas por claves
template <class K, class V> bool operator==(entrada<K,V> e1, entrada<K,V> e2);

// Operador << para entradas
template <class K, class V> std::ostream& operator<<(std::ostream& os, entrada<K,V> e);

// Crea una tabla vacía
template <class K, class V> tabla<K,V> tabla_vacia();

// Crea una tabla de frecuencias vacía
template <class K> tabla_frecuencias<K> tabla_frecuencias_vacia();

// Determina si una tabla está vacía
template <class K, class V> bool es_tabla_vacia(tabla<K,V> t);

// Determina si una clave está en la tabla
template <class K, class V> bool esta_clave(tabla<K,V> t, K clave);

// Cosulta el valor de una clave.
// Función parcial: si la clave no está en la tabla se lanza la excepción ClaveNoEncontrada
template <class K, class V> V consultar(tabla<K,V> t, K clave);

// Función combinar para enteros
template <class V> V combinar(V a, V b);

// Función combinar para enteros
int combinar(int a, int b);

// Función combinar para codigos binarios
std::vector<bool> combinar(std::vector<bool>, std::vector<bool>);

// Añade una clave y valor (que forman una entrada) a una tabla
template <class K, class V> void aniadir(tabla<K,V> &t, K clave, V valor);

// Añade una entrada a una tabla
template <class K, class V> void aniadir(tabla<K,V> &t, entrada<K,V> e);

// Dada una clave elimina la entrada correspondiente de la tabla
// Función parcial: si la clave no está en la tabla se lanza la excepción ClaveNoEncontrada
template <class K, class V> void eliminar(tabla<K,V> t, K clave);

template <class K, class V> std::ostream& operator<<(std::ostream& os, tabla<K,V> t);

// Devuelve una tabla de frecuencias de los caracteres de un texto.
tabla_frecuencias<char> frecuencias_char(std::string texto);

/* IMPLEMENTACIONES */

template <class K, class V> bool operator<=(entrada<K,V> e1, entrada<K,V> e2){
    return e1.clave <= e2.clave;
}

template <class K, class V> bool operator==(entrada<K,V> e1, entrada<K,V> e2){
    return e1.clave == e2.clave;
}

template <class K, class V> std::ostream& operator<<(std::ostream& os, entrada<K,V> e){
    os <<"(" << e.clave << ", " << e.valor << ")";
    return os;
}

template <class K, class V> tabla<K,V> tabla_vacia(){
    return abb_vacio<entrada<K,V>>();
}

template <class K> tabla_frecuencias<K> tabla_frecuencias_vacia(){
    return tabla_vacia<K, int>();
}

template <class K, class V> bool es_tabla_vacia(tabla<K,V> t){
    return t == nullptr;
}

template <class K, class V> bool esta_clave(tabla<K,V> t, K clave){
    entrada<K,V> e;
    e.clave = clave;
    return esta(t, e);
}

template <class K, class V> tabla<K,V> consultar_nodo(tabla<K,V> t, K clave){
    if(es_tabla_vacia(t)) throw ClaveNoEncontrada();
    else if(t->dato.clave == clave){
        return t;
    }
    else return (t->dato.clave <= clave)
        ? consultar_nodo(t->dr, clave)
        : consultar_nodo(t->iz, clave);
}

template <class K, class V> V consultar(tabla<K,V> t, K clave){
    return consultar_nodo(t, clave)->dato.valor;
}

int combinar(int a, int b){
    return a + b;
}

std::vector<bool> combinar(std::vector<bool>, std::vector<bool>){
    throw std::runtime_error("Un caracter nopuede tener varios códigos");
}

template <class K, class V> void aniadir(tabla<K,V> &t, K clave, V valor){
    if(!esta_clave(t, clave)){
        entrada<K,V> e;
        e.clave = clave;
        e.valor = valor;
        insertar(t, e);
    }
    else {
        tabla<K,V> nodo = consultar_nodo(t, clave);
        nodo->dato.valor = combinar(nodo->dato.valor, valor);
    }
}

template <class K, class V> void aniadir(tabla<K,V> &t, entrada<K,V> e){
    aniadir(t, e.clave, e.valor);
}

template <class K, class V> void eliminar(tabla<K,V> t, K clave){
    //TODO
}

template <class K, class V> std::ostream& operator<<(std::ostream& os, tabla<K,V> t){
    std::vector<entrada<K,V>> v;
    inorden(t, v);
    for(entrada<K,V> e:v) os << e << "\n";
    return os;
}

tabla_frecuencias<char> frecuencias_char(std::string texto){
    tabla_frecuencias<char> tabla = tabla_frecuencias_vacia<char>();
    for (char const &c: texto){
        aniadir(tabla, c, 1);
    }
    return tabla;
}
