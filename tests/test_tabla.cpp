#include "test_utils.hpp"
#include <iostream>
#include <string>
#include "../tads/tabla.hpp"
#include "../tads/abb.hpp"

typedef int el;

int main(){
    string s = "hola caracola";
    tabla<char,int> frec = tabla_vacia<char,int>();
    for (char const &c: s){
        aniadir(frec, c, 1);
    }
    abb_graphviz("tabla.dot", frec);
    return 0;
}
