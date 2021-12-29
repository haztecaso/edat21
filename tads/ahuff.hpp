/*
 * Árboles Huffman
 */

#include "basicos.hpp"
#include "tabla.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>

using codigo_h = std::vector<bool>;

// Tabla de frecuencias
template <class K> using tfrecuencias = tabla<K,int>;

// Tabla de códigos
template <class K> using tcodigos = tabla<K,codigo_h>;

template <class K> struct nodo_h {
    K clave;
    int frec = -1;
    nodo_h<K> * hijo_iz = nullptr;
    nodo_h<K> * hijo_dr = nullptr;
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

template <class K> using ahuff = nodo_h<K> *;

codigo_h codigo_vacio();
std::ostream& operator<<(std::ostream& os, codigo_h codigo);

// Crea una tabla de frecuencias vacía
template <class K> tfrecuencias<K> tfrecuencias_vacia();

// Crea una tabla de códigos vacía
template <class K> tcodigos<K> tcodigos_vacia();

template <class K> ahuff<K> crear_hoja(K clave, int frec);
template <class K> ahuff<K> plantar(ahuff<K> a1, ahuff<K> a2);
template <class K> struct AHuffCompare;
template <class K> ahuff<K> ahuff_desde_frecuencias(tfrecuencias<K> tfrec);
template <class K> void tabla_codigos(ahuff<K> a, tabla<K,codigo_h> &cods, codigo_h prefijo);
template <class K> ahuff<K> ahuff_desde_tabla_codigos(tabla<K,codigo_h> cods);
template <class K> void ahuff_graphviz(std::ostream &os, ahuff<K> a);
template <class K> void ahuff_graphviz(std::string filename, ahuff<K> a);

codigo_h codigo_vacio(){
    return std::vector<bool>();
}

template <class K> tfrecuencias<K> tfrecuencias_vacia(){
    return tabla_vacia<K, int>();
}

template <class K> tcodigos<K> tcodigos_vacia(){
    return tabla_vacia<K, codigo_h>();
}

std::ostream& operator<<(std::ostream& os, codigo_h codigo){
    for (bool b:codigo) os << (b ? 1 : 0);
    return os;
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

template <class K> struct AHuffCompare {
    bool operator()(const ahuff<K> a1, const ahuff<K> a2){
        return a1->frec > a2->frec;
    }
};

// Función auxiliar para convertir una tabla de frecuencias en una cola con
// prioridad de hojas, utilizando un recorrido en inorden por el ABB de la tabla
// de frecuencias.
template <class K>
void cola_desde_frecuencias(
        tfrecuencias<K> tfrec,
        std::priority_queue<ahuff<K>,std::vector<ahuff<K>>, AHuffCompare<K>> &q
        ){
    if(!es_abb_vacio(tfrec)){
        cola_desde_frecuencias(tfrec->iz, q);
        ahuff<K> h = crear_hoja(tfrec->dato.clave, tfrec->dato.valor);
        q.push(h);
        cola_desde_frecuencias(tfrec->dr, q);
    }
}

template <class K> ahuff<K> ahuff_desde_frecuencias(tfrecuencias<K> tfrec){
    std::priority_queue<ahuff<K>,std::vector<ahuff<K>>, AHuffCompare<K>> q;
    cola_desde_frecuencias(tfrec, q);
    ahuff<K> a, b, c;
    while(q.size() > 1){
        a = q.top();
        q.pop();
        b = q.top();
        q.pop();
        c = plantar(a, b);
        q.push(c);
    }
    return q.top();
}

codigo_h pre(codigo_h codigo, bool prefijo){
    codigo.push_back(prefijo);
    return codigo;
}

template <class K> void tabla_codigos(ahuff<K> a, tabla<K,codigo_h> &cods, codigo_h prefijo){
    if(!a->es_hoja()){
        tabla_codigos(a->hijo_iz, cods, pre(prefijo, false));
        tabla_codigos(a->hijo_dr, cods, pre(prefijo, true));
    } else {
        aniadir(cods, a->clave, prefijo);
    }
}

template <class K> ahuff<K> ahuff_desde_tabla_codigos(tabla<K,codigo_h> cods){
    using ecod = entrada<char, codigo_h>;
    std::vector<ecod> v = std::vector<ecod>();
    inorden(cods, v);
    ahuff<K> result = new nodo<K>;
    for(ecod e:v){
        long unsigned int pos = 0;
        ahuff<K> actual = result;
        for(bool b: e.valor){
            pos++;
            ahuff<K> &siguiente = b ? actual->hijo_dr : actual->hijo_iz;
            if(siguiente == nullptr){
                if(pos == e.valor.size()){
                    siguiente = crear_hoja(e.clave, -1);
                } else {
                    siguiente = new nodo<K>;
                    actual = siguiente;
                }
            }
            else if(!siguiente->es_hoja()){
                actual = siguiente;
            }
            else{
                throw std::runtime_error("ERROR: Dos claves no pueden tener el mismo códigstringstream s descomprimir(datoso");
            }
        }
    }
    return result;
    }

template <class K> void subtree_graphviz(std::ostream &os, std::string id, ahuff<K> a){
    if(a->es_hoja()){
        os << "    " << "ahuff_node" << id << " [shape=\"record\" ";
        os << "label = \"{" << a->frec << "|" << a->clave << "}\"];\n";
    }
    else{
        os << "    " << "ahuff_node" << id << " [label = \"" << a->frec << "\"];\n";
        os << "    " << "ahuff_node" << id << " -> " << "ahuff_node" << id << "i [label = 0];\n";
        if(a->hijo_iz != nullptr) subtree_graphviz(os, id + "i", a->hijo_iz);
        os << "    " << "ahuff_node" << id << " -> " << "ahuff_node" << id << "d [label = 1];\n";
        if(a->hijo_dr != nullptr) subtree_graphviz(os, id + "d", a->hijo_dr);
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
