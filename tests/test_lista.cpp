#include "test_utils.hpp"
#include "lista.hpp"

using namespace std;

typedef char el;

enum dir { iz, dr };

dir rand_dir();

void test_insertar(dir d, lista<el> &l);
void test_eliminar(dir d, lista<el> &l);
void test_liberar(lista<el> &l);

int main(){
    srand(time(NULL)); // initialize random seed
    lista<el> l;
    for(int i = 0; i < N_TESTS; i++)
    {
        dir d = rand_dir();
        if (rand() % 100 > 50) test_insertar(d, l);
        else test_eliminar(d, l);
    }
    return 0;
}

dir rand_dir(){
        if (rand() % 2 == 0) return iz;
        else return dr;
}

void test_insertar(dir d, lista<el> &l){
    const int tamano_inicial = tamano(l);
    el e = (el) 97 + rand() % 26;
    if(d == iz){
        insertar_inicio(l, e);
        assert_eq(e, primero (l));
    }
    else if(d == dr){
        insertar_final(l, e);
        assert_eq(e, ultimo(l));
    }
    const int tamano_final = tamano(l);
    assert_eq(tamano_final, tamano_inicial + 1);
}

void test_eliminar(dir d, lista<el> &l){
    if(es_vacia(l))
    {
        bool error = false;
        try
        {
            if(d == iz) eliminar_inicio(l);
            else if (d == dr) eliminar_final(l);
        }
        catch(VaciaUndef const&)
        {
            error = true;
        }
        assert_true(error);
    }
    else
    {
        const int tamano_inicial = tamano(l);
        if(d == iz) eliminar_inicio(l);
        else if (d == dr) eliminar_final(l);
        const int tamano_final = tamano(l);
        assert_eq(tamano_final, tamano_inicial - 1);
    }
}

void test_liberar(lista<el> &l)
{
    liberar(l);
    assert_eq(tamano(l), 0);
}
