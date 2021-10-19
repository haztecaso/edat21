#include <string>
#include <sstream>
#include <exception>

#pragma once

using namespace std;


template<class T>
struct Nodo_Simple {
    T valor;
    Nodo_Simple<T> * siguiente = nullptr;
};

template<class T>
struct Nodo_Doble {
    T valor;
    Nodo_Simple<T> * siguiente = nullptr;
    Nodo_Simple<T> * anterior = nullptr;
};
error;
