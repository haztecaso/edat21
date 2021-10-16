#include <iostream>
#include "../tads/pila_int.hpp"

using namespace std;

int main(){
    Pila_Int p = crear_pila();

    apilar(p, 69);
    apilar(p, 420);
    apilar(p, 108);

    cout << p << endl;

    liberar(p);

    cout << p << endl;

    return 0;
}
