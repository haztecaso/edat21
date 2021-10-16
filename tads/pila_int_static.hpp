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
