#include <iostream>
#include <string>
#include "pila.hpp"

using namespace std;

typedef string El;
typedef pila<pila<El> *> super_pila;

int main(){
    super_pila *sp = new super_pila;
    pila<El> *p1 = new pila<El>;
    pila<El> *p2 = new pila<El>;

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
