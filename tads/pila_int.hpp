#include <string>
#include <sstream>
#include <exception>

using namespace std;

struct nodo_simple_int {
    int dato;
    nodo_simple_int * siguiente = nullptr;
};

struct pila_int {
    nodo_simple_int * nodo = nullptr;
    int tamano = 0;
};

// Determina si una pila está vacía
bool es_vacia(pila_int pila);

// Añade un elemento a la cima de una pila
void apilar(pila_int &pila, int dato);

// Quita la cima de una pila
void desapilar(pila_int &pila);

// Devuelve (sin eliminar) la cima de una pila
int cima(pila_int pila);

// Devuelve y elimina la cima de una pila
int cima_y_desapilar(pila_int &pila);

// Devuelve el tamaño de una pila
int tamano(pila_int pila);

// Libera la memoria de una pila
void liberar(pila_int &pila);

// Sobrecarga del operador << para imprimir las pilas por pantalla
ostream& operator<<(ostream& os, pila_int obj);

// Excepción para funciones parciales no definidas sobre las pilas vacías
struct PilaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las pilas vacías.";
    }
};


// Implementaciones

bool es_vacia(pila_int pila)
{
    return pila.tamano == 0;
}

nodo_simple_int * crear_nodo(int dato, nodo_simple_int * siguiente)
{
    nodo_simple_int *nodo = new nodo_simple_int;
    nodo->dato = dato;
    nodo->siguiente = siguiente;
    return nodo;
}

void apilar(pila_int &pila, int dato)
{
    if (es_vacia(pila))
    {
        pila.nodo = crear_nodo(dato, nullptr);
    }
    else
    {
        nodo_simple_int *nuevo = crear_nodo(dato, pila.nodo);
        pila.nodo = nuevo;
    }
    pila.tamano++;
}

nodo_simple_int * liberar_nodo_y_avanzar(nodo_simple_int * &nodo)
{
    nodo_simple_int * siguiente = nodo->siguiente;
    delete nodo;
    nodo = siguiente;
    return nodo;
}

void desapilar(pila_int &pila)
{
    if(!es_vacia(pila))
    {
        liberar_nodo_y_avanzar(pila.nodo);
        pila.tamano--;
    }
    else
        throw PilaVaciaUndef();
}

int cima(pila_int pila)
{
    if(!es_vacia(pila))
    {
        return pila.nodo->dato;
    }
    else
        throw PilaVaciaUndef();
}

int cima_y_desapilar(pila_int &pila){
    int result = cima(pila);
    desapilar(pila);
    return result;
}

int tamano(pila_int pila)
{
    return pila.tamano;
}

void liberar(pila_int &pila)
{
    while (!es_vacia(pila))
        desapilar(pila);
}

ostream& operator<<(ostream& os, pila_int pila)
{
    nodo_simple_int *nodo_actual = pila.nodo;
    while (nodo_actual != nullptr)
    {
        os << nodo_actual->dato << " ";
        nodo_actual = nodo_actual->siguiente;
    }
    return os;
}
