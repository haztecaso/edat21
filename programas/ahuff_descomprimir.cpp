#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<limits.h>
#include<random>
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
            else if( c == '1') e.valor.insert(e.valor.begin(), true);
            else if( c == '0') e.valor.insert(e.valor.begin(), false);
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
    char c;
    f.get(c);
    if(c!=';') throw runtime_error("Error al leer los datos: se esperaba un ';' después del entero con la longitud de los datos");
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

int main(int argc, char** argv){
    if(argc != 2){
        std::cout << "Error: este programa requiere exactamente un parámetro, la dirección del fichero a descomprimir." << endl;
        return 1;
    }
    string filename = string(argv[1]);
    ifstream f = ifstream(filename);

    cout << "- Leyendo tabla de códigos" << endl;
    tabla<char, codigo_h> tabla_codigos = leer_tabla_codigos(f);

    vector<bool> datos = leer_datos(f);

    cout << tabla_codigos;
    cout << datos;

    return 0;
}  
