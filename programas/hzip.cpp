#include <fstream>
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cstdint>
#include "../tads/tabla.hpp"
#include "../tads/ahuff.hpp"

using namespace std;
using ecod = entrada<char, codigo_h>;

const string CABECERA = "FICHERO_COMPRIMIDO_AHUFF";

struct opciones {
    enum { modo_comprimir, modo_descomprimir } modo;
    string f_entrada = "";
    string f_salida = "";
};

const char * mensaje_uso =
            "Uso:\n"
            "  hzip <modo> [<fichero_entrada>] [<fichero_salida>]\n"
            "Parámetros:\n"
            "  modo = \"c\" | \"d\"    comprimir o descomprimir\n"
            "  fichero_entrada     ruta del fichero que se va a procesar\n"
            "  fichero_salida      ruta del fichero donde se escribirán los resultados\n";

/* CABECERAS (signaturas) */

// FUNCIONES PRINCIPALES

// Comprime un istream y devuelve el resultado en un ostream
// TODO: Soportar cin para la entrada
void comprimir(istream &entrada, ostream &salida);

// Descomprime un istream y devuelve el resultado en un ostream
void descomprimir(istream &entrada, ostream &salida);

// Escribe optimamente una secuencia de bits (de tipo vector<bool>) en un ostream
void empaquetar_bits(vector<bool> datos, ostream &salida);

// Función inversa de empaquetar_bits
vector<bool> desempaquetar_bits(istream &e);

// Función inversa de empaquetar_bits que desempaqueta una cantidad dada de bits.
// IMPORTANTE: El parámetro num_bits debe ser menor o igual que CHAR_BIT.
void desempaquetar_seccion(istream &e, unsigned int num_bits, vector<bool> &datos);

// Construir una tabla de frecuencias a partir de un istream
tfrecuencias<char> construir_tabla_frecuencias(istream &e);

// Codifica una tabla de códigos para poder guardarla en un fichero
void codificar_tabla(tcodigos<char> abla_codigos, ostream &salida);

// Lee y decodifica la tabla de codigos de un fichero comprimido
tcodigos<char> leer_tabla_codigos(istream &es);

// Reemplaza los caracteres de un istream por una concatenación de codigos de
// huffman, dada la tabla de codigos correspondiente a los datos.
vector<bool> codificar_datos(istream &e, tcodigos<char> tabla_codigos);

// Decodifica unos datos (vector de booleanos), dado un ahuff y una posición en
// el ahuff (a_actual). Además modifica a_actual para guardar la posición actual
// en el árbol, de modo que se pueda continuar la decodifiación en la siguiente
// llamada a la función.
void decodificar_datos(vector<bool> &datos, ahuff<char> a, ahuff<char> &a_actual, ostream &salida);

// Comprueba que un istream comienza con la cabecera correcta
void comprobar_cabecera(istream &e);

// Analizar los argumentos
opciones analizar_argumentos(char ** argv);

/* IMPLEMENTACIONES */

int main(int argc, char** argv){
    (void) argc;

    int error_n = 0;

    opciones opc;
    try{
        opc = analizar_argumentos(argv);
    } catch(const runtime_error& error) {
        cerr << "ERROR: " << error.what() << endl;
        cerr << mensaje_uso;
        return 1;
    }

    ifstream entrada_f;
    bool entrada_es_f = false;
    if(opc.f_entrada!= ""){
        entrada_f = ifstream(opc.f_entrada);
        entrada_es_f = true;
    }

    ofstream salida_f;
    bool salida_es_f = false;
    if(opc.f_salida != ""){
        salida_f = ofstream(opc.f_salida);
        salida_es_f = true;
    }

    try{
        if(opc.modo == opciones::modo_comprimir)
            comprimir(entrada_es_f ? entrada_f : cin, salida_es_f ? salida_f : cout);
        else if(opc.modo == opciones::modo_descomprimir)
            descomprimir(entrada_es_f ? entrada_f : cin, salida_es_f ? salida_f : cout);
    } catch(const runtime_error& error) {
        error_n = 1;
        cerr << "ERROR: " << error.what() << endl;
    }
    if(entrada_es_f) entrada_f.close();
    if(salida_es_f)  entrada_f.close();

    return error_n;
}

