/*
 * Árboles Huffman
 */

#include "basicos.hpp"
#include "tabla.hpp"
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>

using codigo_h = std::vector<bool>;

template <class K> struct nodo_h {
    K clave;
    int frec;
    nodo_h<K> * hijo_iz;
    nodo_h<K> * hijo_dr;
    virtual bool es_hoja();
};

template <class K> struct hoja: nodo_h<K> {
    bool es_hoja() {
        return true;
    }
    hoja<K>(K c, int f){
        this->clave = c;
        this->frec = f;
    }
};

template <class K> struct nodo: nodo_h<K> {
    bool es_hoja() {
        return false;
    }
};

template <class K> using ahuff = nodo_h<K>*;


template <class K> ahuff<K> crear_hoja(K clave, int frec);

template <class K> ahuff<K> plantar(ahuff<K> a1, ahuff<K> a2);

template <class K> ahuff<K> ahuff_desde_frecuencias(tabla_frecuencias<K>);

template <class K> void ahuff_graphviz(std::ostream &os, ahuff<K> a);
template <class K> void ahuff_graphviz(std::string filename, ahuff<K> a);

// Para usar las hojas
template <class K> void test(hoja<K> a){
 if (a->es_hoja()){
    ((hoja<K> *) a)->clave;
 }
 else {
    ((nodo<K> *) a)->clave;
 }
}

template <class K> ahuff<K> crear_hoja(K clave, int frec){
    return new hoja<K>(clave, frec);
}

template <class K> ahuff<K> plantar(ahuff<K> hijo_iz, ahuff<K> hijo_dr){
    ahuff<K> a = new nodo<K>;
    a->hijo_iz = hijo_iz;
    a->hijo_dr = hijo_dr;
    a->frec = hijo_dr->frec + hijo_iz->frec;
    return a;
}

template <class K> ahuff<K> ahuff_desde_frecuencias(tabla_frecuencias<K>){
    std::priority_queue<ahuff<K>,std::vector<ahuff<K>>> q;
}

template<class K> void subtree_graphviz(std::ostream &os, std::string id, ahuff<K> a){
    if(a->es_hoja()){
        os << "    " << "ahuff_node" << id << " [shape=\"record\" ";
        os << "label = \"{" << a->frec << "|" << a->clave << "}\"];\n";
    }
    else{
        os << "    " << "ahuff_node" << id << " [label = \"" << a->frec << "\"];\n";
        os << "    " << "ahuff_node" << id << " -> " << "ahuff_node" << id << "i;\n";
        subtree_graphviz(os, id + "i", a->hijo_iz);
        os << "    " << "ahuff_node" << id << " -> " << "ahuff_node" << id << "d;\n";
        subtree_graphviz(os, id + "d", a->hijo_dr);
    }
}

template <class K> void ahuff_graphviz(std::ostream &os, ahuff<K> a){
    os << "digraph AHuffman {\n";
    os << sep << "node [shape = circle]\n";
    subtree_graphviz(os, "", a);
    os << "}\n";
}

template <class K> void ahuff_graphviz(std::string filename, ahuff<K> a){
    std::ofstream file;
    file.open(filename);
    ahuff_graphviz(file, a);
    file.close();
}
