#include "test_utils.hpp"
#ifndef STATIC
    #include "../tads/pila.hpp"
#else
    #include "../tads/pila_static.hpp"
#endif

using namespace std;

typedef char el;

void test_apilar(pila<el> &p);
void test_desapilar(pila<el> &p);
void test_liberar(pila<el> &p);

int main(){
    srand(time(NULL)); // initialize random seed
    pila<el> p;
    for(int i = 0; i < N_TESTS; i++)
    {
        if (rand() % 100 > 50)
            test_apilar(p);
        else
            test_desapilar(p);
    }
    test_liberar(p);
    return 0;
}

void test_apilar(pila<el> &p)
{
    const int tamano_inicial = tamano(p);
    el e = (el) 97 + rand() % 26;
    apilar(p, e);
    const int tamano_final = tamano(p);
    assert_eq(tamano_final, tamano_inicial + 1);
}

void test_desapilar(pila<el> &p)
{
    if(es_vacia(p))
    {
        bool error = false;
        try {
            desapilar(p);
        }
        catch(VaciaUndef const&)
        {
            error = true;
        }
        assert_true(error);
    }
    else
    {
        const int tamano_inicial = tamano(p);
        desapilar(p);
        const int tamano_final = tamano(p);
        assert_eq(tamano_final, tamano_inicial - 1);
    }
}

void test_liberar(pila<el> &p)
{
    liberar(p);
    assert_eq(tamano(p), 0);
}
