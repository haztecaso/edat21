#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <cmath>

#include "pila.hpp"

#define PRECISION 12
#define NUMERO_REGISTROS 2

using namespace std;

typedef long double el;
typedef pila<el> mem;
typedef el *reg;


enum Lit {
    op_dump,
    op_print,
    op_printall,
    op_dumpprint,
    op_dup,
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

const string ops_1[] = {
    "sen",
    "cos",
    "tan",
    "asen",
    "acos",
    "atan",
};

Lit parse_op(string lit);
void casos_lit(Lit lit, mem &m, reg r);
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


Lit parse_lit(string lit)
{
    if (lit == "d") return op_dump;
    if (lit == "P") return op_printall;
    if (lit == "=") return op_print;
    if (lit == "p") return op_dumpprint;
    if (lit == "dup") return op_dup;
    if (lit == "+") return op_suma;
    if (lit == "-") return op_resta;
    if (lit == "*") return op_mult;
    if (lit == "/") return op_div;
    if (lit == "^") return op_pot;
    if (lit == "sen") return op_sen;
    if (lit == "cos") return op_cos;
    if (lit == "tan") return op_tan;
    if (lit == "G") return op_gamma;
    if (lit == "PI") return const_pi;
    throw "`"+ lit + "` literal unknown";
}

void casos_lit(Lit lit, mem &m, reg r)
{
    switch(lit)
    {
        case op_dump:
            desapilar(m);
            break;
        case op_print:
            r[0] = cima(m);
            cout << r[0] << " ";
            break;
        case op_printall:
            cout << m;
            break;
        case op_dumpprint:
            r[0] = cima_y_desapilar(m);
            cout << r[0] << " ";
            break;
        case op_dup:
            r[0] = cima(m);
            apilar(m, r[0]);
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

bool ejecutar(mem &m, ifstream &file)
{
    string word;
    if(file >> word)
    {
        try
        {
            el valor = stold(word);
            apilar(m, valor);
        }
        catch (const invalid_argument)
        {
            Lit lit = parse_lit(word);
            el r[NUMERO_REGISTROS];
            try
            {
                casos_lit(lit, m, r); 
                cout << flush;
            }
            catch (PilaVaciaUndef)
            {
                throw "PilaVacia. No se ha podido ejecutar `" + word + "`";
            }
        }
        return true;
    }
    else return false;
}


int main(int argc, char ** argv) {
    if (argc >= 2)
    {
        ifstream file;
        file.open(argv[1]);
        if (!file.is_open()) return 1;
        mem *m = new mem;
        cout << setprecision(PRECISION);
        try
        {
            while(ejecutar(*m, file));
            cout << endl;
        }
        catch(string err)
        {
            cout << endl << "Error: " << err << endl;
        }
        delete m;
        return 0;
    }
    else return 1;
}
