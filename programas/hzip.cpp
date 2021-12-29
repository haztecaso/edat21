#include <fstream>
#include <iostream>
#include <limits.h>
#include <sstream>
#include <vector>
#include "../tads/tabla.hpp"
#include "../tads/ahuff.hpp"

using namespace std;

/* CABECERAS (signaturas) */

// Construir una tabla de frecuencias a partir de los caracteres de un fichero
tfrecuencias<char> construir_tabla_frecuencias(ifstream &f);
// Codifica una tabla de códigos para poder guardarla en un fichero
stringstream codificar_tabla(tabla<char,codigo_h> tabla_codigos);
// Reemplaza los caracteres del fichero por una concatenación de codigos de huffman, dada la tabla de caracteres.
vector<bool> codificar_fichero(tabla<char,codigo_h> tabla_codigos, ifstream &f);
// Optimiza el espacio que ocupan los datos (un vector de booleanos) para que el fichero resultante ocupe menos espacio
stringstream optimizar_datos(vector<bool> datos);
// Comprime un fichero y guarda el resultado en otro fichero con el mismo
// nombre pero acabado en ".huff"
void comprimir(string filename);

// Lee y decodifica la tabla de codigos de un fichero comprimido
tabla<char, codigo_h> leer_tabla_codigos(ifstream &f);
// Lee los datos comprimidos de un fichero, decodificandolos en un vector de booleanos
vector<bool> leer_datos(ifstream &f);
// Descomprime un vector de booleanos, dado un ahuff con las codificaciones de los caracteres
stringstream descomprimir_datos(vector<bool> datos, ahuff<char> a);
// Descomprime un fichero y guarda el resultado en otro fichero con el mismo
// nombre pero acabado en ".txt"
void descomprimir(string filename);

/* IMPLEMENTACIONES */

int main(int argc, char** argv){
    if(argc != 3){
        // TODO: USAGE
        std::cout << "Error: este programa requiere exactamente dos parámetros" << endl;
        return 1;
    }

    string cmd = string(argv[1]);
    string filename = string(argv[2]);

    if(cmd == "c" || cmd == "cmp" || cmd == "comprimir"){
        comprimir(filename);
    } else if(cmd == "d" || cmd == "des" || cmd == "descomprimir"){
        descomprimir(filename);
    }
    else {
        // TODO: Error message
        std::cout << "ERROR" << endl;
        return 1;
    }

    return 0;
}

void comprimir(string filename){
    ifstream f = ifstream(filename);

    // Generando tabla de frecuencias
    tfrecuencias<char> frecs = construir_tabla_frecuencias(f);

    // Generando Árbol de Huffman
    ahuff<char> a = ahuff_desde_frecuencias(frecs);

    // Guarda el árbol de huffman en formato .dot. Muy útil para debuguear el
    // código. Para compilar el gráfico hay que ejecutar el siguiente comando
    // (del paquete graphviz): dot -Tpng -O ahuff.dot
    ahuff_graphviz("ahuff.dot", a);

    // Generando tabla de códigos de Huffman
    tcodigos<char> tabla_codigos = tcodigos_vacia<char>();
    crear_tabla_codigos(a, tabla_codigos, codigo_vacio());

    // Comprimiendo fichero y codificando tabla de códigos
    stringstream codigos_codificados = codificar_tabla(tabla_codigos);
    vector<bool> datos_bin= codificar_fichero(tabla_codigos, f);
    stringstream datos_optim = optimizar_datos(datos_bin);

    // Guardando fichero comprimido
    string ofilename = filename + ".huff";
    ofstream of = ofstream(ofilename);
    of << codigos_codificados.rdbuf();
    of << datos_optim.rdbuf();
}

void descomprimir(string filename){
    ifstream f = ifstream(filename);

    // Leyendo tabla de códigos
    tabla<char, codigo_h> tabla_codigos = leer_tabla_codigos(f);

    // Leyendo datos
    vector<bool> datos = leer_datos(f);

    // Construyendo árbol de Huffman a partir de la tabla de códigos
    ahuff<char> a = ahuff_desde_tabla_codigos(tabla_codigos);
    ahuff_graphviz("ahuff_descompresion.dot", a);

    // Descomprimiendo los datos a partir del árbol de Huffman
    stringstream texto = descomprimir_datos(datos, a);

    // Guardando fichero descomprimido
    string ofilename = filename + ".txt";
    ofstream of = ofstream(ofilename);
    of << texto.rdbuf();
}

