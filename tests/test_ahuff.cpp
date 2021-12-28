#include <iostream>
#include "../tads/tabla.hpp"
#include "../tads/ahuff.hpp"

using std::cout;
using std::endl;

typedef char K;
int main(){
    std::string texto = "¿Hola que tal? ¿Cómo te va la vida?";
    tabla_frecuencias<K> frec = frecuencias_char(texto);
    ahuff<K> a = ahuff_desde_frecuencias(frec);
    tabla<K,codigo_h> cods = tabla_vacia<K,codigo_h>();
    tabla_codigos(a, cods, codigo_vacio());
    cout << cods;
    ahuff_graphviz("ahuff.dot", a);
    return 0;
}
