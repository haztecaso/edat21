#include <string>
#include <sstream>
#include <exception>

using namespace std;

struct Nodo_Cola_Int {
    int valor;
    Nodo_Cola_Int * siguiente;
};

typedef Nodo_Cola_Int * Cola_Int;

const Cola_Int cola_vacia = nullptr;

// Determina si una cola está vacía
bool es_vacia(Cola_Int cola);

// Constructor para colas vacías
Cola_Int crear_cola();

// Constructor para colas con un elemento
Cola_Int crear_cola(int valor);

// Añade un elemento a la cima de una cola
void acolar(Cola_Int &cola, int valor);

// Quita la cima de una cola
void desacolar(Cola_Int &cola);

// Devuelve (sin eliminar) la cima de una cola
int cima(Cola_Int cola);

// Devuelve y elimina la cima de una cola
int cima_y_desacolar(Cola_Int &cola);

// Devuelve el tamaño de una cola
int tamano(Cola_Int cola);

// Libera la memoria de una cola
void liberar(Cola_Int &cola);

// Sobrecarga del operador << para imprimir las colas por pantalla
ostream& operator<<(ostream& os, Cola_Int obj);

// Excepción para funciones parciales no definidas sobre las colas vacías
struct colaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las colas vacías.";
    }
};


// Implementaciones

bool es_vacia(Cola_Int cola)
{
    return cola == cola_vacia;
}

Cola_Int crear_cola()
{
    return cola_vacia;
}

Cola_Int crear_cola(int valor)
{
    Cola_Int cola = new Nodo_Cola_Int;
    cola->valor = valor;
    cola->siguiente = cola_vacia;
    return cola;
}

void acolar(Cola_Int &cola, int valor)
{
    if (es_vacia(cola))
        cola = crear_cola(valor);
    else
    {
        Cola_Int nueva = new Nodo_Cola_Int;
        nueva->valor = valor;
        nueva->siguiente = cola;
        cola = nueva;
    }
}

void desacolar(Cola_Int &cola)
{
    if(!es_vacia(cola))
    {
        Cola_Int old = cola;
        cola = cola->siguiente;
        delete old;
    }
    else
        throw colaVaciaUndef();
}

int cima(Cola_Int cola)
{
    if(!es_vacia(cola))
    {
        return cola->valor;
    }
    else
        throw colaVaciaUndef();
}

int cima_y_desacolar(Cola_Int &cola){
    int result = cima(cola);
    desacolar(cola);
    return result;
}

int tamano(Cola_Int cola)
{
    int result = 0;
    Cola_Int actual = cola;
    while (!es_vacia(actual))
    {
        actual = actual->siguiente;
        result++;
    }
    return result;
}

void liberar(Cola_Int &cola)
{
    while (!es_vacia(cola))
        desacolar(cola);
    delete cola;
}

ostream& operator<<(ostream& os, Cola_Int obj)
{
    Cola_Int actual = obj;
    while (!es_vacia(actual))
    {
        os << actual->valor << " ";
        actual = actual->siguiente;
    }
    return os;
}
