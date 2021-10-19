#include <iostream>
#include <string>
#include "../tads/pila.hpp"

using namespace std;

typedef string El;
typedef Pila<Pila<El> *> SuperPila;

int main(){
    SuperPila *sp = new SuperPila;
    Pila<El> *p1 = new Pila<El>;
    Pila<El> *p2 = new Pila<El>;

    apilar(*sp, p1);
    apilar(*sp, p2);

    apilar(*p1, string("A"));
    apilar(*p2, string("B"));

    cout << sp << endl;

    apilar(*p1, string("B"));
    apilar(*p2, string("A"));
    apilar(*p1, string("C"));
    apilar(*p2, string("C"));
    apilar(*sp, p1);
    apilar(*sp, p1);
    apilar(*sp, p2);
    apilar(*sp, p2);

    cout << sp << endl;

    return 0;
}
