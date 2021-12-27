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
bool operator<(par_int e1,par_int e2);
ostream& operator<<(ostream& os, par_int e);

// Algoritmo de ordenación quicksort para secuencias.
template<class T> void quicksort(secuencia<T> s);

// Algoritmo recursivo de ordenación quicksort para cadenas de nodos simples.
template<class T> void quicksort(nodo_simple<T> *inicio, nodo_simple<T> *fin);

// Dada una cadena de nodos simples utiliza el último elemento como pivote y
// reordena la cadena en dos secciones: una con elementos menores y otra mayores
// o iguales.
template<class T> nodo_simple<T> * particion(nodo_simple<T> *inicio, nodo_simple<T> *fin);

int main(){
    secuencia<par_int> s = crear_secuencia<par_int>();
    for(int i = 0; i < 10; i++){
      int n = rand() % 100;
      // Se añaden dos valores con primeras componentes consecutivas y segundas
      // iguales para verificar más fácilmente si el algoritmo de ordenación es
      // estable.
      insertar(s,crear(2*i,n));
      insertar(s,crear(2*i+1,n));
    }

    // Secuencia antes de ser ordenada
    cout << s << endl;

    // Se puede observar que esta implementación del quicksort no es estable.
    quicksort(s);

    // Secuencia despúes de ser ordenada
    cout << s << endl;

}

par_int crear(int p, int s){
    par_int result;
    result.primero = p;
    result.segundo = s;
    return result;
};

bool operator<(par_int e1, par_int e2){
  return e1.segundo<e2.segundo;
};

ostream& operator<<(ostream& os, par_int e)
{
    os << "(" << e.primero << "," << e.segundo << ")";
    return os;
};

template<class T> void quicksort(secuencia<T> s){
    quicksort(primero(s),ultimo(s));
}

template<class T> void quicksort(nodo_simple<T> *inicio, nodo_simple<T> *fin)
{
    if (inicio == fin)
        return;
    nodo_simple<T> *anterior = particion(inicio, fin);
    quicksort(inicio, anterior);
    quicksort(anterior->siguiente, fin);
}

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
