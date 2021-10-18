#include <string>
#include <sstream>
#include <exception>

using namespace std;

const int CAP_INIC = 10;

struct Pila_Int_Struct {
    int capacidad = CAP_INIC;
    int tamano = 0;
    int *contenido = new int[CAP_INIC];
};

typedef Pila_Int_Struct * Pila_Int;

// No hemos definido la constante pila_vacia ya que hay que alocar memoria para
// definir las pilas vacias.

// Determina si una pila está vacía
bool es_vacia(Pila_Int pila);

// Constructor para pilas vacías
Pila_Int crear_pila();

// Constructor para pilas con un elemento
Pila_Int crear_pila(int valor);

// Añade un elemento a la cima de una pila
void apilar(Pila_Int pila, int valor);

// Quita la cima de una pila
void desapilar(Pila_Int pila);

// Devuelve (sin eliminar) la cima de una pila
int cima(Pila_Int pila);

// Devuelve y elimina la cima de una pila
int cima_y_desapilar(Pila_Int pila);

// Devuelve el tamaño de una pila
int tamano(Pila_Int pila);

// Libera la memoria de una pila
void liberar(Pila_Int &pila);

// Sobrecarga del operador << para imprimir las pilas por pantalla
ostream& operator<<(ostream& os, Pila_Int pila);

// Excepción para funciones parciales no definidas sobre las pilas vacías
struct PilaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las pilas vacías";
    }
};

// Implementaciones

bool es_vacia(Pila_Int pila)
{
    return pila->tamano == 0;
}

Pila_Int crear_pila()
{
    Pila_Int pila = new Pila_Int_Struct;
    return pila;
}

Pila_Int crear_pila(int valor)
{
    Pila_Int pila = new Pila_Int_Struct;
    pila->tamano = 1;
    pila->contenido[0] = valor;
    return pila;
}

void aumentar_capacidad(Pila_Int pila)
{
    int *contenido = new int[pila->capacidad * 2];
    for(int i; i < pila->capacidad; i++)
        contenido[i] = pila->contenido[i]; // Hay alguna manera mejor de hacer esta copia?
    delete pila->contenido;
    pila->contenido = contenido;
    pila->capacidad *= 2;
}

void apilar(Pila_Int pila, int valor)
{
    if(pila->tamano == pila->capacidad)
        aumentar_capacidad(pila);
    pila->contenido[pila->tamano - 1] = valor;
    pila->tamano++;
}

void desapilar(Pila_Int pila)
{
    if(!es_vacia(pila))
        pila->tamano--;
    else
        throw PilaVaciaUndef();
}

int cima(Pila_Int pila)
{
    if(!es_vacia(pila))
        return pila->contenido[pila->tamano - 1];
    else
        throw PilaVaciaUndef();
}

int cima_y_desapilar(Pila_Int pila)
{
    int result = cima(pila);
    desapilar(pila);
    return result;
}

int tamano(Pila_Int pila)
{
    return pila->tamano;
}

void liberar(Pila_Int &pila)
{
    delete pila;
}

ostream& operator<<(ostream& os, Pila_Int pila)
{
    for(int i = 1; i <= pila->tamano; i++)
        os << pila->contenido[pila->tamano - 1 - i] << " ";
    return os;
}
