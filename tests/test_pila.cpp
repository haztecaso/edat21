#include <iostream>
#include <stdlib.h>
#include <string>
#include "pila.hpp"
#include "utils.hpp"

using namespace std;

typedef char el;

int n_apilados, n_desapilados, n_errores = 0;

void test_apilar(pila<el> &p);
void test_desapilar(pila<el> &p);

int main(){
    srand (time(NULL)); // initialize random seed
    pila<el> p;
    int n = rand() % 1024 + 1024;
    n_apilados = 0;
    n_desapilados = 0;
    for(int i; i < n; i++)
    {
        
        if (rand() % 100 > 50)
        {
            test_apilar(p);
        }
        else
        {
            test_desapilar(p);
        }
    }
    assert_eq(n, n_apilados+n_desapilados+n_errores);
    int t = tamano(p);
    assert_eq(t, n_apilados-n_desapilados);
    cout << p << endl;
    liberar(p);
    t = tamano(p);
    assert_eq(t, 0);
    return 0;
}

void test_apilar(pila<el> &p)
{
    const int tamano_inicial = tamano(p);
    el e = (el) 97 + rand() % 26;
    apilar(p, e);
    const int tamano_final = tamano(p);
    assert_eq(tamano_final, tamano_inicial + 1);
    n_apilados++;
}

void test_desapilar(pila<el> &p)
{
    if(es_vacia(p))
    {
        bool error = false;
        try
        {
            desapilar(p);
        }
        catch(PilaVaciaUndef)
        {
            error = true;
        }
        assert_true(error);
        n_errores++;
    }
    else
    {
        const int tamano_inicial = tamano(p);
        desapilar(p);
        const int tamano_final = tamano(p);
        assert_eq(tamano_final, tamano_inicial - 1);
        n_desapilados++;
    }
}
