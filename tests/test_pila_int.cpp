#include <iostream>
#include "pila_int.hpp"

using namespace std;

int main(){
    pila_int p;

    apilar(p, 69);
    apilar(p, 420);
    apilar(p, 108);

    cout << p << endl;

    desapilar(p);

    cout << p << endl;

    liberar(p);

    cout << p << endl;

    return 0;
}
