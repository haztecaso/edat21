#include <iostream>
#include "../tads/tabla.hpp"
#include "../tads/ahuff.hpp"

using std::cout;

typedef char K;
int main(){
    std::string texto = "hola caracola. pa ti mi cola";
    /* tabla_frecuencias<K> frec = frecuencias_char(texto); */

    tabla_frecuencias<K> frec = tabla_frecuencias_vacia<K>();
    aniadir(frec, 'C', 32);
    aniadir(frec, 'D', 42);
    aniadir(frec, 'E', 120);
    aniadir(frec, 'K', 7);
    aniadir(frec, 'L', 42);
    aniadir(frec, 'M', 24);
    aniadir(frec, 'U', 37);
    aniadir(frec, 'Z', 2);

    cout << frec;

    ahuff<K> a = ahuff_desde_frecuencias(frec);
    ahuff_graphviz("ahuff.dot", a);
    return 0;
}
