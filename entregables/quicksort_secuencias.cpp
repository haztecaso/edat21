/*
 * QUICKSORT PARA SECUENCIAS
 *
 * Jorge González Gutiérrez
 * Adrián Lattes Grassi
 * Fernando Montero Erustes
 *
 */

#include <sstream>
#include <iostream>

using namespace std;

/* STRUCTS Y TIPOS */ 

// Definición de los nodos simples
template<class T> struct nodo_simple {
    T dato;
    nodo_simple<T> * siguiente = nullptr;
};

struct par_int{
  int primero;
  int segundo;
};

// Definición de las secuencias
template <typename T> struct secuencia {
    nodo_simple<T> * primero; // puntero al anterior al primero
    nodo_simple<T> * anterior; // puntero al anterior al actual
};

/* CABECERAS (SIGNATURAS) */

// OPERACIONES DE NODOS SIMPLES

// Crea e inicializa un nuevo nodo simple dado un dato y un nodo siguiente.
template <class T> nodo_simple<T> * crear_nodo_simple(T d, nodo_simple<T> * s);
// Intercambia los valores de dos nodos simples
template <class T> void intercambiar(nodo_simple<T> *a, nodo_simple<T> *b);

// OPERACIONES DE SECUENCIAS

// Reserva memoria para una secuencia vacia
template <typename T> secuencia<T> crear_secuencia();
// Inserta un elemento en la posición actual
template <typename T> void insertar(secuencia<T>& s, T e);
// Elimina el elemento de la posición actual
template <typename T> void eliminar(secuencia<T>& s);
// Devuelve el nodo actual
template <typename T> nodo_simple<T> * nodo_actual(const secuencia<T>& s);
// Devuelve el valor del nodo actual
template <typename T> T valor_actual(const secuencia<T>& s);
// Avanza en una posición del valor actual
template <typename T> void avanzar(secuencia<T>& s);
// Reinicia el valor actual al primero
template <typename T> void reiniciar(secuencia<T>& s);
// Devuelve el primer nodo de una secuencia
template <typename T> nodo_simple<T> *primero(secuencia<T> s);
// Devuelve el último nodo de una secuencia
template <typename T> nodo_simple<T> *ultimo(secuencia<T> s);
// Determina si se ha alcanzado el final de una secuencia
template <typename T> bool fin(secuencia<T> s);
// Sobrecarga del operador << para imprimir una secuencia
template <typename T> ostream& operator<<(ostream& os, secuencia<T> s);

// OPERACIONES DE PARES DE ENTEROS

// Crea un par de enteros dados dos enteros
par_int crear(int p, int s);
// Sobrecarga del operador < (compara solo los segundos elementos)
bool operator<(par_int e1,par_int e2);
// Sobrecarga del operador << para imprimir pares de enteros
ostream& operator<<(ostream& os, par_int e);

// ALGORITMO DE ORDENACIÓN QUICKSORT

// Algoritmo de ordenación quicksort para secuencias.
template<class T> void quicksort(secuencia<T> s);
// Algoritmo recursivo de ordenación quicksort para cadenas de nodos simples.
template<class T> void quicksort(nodo_simple<T> *inicio, nodo_simple<T> *fin);
// Dada una cadena de nodos simples utiliza el último elemento como pivote y
// reordena la cadena en dos secciones: una con elementos menores y otra mayores
// o iguales.
template<class T> nodo_simple<T> * particion(nodo_simple<T> *inicio, nodo_simple<T> *fin);

// MAIN
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

/* IMPLEMENTACIONES */

// OPERACIONES DE NODOS SIMPLES
template <class T> nodo_simple<T> * crear_nodo_simple(T d, nodo_simple<T> * s){
    nodo_simple<T> *nodo = new nodo_simple<T>;
    nodo->dato = d;
    nodo->siguiente = s;
    return nodo;
}

template <class T> void intercambiar(nodo_simple<T> *a, nodo_simple<T> *b){
    const T tmp = a->dato;
    a->dato = b->dato;
    b->dato = tmp;
}

// OPERACIONES DE SECUENCIAS
template <typename T> secuencia<T> crear_secuencia(){
    secuencia<T> s;
    s.primero = new nodo_simple<T>;
    s.anterior = s.primero;
    return s;
}

template <typename T> void insertar(secuencia<T>& s, T e){
    nodo_simple<T> * nodo_nuevo = crear_nodo_simple(e, s.anterior->siguiente);
    s.anterior->siguiente = nodo_nuevo;
    s.anterior = nodo_nuevo;
}

template <typename T> void eliminar(secuencia<T>& s){
    if(!fin(s)){
        nodo_simple<T> * tmp = s.anterior->siguiente;
        s.anterior->siguiente = tmp->siguiente;
        delete tmp;
    } else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> nodo_simple<T> * nodo_actual(const secuencia<T>& s){
    if(!fin(s)){
        return s.anterior->siguiente;
    } else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> T valor_actual(const secuencia<T>& s){
    if(!fin(s)){
        return s.anterior->siguiente->dato;
    } else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> void avanzar(secuencia<T>& s){
    if(!fin(s)){
        s.anterior = s.anterior->siguiente;
    } else {
        throw runtime_error("final de la secuencia");
    }
}

template <typename T> void reiniciar(secuencia<T>& s){
    s.anterior = s.primero;
}

template <typename T> nodo_simple<T> *primero(secuencia<T> s){
    return s.primero->siguiente;
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


template <typename T> bool fin(secuencia<T> s){
    return s.anterior->siguiente == NULL;
}

const string FLECHA = "↓";

template <typename T> ostream& operator<<(ostream& os, secuencia<T> s){
    nodo_simple<T> * aux = s.primero;
    while(aux->siguiente != NULL){
        if(aux == s.anterior){
            os << FLECHA;
        }
        os << aux->siguiente->dato << " ";
        aux = aux->siguiente;
    }
    return os;
}

// OPERACIONES DE PARES DE ENTEROS

par_int crear(int p, int s){
    par_int result;
    result.primero = p;
    result.segundo = s;
    return result;
};

bool operator<(par_int e1, par_int e2){
  return e1.segundo<e2.segundo;
};

ostream& operator<<(ostream& os, par_int e){
    os << "(" << e.primero << "," << e.segundo << ")";
    return os;
};

// ALGORITMO DE ORDENACIÓN QUCKSORT
template<class T> void quicksort(secuencia<T> s){
    quicksort(primero(s),ultimo(s));
}

template<class T> void quicksort(nodo_simple<T> *inicio, nodo_simple<T> *fin){
    if (inicio == fin)
        return;
    nodo_simple<T> *anterior = particion(inicio, fin);
    quicksort(inicio, anterior);
    quicksort(anterior->siguiente, fin);
}

template<class T> nodo_simple<T> * particion(nodo_simple<T> *inicio, nodo_simple<T> *fin){
    if (inicio == fin|| inicio == nullptr || fin == nullptr )
        return inicio;
    nodo_simple<T> *anterior = inicio;
    nodo_simple<T> *actual = inicio;
    T pivote = fin->dato;
    while(inicio != fin){
        if(inicio->dato < pivote){
            anterior = actual;
            intercambiar(actual, inicio);
            actual = actual->siguiente;
        }
        inicio = inicio->siguiente;
    }
    intercambiar(actual, fin);
    return anterior;
}
