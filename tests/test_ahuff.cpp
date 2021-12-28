#include <iostream>
#include "../tads/tabla.hpp"
#include "../tads/ahuff.hpp"

using std::cout;
typedef char K;
int main(){
    ahuff<K> a = crear_hoja('a', 4);
    ahuff<K> b = crear_hoja('b', 10);
    ahuff<K> c = crear_hoja('c', 1);
    ahuff<K> arb = plantar(a,b);
    ahuff<K> arb2 = plantar(arb, c);
    ahuff_graphviz("ahuff.dot", arb2);
    return 0;
}
