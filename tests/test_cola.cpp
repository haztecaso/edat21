#include <iostream>
#include "cola.hpp"
#include "utils.hpp"

using namespace std;

typedef char el;
void test_encolar(cola<el> &c);
void test_desencolar(cola<el> &c);

int main(){
    srand (time(NULL)); // initialize random seed
    cola<char> c;

    for(int i; i < N_TESTS; i++)
    {
        if (rand() % 100 > 50)
        {
            test_encolar(c);
        }
        else
        {
            test_desencolar(c);
        }
    }
    liberar(c);
    assert_eq(tamano(c), 0);
    return 0;
}

void test_encolar(cola<el> &c)
{
    const int tamano_inicial = tamano(c);
    el e = (el) 97 + rand() % 26;
    encolar(c, e);
    const int tamano_final = tamano(c);
    assert_eq(tamano_final, tamano_inicial + 1);
}

void test_desencolar(cola<el> &c)
{
    if(es_vacia(c))
    {
        bool error = false;
        try
        {
            desencolar(c);
        }
        catch(ColaVaciaUndef)
        {
            error = true;
        }
        assert_true(error);
    }
    else
    {
        const int tamano_inicial = tamano(c);
        desencolar(c);
        const int tamano_final = tamano(c);
        assert_eq(tamano_final, tamano_inicial - 1);
    }
}
