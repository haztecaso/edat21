#include <string>
#include <sstream>
#include <exception>

using namespace std;

const int CAP_INIC = 2;
const int MULT_CRECIMIENTO = 2;

struct pila_int {
    int cap = CAP_INIC;
    int prof = 0;
    int *datos = new int[CAP_INIC];
};


// No hemos definido la constante pila_vacia ya que hay que alocar memoria para
// definir las pilas vacias.

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
int profundidad(pila_int pila);

// Libera la memoria de una pila
void liberar(pila_int &pila);

// Sobrecarga del operador << para imprimir las pilas por pantalla
ostream& operator<<(ostream& os, pila_int pila);

// Excepción para funciones parciales no definidas sobre las pilas vacías
struct PilaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las pilas vacías";
    }
};

// Implementaciones

bool es_vacia(pila_int pila)
{
    return pila.prof== 0;
}

void aumentar_cap(pila_int &pila)
{
    int *datos = new int[pila.cap * MULT_CRECIMIENTO];
    for(int i = 0; i < pila.prof; i++) // Hay alguna manera mejor de hacer esta copia?
    {
        datos[i] = pila.datos[i];
    }
    delete[] pila.datos;
    pila.datos = datos;
    pila.cap *= MULT_CRECIMIENTO;
}

void apilar(pila_int &pila, int dato)
{
    if(pila.prof== pila.cap)
        aumentar_cap(pila);
    pila.datos[pila.prof] = dato;
    pila.prof++;
}

void desapilar(pila_int &pila)
{
    if(!es_vacia(pila))
        pila.prof--;
    else
        throw PilaVaciaUndef();
}

int cima(pila_int pila)
{
    if(!es_vacia(pila))
        return pila.datos[pila.prof- 1];
    else
        throw PilaVaciaUndef();
}

int cima_y_desapilar(pila_int &pila)
{
    int result = cima(pila);
    desapilar(pila);
    return result;
}

int profundidad(pila_int pila)
{
    return pila.prof;
}

void liberar(pila_int &pila)
{
    pila.prof--;
    if(pila.datos) delete[] pila.datos;
}

ostream& operator<<(ostream& os, pila_int pila)
{
    os << "[";
    for(int i = pila.prof - 1; i >= 0; i--)
    {
        os << pila.datos[i];
        if (i > 0) os << " ";
    }
    os << "]";
    return os;
}
