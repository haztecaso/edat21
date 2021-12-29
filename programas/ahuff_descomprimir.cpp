#include <fstream>
#include <iostream>
#include <limits.h>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include "../tads/tabla.hpp"
#include "../tads/ahuff.hpp"

using namespace std;

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

stringstream descomprimir(vector<bool> datos, ahuff<char> a){
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

int main(int argc, char** argv){
    if(argc != 2){
        std::cout << "Error: este programa requiere exactamente un parámetro, la dirección del fichero a descomprimir." << endl;
        return 1;
    }
    string filename = string(argv[1]);
    ifstream f = ifstream(filename);

    cout << "- Leyendo tabla de códigos" << endl;
    tabla<char, codigo_h> tabla_codigos = leer_tabla_codigos(f);

    cout << "- Leyendo datos" << endl;
    vector<bool> datos = leer_datos(f);

    cout << "- Construyendo árbol de Huffman a partir de la tabla de códigos" << endl;
    ahuff<char> a = ahuff_desde_tabla_codigos(tabla_codigos);
    ahuff_graphviz("ahuff_descompresion.dot", a);

    cout << "- Descomprimiendo los datos a partir del árbol de Huffman" << endl;
    stringstream texto = descomprimir(datos, a);

    cout << texto.str();

    return 0;
}  
