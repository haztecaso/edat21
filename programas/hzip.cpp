#include <fstream>
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "../tads/tabla.hpp"
#include "../tads/ahuff.hpp"

using namespace std;

/* CABECERAS (signaturas) */

// FUNCIONES PRINCIPALES

// Comprime un istream y devuelve el resultado en un ostream
// TODO: Soportar cin para la entrada
void comprimir(istream &entrada, ostream &salida);

// Descomprime un istream y devuelve el resultado en un ostream
// TODO: Soportar cin para la entrada
void descomprimir(istream &entrada, ostream &salida);

// Escribe optimamente una secuencia de bits (de tipo vector<bool>) en un ostream
void empaquetar_bits(vector<bool> datos, ostream &salida);

// Función inversa de empaquetar_bits
vector<bool> desempaquetar_bits(istream &e);

// Función inversa de empaquetar_bits
codigo_h desempaquetar_codigo(istream &e, tcodigos<char> tabla_codigos);

// Construir una tabla de frecuencias a partir de un istream
tfrecuencias<char> construir_tabla_frecuencias(istream &e);

// Codifica una tabla de códigos para poder guardarla en un fichero
void codificar_tabla(tcodigos<char> abla_codigos, ostream &salida);

// Lee y decodifica la tabla de codigos de un fichero comprimido
tcodigos<char> leer_tabla_codigos(istream &es);

// Reemplaza los caracteres de un istream por una concatenación de codigos de
// huffman, dada la tabla de codigos correspondiente a los datos.
vector<bool> codificar_datos(istream &e, tcodigos<char> tabla_codigos);

// Descomprime un vector de booleanos, dado un ahuff con las codificaciones de los caracteres
void descomprimir_datos(vector<bool> datos, ahuff<char> a, ostream &salida);

/* IMPLEMENTACIONES */

const char * mensaje_uso = 
            "Uso:\n"
            "  hzip <modo> [<fichero_entrada>] [<fichero_salida>]\n"
            "Parámetros:\n"
            "  modo = \"c\" | \"d\"    comprimir o descomprimir\n"
            "  fichero_entrada     ruta del fichero que se va a procesar\n"
            "  fichero_salida      ruta del fichero donde se escribirán los resultados\n";

enum modo { modo_comprimir, modo_descomprimir};

int main(int argc, char** argv){
    (void) argc;

    if(*argv == NULL){
        cerr << "¡ERROR!" << "\n" << endl;
        return 1;
    }

    string nombre_programa = string(*argv++);

    if(*argv == NULL){
        cerr << "ERROR: El parámetro modo es obligatorio.\n" << mensaje_uso << endl;
        return 1;
    }

    modo modo;
    if(strcmp(*argv, "c") == 0){
        modo = modo_comprimir;
        (void) *argv++;
    } else if(strcmp(*argv, "d") == 0){
        modo = modo_descomprimir;
        (void) *argv++;
    } else {
        cerr <<
            "ERROR: ¡modo incorrecto!\n"
            "El modo debe ser \"c\" (comprimir) o \"d\" (descomprimir), pero se ha"
            "recibido \"" << *argv << "\".\n\n" << mensaje_uso << endl;
        return 1;
    }

    string nombre_fichero_entrada = "";
    string nombre_fichero_salida  = "";

    while(*argv != NULL){
        if(nombre_fichero_entrada == ""){
            nombre_fichero_entrada = string(*argv++);
        } else if (nombre_fichero_salida == ""){
            nombre_fichero_salida = string(*argv++);
        } else {
            cerr << "ERROR: Demasiados parámetros recibidos \n" << mensaje_uso << endl;
            return 1;
        }
    }

    ifstream entrada_f;
    bool entrada_es_f = false;
    if(nombre_fichero_entrada != ""){
        entrada_f = ifstream(nombre_fichero_entrada);
        entrada_es_f = true;
    }

    ofstream salida_f;
    bool salida_es_f = false;
    if(nombre_fichero_salida != ""){
        salida_f = ofstream(nombre_fichero_salida);
        salida_es_f = true;
    }

    if(!entrada_es_f && modo == modo_comprimir){
        cerr << "ERROR: El modo de compresión no soporta la lectura desde stdin\n";
        return 1;
    }

    if(!entrada_es_f && modo == modo_descomprimir){
        cerr << "ERROR: El modo de descompresión todavía no soporta la lectura desde stdin\n";
        return 1;
    }

    if(modo == modo_comprimir)
        comprimir(entrada_es_f ? entrada_f : cin, salida_es_f ? salida_f : cout);
    else if(modo == modo_descomprimir)
        descomprimir(entrada_es_f ? entrada_f : cin, salida_es_f ? salida_f : cout);

    if(entrada_f) entrada_f.close();
    if(salida_f)  entrada_f.close();

    return 0;
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

    // Comprimiendo fichero y codificando tabla de códigos
    codificar_tabla(tabla_codigos, salida);
    vector<bool> datos_bin = codificar_datos(entrada, tabla_codigos);
    empaquetar_bits(datos_bin, salida);
}

