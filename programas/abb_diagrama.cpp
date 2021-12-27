// Comando para compilar el diagrama en formato svg (paquete graphviz):
// dot -Tsvg -O abb.dot

#include "../tads/abb.hpp"
#include <iostream>

using namespace std;

typedef char el;

abb<el> abb_rand(int tamano);

const int N = 10;

int main(){
    srand(time(NULL));

    abb<el> arbol = abb_rand(N);

    abb_graphviz("abb.dot", arbol);

    return 0;
}

char char_rnd(){
    return 97 + rand() % 26;
}

abb<el> abb_rand(int tamano){
    abb<el> t = nullptr;

    for(int i = 0; i < tamano; i++){
        el e = char_rnd();
        insertar(t, e);
    }
    return t;
}
