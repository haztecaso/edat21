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
#include <vector>
#include "basicos.hpp"

/* STRUCTS Y TIPOS */

template<class T> using abb = nodo_doble<T> *;

/* CABECERAS (SIGNATURAS) */

// Función para crear un abb vacío
template<class T> abb<T> abb_vacio();

// Función determinar si un abb es vacío
template<class T> bool es_abb_vacio(abb<T> a);

// Determina si un elemento está en un abb
template<class T> bool esta(abb<T> &a, T e);

// Inserta un elemento en un abb
template<class T> void insertar(abb<T> &a, T e);

// Elimina un elemento de un abb
template<class T> void eliminar(abb<T> &a, T e);

// Recorrido inorden de un abb. Se guarda en una lista que se debe pasar en el
// segundo parámetro.
template<class T> void inorden(abb<T> a, std::vector<T> &result);


// Funciones para generar gráficos de los ABB's
template<class T> void abb_graphviz(std::ostream &os, abb<T> a);
template<class T> void abb_graphviz(std::string filename, abb<T> a);

/* IMPLEMENTACIONES */

template<class T> abb<T> abb_vacio(){
    return (abb<T>) nullptr;
}

template<class T> bool es_abb_vacio(abb<T> a){
    return a == nullptr;
}

template<class T> bool esta(abb<T> &a, T e){
    if(es_abb_vacio(a)) return false;
    else if(a->dato == e) return true;
    else return a->dato <= e ? esta(a->dr, e) : esta(a->iz, e);
}

template<class T> void insertar(abb<T> &a, T e){
    if(es_abb_vacio(a)){
        nodo_doble<T> * nodo_null = nullptr;
        a = crear_nodo_doble(e, nodo_null, nodo_null);
    }
    else{
        insertar((a->dato <= e) ? a->dr : a->iz, e);
    }
}

template<class T> void eliminar(abb<T> &a, T e){
    abb<T> b;
    if(!es_abb_vacio(a)){
        if(a->dato == e){
            if(es_abb_vacio(a->dr)){
                b = a;
                a = a->iz;
                delete b;
            }
            else if(es_abb_vacio(a->iz)){
                b = a;
                a = a->dr;
                delete b;
            }
            else{
                //TODO
            }
        }
        else if(e <= a->valor){
            eliminar(a->dr);
        }
        else if(e <= a->valor){
            eliminar(a->iz);
        }
    }
}

template<class T> void inorden(abb<T> a, std::vector<T> &result){
    if(!es_abb_vacio(a)){
    inorden(a->iz, result);
    result.push_back(a->dato);
    inorden(a->dr, result);
    }
}

const std::string sep = "    ";
const std::string nname = "abb_node";

template<class T> void subtree_graphviz(std::ostream &os, std::string id, abb<T> a){
    if(es_abb_vacio(a)){
        os << sep << nname << id << " [label = \" \", style = invis];\n";
    } else {
        os << sep << nname << id << " [label = \"" << a->dato << "\"];\n";
        os << sep << nname << id << " -> " << nname << id << "i;\n";
        subtree_graphviz(os, id + "i", a->iz);
        os << sep << nname << id << " -> " << nname << id << "d;\n";
        subtree_graphviz(os, id + "d", a->dr);
    }
}

template<class T> void abb_graphviz(std::ostream &os, abb<T> a){
    os << "digraph ABB {\n";
    os << sep << "node [shape = circle]\n";
    subtree_graphviz(os, "", a);
    os << "}\n";
}

template<class T> void abb_graphviz(std::string filename, abb<T> a){
    std::ofstream file;
    file.open(filename);
    abb_graphviz(file, a);
    file.close();
}
