#include <sstream>
#include <iostream>
#include "../tads/basicos.hpp"
#include "../tads/secuencia.hpp"

using namespace std;

template <typename T> // T debe tener definido el operador <
void ordenar(secuencia<T>& s); //ordena la secuencia s,00

struct par_int{
  int primero;
  int segundo;
};

par_int crear(int p, int s);
bool operator<=(par_int e1,par_int e2);
ostream& operator<<(ostream& os, par_int e);
template<class T> nodo_simple<T> * ultimo(secuencia<T> s);

template<class T> nodo_simple<T> * particion(nodo_simple<T> *inicio, nodo_simple<T> *fin)
{
    if (inicio == fin|| inicio == nullptr || fin == nullptr )
        return inicio;
    nodo_simple<T> *anterior = inicio;
    nodo_simple<T> *actual = inicio;
    T pivote = fin->dato;
    while(inicio != fin)
    {
        if(inicio->dato < pivote)
        {
            anterior = actual;
            intercambiar(actual, inicio);
            actual = actual->siguiente;
        }
        inicio = inicio->siguiente;
    }
    intercambiar(actual, fin);
    return anterior;
}

template<class T> void quicksort(nodo_simple<T> *inicio, nodo_simple<T> *fin){
    if (inicio == fin)
        return;
    nodo_simple<T> *anterior = particion(inicio, fin);
    quicksort(inicio, anterior);
    quicksort(anterior->siguiente, fin);
}

int main(){
    secuencia<int> s = crear_secuencia<int>();
    for(int i = 0; i< 11; i++){
      int n = rand() % 100;
      insertar(s,n);
    }

    /* cout << s << endl; */
    reiniciar(s);
    nodo_simple<int> *i = nodo_actual(s);
    nodo_simple<int> *f = ultimo(s);

    cout << s << endl;
    quicksort(i,f);
    cout << s << endl;

    /* nodo_simple<int> *anterior = particion(i,f); */
    /* cout << s << endl; */
    /* cout << anterior->dato << endl; */

}


template<class T> nodo_simple<T> *ultimo(secuencia<T> s){
    reiniciar(s);
    nodo_simple<T> *result = nullptr;
    while(!fin(s)){
        result = nodo_actual(s);
        avanzar(s);
    }
    return result;
}

par_int crear(int p, int s){
    par_int result;
    result.primero = p;
    result.segundo = s;
    return result;
};

bool operator<=(par_int e1, par_int e2){
  return e1.segundo<=e2.segundo;
};

ostream& operator<<(ostream& os, par_int e)
{
    os << "(" << e.primero << "," << e.segundo << ")";
    return os;
};