tfrecuencias<char> construir_tabla_frecuencias(ifstream &f){
    f.clear();
    f.seekg(0, f.beg);
    tfrecuencias<char> tabla = tfrecuencias_vacia<char>();
    for (char c; f.get(c);) aniadir(tabla, c, 1);
    return tabla;
}

using ecod = entrada<char, codigo_h>;

stringstream codificar_tabla(tabla<char,codigo_h> tabla_codigos){
    stringstream s;
    vector<ecod> v = vector<ecod>();
    inorden(tabla_codigos, v);
    for (ecod e: v) s << e.clave << ":" << e.valor << ";";
    s << ";;";
    return s;
}

vector<bool> codificar_fichero(tabla<char,codigo_h> tabla_codigos, ifstream &f){
    f.clear();
    f.seekg(0, f.beg);
    vector<bool> datos = vector<bool>();

    // TODO: Optimizar
    for (char c; f.get(c);){
        for(bool b:consultar(tabla_codigos,c)) datos.push_back(b);
    }
    return datos;
}

stringstream optimizar_datos(vector<bool> datos){
    stringstream s;
    long num_bits = datos.size();
    unsigned char c;
    long inic;
    s << num_bits << "\n";
    for(int i = 0; i < num_bits/CHAR_BIT; i++){
        c = 0;
        inic = i*CHAR_BIT;
        for(int j = CHAR_BIT-1; j>=0; j--) c = c*2+datos[inic+j];
        s<<c;
    }
    c = 0;
    inic = (num_bits/CHAR_BIT)*CHAR_BIT;
    for(int j = num_bits%CHAR_BIT-1;j>=0;j--){
        c = c *2 + datos[inic + j];
    }
    s << c;
    return s;
}

tabla<char, codigo_h> leer_tabla_codigos(ifstream &f){
    tabla<char, codigo_h> t = tabla_vacia<char,codigo_h>();
    while(true){
        entrada<char, codigo_h> e;
        f.get(e.clave);
        char c;
        f.get(c);
        if (e.clave == ';' and c == ';') break;
        else if (c != ':'){
            string error_msg = "Error al descodificar una entrada: se esperaba";
            error_msg += "el caracter ':' como separador o la secuencia \";;\"";
            error_msg += "como indicador del final de la tabla de códigos\n";
            error_msg += "Obtenido: clave = "+ string(1, e.clave);
            error_msg += ", separador = " + string(1, c);
            throw runtime_error(error_msg);
        }
        while(f.get(c)){
            if(c == ';') break;
            else if( c == '1') e.valor.push_back(true);
            else if( c == '0') e.valor.push_back(false);
            else throw runtime_error("Error al descodificar una entrada: se esperaba un 0,1 o ;");
        }
        aniadir(t, e);
    }
    return t;
}

vector<bool> leer_datos(ifstream &f){
    long num_bits;
    vector<bool> result;
    f >> num_bits;
    unsigned char c;
    string s;
    getline(f,s);
    long pos = 0;
    for(long i =0; i<num_bits/CHAR_BIT; i++){
         c = f.get();
         for(long j = 0 ; j<CHAR_BIT;j++){
              result.push_back(c % 2);
              c = c/2;
              pos++;
         }
    }
    c = f.get();
    for(long j = num_bits%CHAR_BIT-1;j>=0;j--){
        result.push_back(c % 2);
        c = c/2;
    }
    f.close();
    return result;
}

stringstream descomprimir_datos(vector<bool> datos, ahuff<char> a){
    stringstream s;
    ahuff<char> actual = a;
    for(long unsigned int i = 0; i< datos.size(); i++){
        if(actual->es_hoja()){
            s << actual->clave;
            actual = a;
            i--;
        }
        else{
            actual = datos[i] ? actual->hijo_dr : actual->hijo_iz;
        }
    }
    return s;
}

