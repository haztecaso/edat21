/*
 * CALCULADORA RPN
 *
 * Adrián Lattes Grassi
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <cmath>

#include "../tads/basicos.hpp"
#include "../tads/pila.hpp"
#include "../tads/cola.hpp"

#define PRECISION 12
#define NUMERO_REGISTROS 16
#define PROMPT ">> "

using std::string;
using std::stringstream;
using std::cout;

typedef long double el;
typedef pila<el> mem;
typedef el *reg;

enum token {
    op_dump,
    op_dumpall,
    op_print,
    op_printmem,
    op_printreg,
    op_printall,
    op_dumpprint,
    op_dup,
    op_2dup,
    op_over,
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
    op_read,
    op_store,
    const_pi,
    const_e,
};

//TODO: Evitar variables globales
bool interactive = false;
bool printed = false;

// Signaturas
void require_params(mem m, int n);
void ejecutar_op(el (*fn)(el), mem &m);
void ejecutar_op(el (*fn)(el, el), mem &m);
void print_reg(reg r);
token parse_token(string word);
void casos_token(token t, mem &m, reg r);
void ejecutar(mem &m, reg r, stringstream &source);
void ejecutar(char * nombre);
void ejecutar();
void inicializar_registro(reg r);

int main(int argc, char ** argv) {
    if (argc >= 2)
        ejecutar(argv[1]);
    else
        ejecutar();
    return 0;
}

struct SinParametros: public std::exception
{
    const char * what () const throw ()
    {
        return "Faltan parámetros para poder ejecutar la operación";
    }
};

void require_params(mem m, int n)
{
    if (m.tamano < n)
        throw "La operación requiere " + std::to_string(n) + " parámetros";
}

void ejecutar_op(el (*fn)(el), mem &m)
{
    require_params(m, 1);
    el x = cima_y_desapilar(m);
    apilar(m, fn(x));
}

void ejecutar_op(el (*fn)(el, el), mem &m)
{
    require_params(m, 2);
    el b = cima_y_desapilar(m);
    el a = cima_y_desapilar(m);
    apilar(m, fn(a, b));
}

void print_reg(reg r)
{
    cout << "reg: ";
    for (int i = 0; i < NUMERO_REGISTROS; i++)
        cout << r[i] << " ";
}

token parse_token(string word)
{
    if (word == "d") return op_dump;
    if (word == "D") return op_dumpall;
    if (word == "M") return op_printmem;
    if (word == "R") return op_printreg;
    if (word == "P") return op_printall;
    if (word == "=") return op_print;
    if (word == "p") return op_dumpprint;
    if (word == "dup") return op_dup;
    if (word == "ddup") return op_2dup;
    if (word == "over") return op_over;
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
    if (word == "pi" || word == "PI") return const_pi;
    if (word == "e" || word == "E") return const_e;
    if (word == "," || word == "read") return op_read;
    if (word == "." || word == "store") return op_store;
    throw "`"+ word + "` word unknown";
}

void casos_token(token t, mem &m, reg r)
{
    el rd0, rd1;
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
            require_params(m, 1);
            rd0 = cima(m);
            cout << rd0 << " ";
            if (interactive) cout << '\n';
            printed = true;
            break;
        case op_printreg:
            print_reg(r);
            if (interactive) cout << '\n';
            printed = true;
            break;
        case op_printmem:
            cout << "mem: " << m;
            if (interactive) cout << '\n';
            printed = true;
            break;
        case op_printall:
            cout << "mem: " << m << '\n';
            print_reg(r);
            if (interactive) cout << '\n';
            printed = true;
            break;
        case op_dumpprint:
            require_params(m, 1);
            rd0 = cima_y_desapilar(m);
            cout << rd0 << " ";
            if (interactive) cout << '\n';
            printed = true;
            break;
        case op_dup:
            require_params(m, 1);
            rd0 = cima(m);
            apilar(m, rd0);
            break;
        case op_2dup:
            require_params(m, 2);
            rd0 = cima_y_desapilar(m);
            rd1 = cima(m);
            apilar(m, rd0);
            apilar(m, rd1);
            apilar(m, rd0);
            break;
        case op_over:
            require_params(m, 2);
            rd0 = cima_y_desapilar(m);
            rd1 = cima(m);
            apilar(m, rd0);
            apilar(m, rd1);
            break;
        case op_swap:
            require_params(m, 2);
            rd0 = cima_y_desapilar(m);
            rd1 = cima_y_desapilar(m);
            apilar(m, rd0);
            apilar(m, rd1);
            break;
        case op_suma:
            ejecutar_op([](el a, el b) { return a + b; }, m);
            break;
        case op_resta:
            ejecutar_op([](el a, el b) { return a - b; }, m);
            break;
        case op_mult:
            ejecutar_op([](el a, el b) { return a * b; }, m);
            break;
        case op_div:
            ejecutar_op([](el a, el b) { return a / b; }, m);
            break;
        case op_pot:
            ejecutar_op(powl, m);
            break;
        case op_sen:
            ejecutar_op(std::sin, m);
            break;
        case op_cos:
            ejecutar_op(std::cos, m);
            break;
        case op_tan:
            ejecutar_op(std::tan, m);
            break;
        case op_gamma:
            ejecutar_op(std::tgamma, m);
            break;
        case op_read: // indice read
            require_params(m, 1);
            rd0 = cima_y_desapilar(m);
            apilar(m, r[(int) rd0]);
            break;
        case op_store: // valor indice store
            rd0 = (int) cima_y_desapilar(m); // indice
            rd1 = cima_y_desapilar(m); // valor
            r[(int) rd0] = rd1;
            break;
        case const_pi:
            apilar(m, (el) M_PI);
            break;
        case const_e:
            apilar(m, (el) M_E);
            break;
    }
}

void ejecutar(mem &m, reg r, stringstream &source)
{
    string word;
    if(source >> word)
    {
        try
        {
            el valor = stold(word);
            apilar(m, valor);
        }
        catch (std::invalid_argument const&)
        {
            try{
                token t = parse_token(word);
                try
                {
                    casos_token(t, m, r); 
                    cout << std::flush;
                }
                catch (VaciaUndef const&)
                {
                    cout << "ERROR: memoria vacía." << '\n';
                }
            }
            catch(string s)
            {
                cout << "ERROR: " << s << '\n';
            }
        }
        ejecutar(m, r, source);
    }
}

// LEER PROGRAMA DESDE FICHERO 
void ejecutar(char * nombre) 
{
    std::ifstream file;
    file.open(nombre);
    if (!file.is_open()) throw "ERROR: Archivo abierto";
    mem *m = new mem;
    el r[NUMERO_REGISTROS];
    inicializar_registro(r);
    cout << std::setprecision(PRECISION);
    try
    {
        stringstream source;
        source << file.rdbuf();
        file.close();
        ejecutar(*m, r, source);
        cout << '\n';
    }
    catch(string err)
    {
        cout << '\n' << "Error: " << err << '\n';
    }
    delete m;
}

// MODO INTERACTIVO
void ejecutar()
{
    interactive = true;
    char input[256];
    cout << PROMPT;
    mem *m = new mem;
    el r[NUMERO_REGISTROS];
    inicializar_registro(r);
    while(std::cin.getline(input, 256))
    {
        stringstream source = stringstream(string(input));
        printed = false;
        ejecutar(*m, r, source);
        if(!es_vacia(*m) && !printed) cout << cima(*m) << '\n';
        cout << PROMPT;
    }
}

void inicializar_registro(reg r)
{
    for (int i = 0; i < NUMERO_REGISTROS; i++) r[i] = 0;
}

