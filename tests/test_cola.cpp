#include "test_utils.hpp"
#ifndef STATIC
    #include "cola.hpp"
#else
    #include "cola_static.hpp"
#endif

using namespace std;

typedef char el;

void test_encolar(cola<el> &c);
void test_desencolar(cola<el> &c);
void test_liberar(cola<el> &c);

int main(){
    srand(time(NULL)); // initialize random seed
    cola<char> c;

    for(int i = 0; i < N_TESTS; i++)
    {
        if (rand() % 100 > 50)
            test_encolar(c);
        else
            test_desencolar(c);
    }
    test_liberar(c);
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
        catch(VaciaUndef const&)
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

void test_liberar(cola<el> &c)
{
    liberar(c);
    assert_eq(tamano(c), 0);
}