void comprimir(istream &entrada, ostream &salida){
    // Generando tabla de frecuencias
    tfrecuencias<char> frecs = construir_tabla_frecuencias(entrada);

    // Generando Árbol de Huffman
    ahuff<char> a = ahuff_desde_frecuencias(frecs);

    // Guarda el árbol de huffman en formato .dot. Muy útil para debuguear el
    // código. Para compilar el gráfico hay que ejecutar el siguiente comando
    // (del paquete graphviz): dot -Tpng -O ahuff.dot
    // ahuff_graphviz("ahuff.dot", a);

    // Generando tabla de códigos de Huffman
    tcodigos<char> tabla_codigos = tcodigos_vacia<char>();
    crear_tabla_codigos(a, tabla_codigos, codigo_vacio());

    // Escribiendo cabecera
    salida << CABECERA;

    // Comprimiendo fichero y codificando tabla de códigos
    codificar_tabla(tabla_codigos, salida);
    vector<bool> datos_bin = codificar_datos(entrada, tabla_codigos);
    empaquetar_bits(datos_bin, salida);
}

void descomprimir(istream &entrada, ostream &salida){
    // Comprobando cabecara
    comprobar_cabecera(entrada);

    // Leyendo tabla de códigos
    tcodigos<char> tabla_codigos = leer_tabla_codigos(entrada);

    // Construyendo árbol de Huffman a partir de la tabla de códigos
    ahuff<char> a = ahuff_desde_tabla_codigos(tabla_codigos);
    // ahuff_graphviz("ahuff_descompresion.dot", a); // ÚTIL PARA DEBUGUEAR

    // Leyendo y descomprimiendo datos poco a poco
    uintmax_t num_bits;
    entrada >> num_bits;

    uintmax_t pos = 0;

    string s;
    getline(entrada,s);

    vector<bool> datos = vector<bool>();

    ahuff<char> a_actual = a;

    while(pos < num_bits){
        unsigned int tamano = num_bits - pos;
        if (tamano > CHAR_BIT) tamano = CHAR_BIT;
        decodificar_datos(datos, a, a_actual, salida);
        desempaquetar_seccion(entrada, tamano, datos);
        pos += CHAR_BIT;
    }
    salida << "\n";
}

void empaquetar_bits(vector<bool> datos, ostream &salida){
    uintmax_t num_bits = datos.size();
    unsigned char c;
    long inic;
    salida << num_bits << "\n";
    for(uintmax_t i = 0; i < num_bits/CHAR_BIT; i++){
        c = 0;
        inic = i*CHAR_BIT;
        for(int j = CHAR_BIT-1; j>=0; j--) c = c*2+datos[inic+j];
        salida<<c;
    }
    c = 0;
    inic = (num_bits/CHAR_BIT)*CHAR_BIT;
    for(int j = num_bits%CHAR_BIT-1;j>=0;j--){
        c = c *2 + datos[inic + j];
    }
    salida << c;
}

vector<bool> desempaquetar_bits(istream &e){
    uintmax_t num_bits;
    vector<bool> result;
    e >> num_bits;
    unsigned char c;
    string s;
    getline(e,s);
    for(uintmax_t i = 0; i<num_bits/CHAR_BIT; i++){
         c = e.get();
         for(long j = 0 ; j<CHAR_BIT;j++){
              result.push_back(c % 2);
              c = c/2;
         }
    }
    c = e.get();
    for(long j = num_bits%CHAR_BIT-1;j>=0;j--){
        result.push_back(c % 2);
        c = c/2;
    }
    return result;
}

