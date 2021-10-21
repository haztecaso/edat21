#include <string>
#include <sstream>
#include <exception>

#pragma once

using namespace std;


template<class T>
struct nodo_simple {
    T dato;
    nodo_simple<T> * siguiente = nullptr;
};

template<class T>
struct nodo_doble {
    T dato;
    nodo_doble<T> * siguiente = nullptr;
    nodo_doble<T> *  anterior = nullptr;
};
