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

template <class K> struct ahuff {
    nodo_h<K> * raiz;
};

template <class K> ahuff<K> crear_hoja(K clave, int frec);

template <class K> ahuff<K> plantar(ahuff<K> a1, ahuff<K> a2);

template <class K> bool operator>(ahuff<K> h1, ahuff<K> h2);

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
    ahuff<K> a;
    a.raiz = new hoja<K>(clave, frec);
    return a;
}

template <class K> ahuff<K> plantar(ahuff<K> hijo_iz, ahuff<K> hijo_dr){
    ahuff<K> a;
    a.raiz = new nodo<K>;
    a.raiz->hijo_iz = hijo_iz.raiz;
    a.raiz->hijo_dr = hijo_dr.raiz;
    a.raiz->frec = hijo_dr.raiz->frec + hijo_iz.raiz->frec;
    return a;
}

template <class K> bool operator>(ahuff<K> h1, ahuff<K> h2){
    return h1.raiz->frec > h2.raiz->frec;
}

template<class K> void subtree_graphviz(std::ostream &os, std::string id, nodo_h<K>* a){
    if(a->es_hoja()){
        os << "    " << "ahuff_node" << id << " [shape=\"record\" ";
        os << "label = \"" << a->clave << "|" << a->frec << "\"];\n";
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
    subtree_graphviz(os, "", a.raiz);
    os << "}\n";
}

template <class K> void ahuff_graphviz(std::string filename, ahuff<K> a){
    std::ofstream file;
    file.open(filename);
    ahuff_graphviz(file, a);
    file.close();
}
