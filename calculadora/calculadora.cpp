#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <cmath>

#include "basicos.hpp"
#include "pila.hpp"
#include "cola.hpp"

#define PRECISION 12
#define NUMERO_REGISTROS 2

using namespace std;

typedef long double el;
typedef pila<el> mem;
typedef el *reg;

//TODO: Evitar variable global

bool interactive = false;

enum token {
    op_dump,
    op_dumpall,
    op_print,
    op_printall,
    op_dumpprint,
    op_dup,
    op_swap,
    op_suma,
    op_resta,
    op_mult,
    op_div,
    op_pot,
    op_sen,
    op_cos,
    op_tan,
    op_gamma,
    const_pi,
};

token parse_op(string word);
void casos_token(token t, mem &m, reg r);
bool ejecutar(mem &m, ifstream &file);
void ejecutar_op(el (*fn)(el), mem &m, reg r);
void ejecutar_op(el (*fn)(el, el), mem &m, reg r);


void ejecutar_op(el (*fn)(el), mem &m, reg r)
{
    r[0] = cima_y_desapilar(m);
    apilar(m, fn(r[0]));
}

void ejecutar_op(el (*fn)(el, el), mem &m, reg r)
{
    r[1] = cima_y_desapilar(m);
    r[0] = cima_y_desapilar(m);
    apilar(m, fn(r[0], r[1]));
}

void print_mem(mem &m)
{
    nodo_simple<el> *e = m.nodo;
    if(es_vacia(m))
    {
        cout << "memoria vacía";
    }
    while (e != nullptr)
    {
        cout << "  " << e->dato;
        if(e->siguiente != nullptr)
            cout << endl;
            e = e->siguiente;
    }
}

token parse_token(string word)
{
    if (word == "d") return op_dump;
    if (word == "D") return op_dumpall;
    if (word == "P") return op_printall;
    if (word == "=") return op_print;
    if (word == "p") return op_dumpprint;
    if (word == "dup") return op_dup;
    if (word == "swap" || word == "sw") return op_swap;
    if (word == "+") return op_suma;
    if (word == "-") return op_resta;
    if (word == "*") return op_mult;
    if (word == "/") return op_div;
    if (word == "^") return op_pot;
    if (word == "sen") return op_sen;
    if (word == "cos") return op_cos;
    if (word == "tan") return op_tan;
    if (word == "G") return op_gamma;
    if (word == "PI") return const_pi;
    throw "`"+ word + "` word unknown";
}

void casos_token(token t, mem &m, reg r)
{
    switch(t)
    {
        case op_dump:
            desapilar(m);
            break;
        case op_dumpall:
            while(!es_vacia(m))
                desapilar(m);
            break;
        case op_print:
            r[0] = cima(m);
            cout << r[0] << " ";
            if (interactive) cout << endl;
            break;
        case op_printall:
            // cout << m;
            print_mem(m);
            if (interactive) cout << endl;
            break;
        case op_dumpprint:
            r[0] = cima_y_desapilar(m);
            cout << r[0] << " ";
            if (interactive) cout << endl;
            break;
        case op_dup:
            r[0] = cima(m);
            apilar(m, r[0]);
            break;
        case op_swap:
            r[0] = cima_y_desapilar(m);
            r[1] = cima_y_desapilar(m);
            apilar(m, r[0]);
            apilar(m, r[1]);
            break;
        case op_suma:
            ejecutar_op([](el a, el b) { return a + b; }, m, r);
            break;
        case op_resta:
            ejecutar_op([](el a, el b) { return a - b; }, m, r);
            break;
        case op_mult:
            ejecutar_op([](el a, el b) { return a * b; }, m, r);
            break;
        case op_div:
            ejecutar_op([](el a, el b) { return a / b; }, m, r);
            break;
        case op_pot:
            ejecutar_op(powl, m, r);
            break;
        case op_sen:
            ejecutar_op(sin, m, r);
            break;
        case op_cos:
            ejecutar_op(cos, m, r);
            break;
        case op_tan:
            ejecutar_op(tan, m, r);
            break;
        case op_gamma:
            ejecutar_op(tgamma, m, r);
            break;
        case const_pi:
            apilar(m, (el) M_PI);
            break;
    }
}


void ejecutar(mem &m, stringstream &source)
{
    string word;
    if(source >> word)
    {
        try
        {
            el valor = stold(word);
            apilar(m, valor);
        }
        catch (const invalid_argument)
        {
            try{
                token t = parse_token(word);
                el r[NUMERO_REGISTROS];
                try
                {
                    casos_token(t, m, r); 
                    cout << flush;
                }
                catch (PilaVaciaUndef)
                {
                    cout << "ERROR: memoria vacía." << endl;
                }
            } catch(string s)
            {
                cout << "ERROR: " << s << endl;
            }
        }
        ejecutar(m, source);
    }
}

void ejecutar_fichero(char * nombre) 
{
    ifstream file;
    file.open(nombre);
    // if (!file.is_open()) return 1;
    mem *m = new mem;
    cout << setprecision(PRECISION);
    try
    {
        stringstream source;
        source << file.rdbuf();
        file.close();
        ejecutar(*m, source);
        cout << endl;
    }
    catch(string err)
    {
        cout << endl << "Error: " << err << endl;
    }
    delete m;
}

void modo_interactivo()
{
    interactive = true;
    char input[256];
    cout << ">> ";
    mem *m = new mem;
    while(cin.getline(input, 256))
    {
        stringstream source = stringstream(string(input));
        ejecutar(*m, source);
        cout << "mem: " << *m << endl;
        cout << ">> ";
    }
}

int main(int argc, char ** argv) {
    if (argc >= 2)
        ejecutar_fichero(argv[1]);
    else
        modo_interactivo();
    return 0;
}
