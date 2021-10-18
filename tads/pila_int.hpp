#include <string>
#include <sstream>
#include <exception>

using namespace std;

struct Nodo_Pila_Int {
    int valor;
    Nodo_Pila_Int * siguiente;
};

typedef Nodo_Pila_Int * Pila_Int;

const Pila_Int pila_vacia = nullptr;

// Determina si una pila está vacía
bool es_vacia(Pila_Int pila);

// Constructor para pilas vacías
Pila_Int crear_pila();

// Constructor para pilas con un elemento
Pila_Int crear_pila(int valor);

// Añade un elemento a la cima de una pila
void apilar(Pila_Int &pila, int valor);

// Quita la cima de una pila
void desapilar(Pila_Int &pila);

// Devuelve (sin eliminar) la cima de una pila
int cima(Pila_Int pila);

// Devuelve y elimina la cima de una pila
int cima_y_desapilar(Pila_Int &pila);

// Devuelve el tamaño de una pila
int tamano(Pila_Int pila);

// Libera la memoria de una pila
void liberar(Pila_Int &pila);

// Sobrecarga del operador << para imprimir las pilas por pantalla
ostream& operator<<(ostream& os, Pila_Int obj);

// Excepción para funciones parciales no definidas sobre las pilas vacías
struct PilaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las pilas vacías.";
    }
};


// Implementaciones

bool es_vacia(Pila_Int pila)
{
    return pila == pila_vacia;
}

Pila_Int crear_pila()
{
    return pila_vacia;
}

Pila_Int crear_pila(int valor)
{
    Pila_Int pila = new Nodo_Pila_Int;
    pila->valor = valor;
    pila->siguiente = pila_vacia;
    return pila;
}

void apilar(Pila_Int &pila, int valor)
{
    if (es_vacia(pila))
        pila = crear_pila(valor);
    else
    {
        Pila_Int nueva = new Nodo_Pila_Int;
        nueva->valor = valor;
        nueva->siguiente = pila;
        pila = nueva;
    }
}

void desapilar(Pila_Int &pila)
{
    if(!es_vacia(pila))
    {
        Pila_Int old = pila;
        pila = pila->siguiente;
        delete old;
    }
    else
        throw PilaVaciaUndef();
}

int cima(Pila_Int pila)
{
    if(!es_vacia(pila))
    {
        return pila->valor;
    }
    else
        throw PilaVaciaUndef();
}

int cima_y_desapilar(Pila_Int &pila){
    int result = cima(pila);
    desapilar(pila);
    return result;
}

int tamano(Pila_Int pila)
{
    int result = 0;
    Pila_Int actual = pila;
    while (!es_vacia(actual))
    {
        actual = actual->siguiente;
        result++;
    }
    return result;
}

void liberar(Pila_Int &pila)
{
    while (!es_vacia(pila))
        desapilar(pila);
    delete pila;
}

ostream& operator<<(ostream& os, Pila_Int obj)
{
    Pila_Int actual = obj;
    while (!es_vacia(actual))
    {
        os << actual->valor << " ";
        actual = actual->siguiente;
    }
    return os;
}
