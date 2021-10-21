#include <iostream>
#include "pila_int_static.hpp"

using namespace std;

int main(){
    pila_int p;
    int i = 1;
    int j = 1;
    int tmp;

    for(int k = 0; k <= 32; k++){
        apilar(p, i);
        tmp = i + j;
        i = j;
        j = tmp;
    }

    cout << p << endl;
    liberar(p);
    cout << p << endl;


    return 0;
}
