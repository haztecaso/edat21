#include <string>
#include <sstream>
#include <exception>

using namespace std;

const int CAP_INIC = 2;
const int MULT_CRECIMIENTO = 2;

template<class T>
struct pila {
    int cap = CAP_INIC;
    int prof = 0;
    T *datos = new T[CAP_INIC];
};


// No hemos definido la constante pila_vacia ya que hay que alocar memoria para
// definir las pilas vacias.

// Determina si una pila está vacía
template<class T> bool es_vacia(pila<T> p);

// Añade un elemento a la cima de una pila
template<class T> void apilar(pila<T> &p, T dato);

// Quita la cima de una pila
template<class T> void desapilar(pila<T> &p);

// Devuelve (sin eliminar) la cima de una pila
template <class T> T cima(pila<T> p);

// Devuelve y elimina la cima de una pila
template <class T> T cima_y_desapilar(pila<T> &p);

// Devuelve el tamaño de una pila
template <class T> int profundidad(pila<T> p);

// Libera la memoria de una pila
template <class T> void liberar(pila<T> &p);

// Sobrecarga del operador << para imprimir las pilas por pantalla
template <class T> ostream& operator<<(ostream& os, pila<T> p);

// Sobrecarga del operador << para imprimir punteros a pilas por pantalla
template <class T> ostream& operator<<(ostream& os, pila<T> *p);

// Excepción para funciones parciales no definidas sobre las pilas vacías
struct PilaVaciaUndef : public exception
{
    const char * what () const throw ()
    {
        return "Operación no definida para las pilas vacías";
    }
};

// Implementaciones
template <class T> bool es_vacia(pila<T> p)
{
    return p.prof== 0;
}

template <class T> void aumentar_cap(pila<T> &p)
{
    T *datos = new T[p.cap * MULT_CRECIMIENTO];
    for(int i = 0; i < p.prof; i++) // Hay alguna manera mejor de hacer esta copia?
    {
        datos[i] = p.datos[i];
    }
    delete[] p.datos;
    p.datos = datos;
    p.cap *= MULT_CRECIMIENTO;
}

template <class T> void apilar(pila<T> &p, T dato)
{
    if(p.prof== p.cap)
        aumentar_cap(p);
    p.datos[p.prof] = dato;
    p.prof++;
}

template <class T> void desapilar(pila<T> &p)
{
    if(!es_vacia(p))
        p.prof--;
    else
        throw PilaVaciaUndef();
}

template <class T> T cima(pila<T> p)
{
    if(!es_vacia(p))
        return p.datos[p.prof- 1];
    else
        throw PilaVaciaUndef();
}

template <class T> T cima_y_desapilar(pila<T> &p)
{
    T result = cima(p);
    desapilar(p);
    return result;
}

template <class T> int profundidad(pila<T> p)
{
    return p.prof;
}

template <class T> void liberar(pila<T> &p)
{
    p.prof--;
    if(p.datos) delete[] p.datos;
}

template <class T> ostream& operator<<(ostream& os, pila<T> p)
{
    os << "[";
    for(int i = p.prof - 1; i >= 0; i--)
    {
        os << p.datos[i];
        if (i > 0) os << " ";
    }
    os << "]";
    return os;
}

template <class T> ostream& operator<<(ostream& os, pila<T> *p)
{
    os << "*" << *p;
    return os;
}