void descomprimir(istream &entrada, ostream &salida){

    // Leyendo tabla de códigos
    tcodigos<char> tabla_codigos = leer_tabla_codigos(entrada);

    // Construyendo árbol de Huffman a partir de la tabla de códigos
    ahuff<char> a = ahuff_desde_tabla_codigos(tabla_codigos);
    // ahuff_graphviz("ahuff_descompresion.dot", a); // ÚTIL PARA DEBUGUEAR

    // Leyendo datos
    vector<bool> datos = desempaquetar_bits(entrada);

    // Descomprimiendo los datos a partir del árbol de Huffman
    descomprimir_datos(datos, a, salida);
}

tfrecuencias<char> construir_tabla_frecuencias(istream &e){
    e.clear();
    e.seekg(0, e.beg);
    tfrecuencias<char> tabla = tfrecuencias_vacia<char>();
    for (char c; e.get(c);) aniadir(tabla, c, 1);
    return tabla;
}

using ecod = entrada<char, codigo_h>;

void codificar_tabla(tcodigos<char> tabla_codigos, ostream &salida){
    vector<ecod> v = vector<ecod>();
    inorden(tabla_codigos, v);
    for (ecod e: v) salida << e.clave << ":" << e.valor << ";";
    salida << ";;";
}

vector<bool> codificar_datos(istream &e, tcodigos<char> tabla_codigos){
    e.clear();
    e.seekg(0, e.beg);
    vector<bool> datos = vector<bool>();

    // TODO: Optimizar
    for (char c; e.get(c);){
        for(bool b:consultar(tabla_codigos,c)) datos.push_back(b);
    }
    return datos;
}

void empaquetar_bits(vector<bool> datos, ostream &salida){
    long num_bits = datos.size();
    unsigned char c;
    long inic;
    salida << num_bits << "\n";
    for(int i = 0; i < num_bits/CHAR_BIT; i++){
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

tcodigos<char> leer_tabla_codigos(istream &es){
    tcodigos<char> t = tcodigos_vacia<char>();
    while(true){
        entrada<char, codigo_h> e;
        es.get(e.clave);
        char c;
        es.get(c);
        if (e.clave == ';' and c == ';') break;
        else if (c != ':'){
            string error_msg = "Error al descodificar la tabla de codigos: se"
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
            else throw runtime_error("Error al descodificar la tabla de codigos"
                    ": se esperaba un '0','1' o ';'");
        }
        aniadir(t, e);
    }
    return t;
}

vector<bool> desempaquetar_bits(istream &e){
    long num_bits;
    vector<bool> result;
    e >> num_bits;
    unsigned char c;
    string s;
    getline(e,s);
    long pos = 0;
    for(long i =0; i<num_bits/CHAR_BIT; i++){
         c = e.get();
         for(long j = 0 ; j<CHAR_BIT;j++){
              result.push_back(c % 2);
              c = c/2;
              pos++;
         }
    }
    c = e.get();
    for(long j = num_bits%CHAR_BIT-1;j>=0;j--){
        result.push_back(c % 2);
        c = c/2;
    }
    return result;
}

void descomprimir_datos(vector<bool> datos, ahuff<char> a, ostream &salida){
    ahuff<char> actual = a;
    for(long unsigned int i = 0; i< datos.size(); i++){
        if(actual->es_hoja()){
            salida << actual->clave;
            actual = a;
            i--;
        }
        else{
            actual = datos[i] ? actual->hijo_dr : actual->hijo_iz;
        }
    }
}

