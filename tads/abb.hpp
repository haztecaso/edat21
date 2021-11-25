/*
 * Árboles binarios de búsqueda
 *
 * Jorge González Gutiérrez
 * Adrián Lattes Grassi
 * Fernando Montero Erustes
 *
 */

#pragma once
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <string>

#include "basicos.hpp"
#include "lista.hpp"

using namespace std;

template<class T>
using abb = nodo_doble<T> *;

// Función para crear un abb vacío
template<class T> abb<T> abb_vacio();

// Función determinar si un abb es vacío
template<class T> bool es_abb_vacio(abb<T> a);

// Función para insertar un elemento en un abb
template<class T> void insertar(abb<T> &a, T e);

// Recorrido inorden de un abb. Se guarda en una lista que se debe pasar en el
// segundo parámetro.
template<class T> void inorden(abb<T> a, lista<T> &result);

template<class T> void abb_graphviz(ostream &os, abb<T> a);
template<class T> void abb_graphviz(string filename, abb<T> a);


/*
 * IMPLEMENTACIONES
 */

template<class T> abb<T> abb_vacio(){
    return (abb<T>) nullptr;
}

template<class T> bool es_abb_vacio(abb<T> a){
    return a == nullptr;
}

template<class T> void insertar(abb<T> &a, T e){
    if(es_abb_vacio(a)){
        nodo_doble<T> * nodo_null = nullptr;
        a = crear_nodo_doble(e, nodo_null, nodo_null);
    }
    else{
        insertar((a->dato > e) ? a->iz : a->dr, e);
    }
}

template<class T> void inorden(abb<T> a, lista<T> &result){
    if(!es_abb_vacio(a)){
    inorden(a->iz, result);
    insertar_final(result, a->dato);
    inorden(a->dr, result);
    }
}

const string sep = "    ";
const string nname = "abb_node";

template<class T> void subtree_graphviz(ostream &os, string id, abb<T> a){
    if(es_abb_vacio(a)){
        os << sep << nname << id << " [label = \" \", style = invis];" << endl;
    } else {
        os << sep << nname << id << " [label = " << a->dato << "];" << endl;
        os << sep << nname << id << " -> " << nname << id << "i;" << endl;
        subtree_graphviz(os, id + "i", a->iz);
        os << sep << nname << id << " -> " << nname << id << "d;" << endl;
        subtree_graphviz(os, id + "d", a->dr);
    }
}

template<class T> void abb_graphviz(ostream &os, abb<T> a){
    os << "digraph ABB {" << endl;
    os << sep << "node [shape = circle]" << endl;
    subtree_graphviz(os, "", a);
    os << "}" << endl;
}

template<class T> void abb_graphviz(string filename, abb<T> a){
    ofstream file;
    file.open(filename);
    abb_graphviz(file, a);
    file.close();
}
