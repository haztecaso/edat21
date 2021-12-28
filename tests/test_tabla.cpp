#include <iostream>
#include "../tads/tabla.hpp"

using std::cout;

int main(){
    std::string texto = "hola caracola. pa ti mi cola";
    tabla_frecuencias<char> frec = frecuencias_char(texto);
    std::cout << "Frecuencias:\n" << frec;
    // abb_graphviz("tabla.dot", frec);
    return 0;
}