void desempaquetar_seccion(istream &e, unsigned int num_bits, vector<bool> &datos){
    unsigned char c = e.get();
    for(unsigned int i = 0; i<num_bits; i++){
        datos.push_back(c % 2);
        c = c / 2;
    }
}

tfrecuencias<char> construir_tabla_frecuencias(istream &e){
    e.clear();
    e.seekg(0, e.beg);
    tfrecuencias<char> tabla = tfrecuencias_vacia<char>();
    for (char c; e.get(c);) aniadir(tabla, c, 1);
    return tabla;
}

void codificar_tabla(tcodigos<char> tabla_codigos, ostream &salida){
    vector<ecod> v = vector<ecod>();
    inorden(tabla_codigos, v);
    for (ecod e: v) salida << e.clave << ":" << e.valor << ";";
    salida << ";;";
}

tcodigos<char> leer_tabla_codigos(istream &es){
    tcodigos<char> t = tcodigos_vacia<char>();
    while(true){
        ecod e;
        es.get(e.clave);
        char c;
        es.get(c);
        if (e.clave == ';' and c == ';') break;
        else if (c != ':'){
            string error_msg = "Al descodificar la tabla de codigos: se"
                "esperaba el caracter ':' como separador o la secuencia \";;\""
                "como indicador del final de la tabla de códigos\n"
                "Obtenido: clave = " + string(1, e.clave) + ", separador = "
                + string(1, c);
            throw runtime_error(error_msg);
        }
        while(es.get(c)){
            if(c == ';') break;
            else if( c == '1') e.valor.push_back(true);
            else if( c == '0') e.valor.push_back(false);
            else throw runtime_error("Al descodificar la tabla de codigos: se"
                    "esperaba un '0','1' o ';'");
        }
        aniadir(t, e);
    }
    return t;
}

vector<bool> codificar_datos(istream &e, tcodigos<char> tabla_codigos){
    e.clear();
    e.seekg(0, e.beg);
    vector<bool> datos = vector<bool>();

    for (char c; e.get(c);){
        codigo_h cod = consultar(tabla_codigos, c);
        datos.insert(datos.end(), cod.begin(), cod.end());
    }
    return datos;
}

void decodificar_datos(vector<bool> &datos, ahuff<char> a, ahuff<char> &a_actual, ostream &salida){
    while(datos.size() > 0){
        bool b = datos[0];
        if(a_actual->es_hoja()){
            salida << a_actual -> clave;
            a_actual = a;
        } else {
            a_actual = b ? a_actual->hijo_dr : a_actual->hijo_iz;
            datos.erase(datos.begin()); // TODO: ¿mejor utilizar deque para tener pop_start?
        }
    }
}

void comprobar_cabecera(istream &e){
        char c;
        for(char s:CABECERA){
            e >> c;
            if(c != s) throw runtime_error("Cabecera incorrecta");
        }
}

opciones analizar_argumentos(char ** argv){
    opciones opc;

    if(*argv == NULL) throw runtime_error("argv vacío");

    (void) *argv++;

    if(*argv == NULL) throw runtime_error("El parámetro modo es obligatorio.");

    if(strcmp(*argv, "c") == 0){
        opc.modo = opciones::modo_comprimir;
        (void) *argv++;
    } else if(strcmp(*argv, "d") == 0){
        opc.modo = opciones::modo_descomprimir;
        (void) *argv++;
    } else {
        throw runtime_error("¡Modo incorrecto! El modo debe ser \"c\" (comprimir) o \"d\" (descomprimir)");
    }

    while(*argv != NULL){
        if(opc.f_entrada== ""){
            opc.f_entrada = string(*argv++);
        } else if (opc.f_salida== ""){
            opc.f_salida = string(*argv++);
        } else {
            throw runtime_error("Demasiados parámetros recibidos");
        }
    }

    if(opc.f_entrada == ""&& opc.modo == opciones::modo_comprimir){
        throw runtime_error("El modo de compresión no soporta la lectura desde stdin");
    }

    return opc;
}
