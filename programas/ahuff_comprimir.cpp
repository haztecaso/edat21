#include <fstream>
#include <iostream>
#include <sstream>
#include <limits.h>
#include <vector>
#include "../tads/tabla.hpp"
#include "../tads/ahuff.hpp"

using namespace std;

tabla_frecuencias<char> construir_tabla_frecuencias(ifstream &f){
    f.clear();
    f.seekg(0, f.beg);
    tabla_frecuencias<char> tabla = tabla_frecuencias_vacia<char>();
    for (char c; f.get(c);) aniadir(tabla, c, 1);
    return tabla;
}


stringstream optimizar_codigo(vector<bool> codigo){
    stringstream s;
    long num_bits = codigo.size();
    unsigned char c;
    long inic;
    s << num_bits << endl;
    for(int i = 0; i < num_bits/CHAR_BIT; i++){
        c = 0;
        inic = i*CHAR_BIT;
        for(int j = CHAR_BIT-1; j>=0; j--) c = c*2+codigo[inic+j];
        s<<c;
    }
    c = 0;
    inic = (num_bits/CHAR_BIT)*CHAR_BIT;
    for(int j = num_bits%CHAR_BIT-1;j>=0;j--){
        c = c *2 + codigo[inic + j];
    }
    s << c;
    return s;
}

vector<bool> comprimir(tabla<char,codigo_h> cods, ifstream &f){
    f.clear();
    f.seekg(0, f.beg);
    vector<bool> datos = vector<bool>();
    for (char c; f.get(c);){
        for(bool b:consultar(cods,c)){
            datos.push_back(b);
        }
    }
    return datos;
}

int main(int argc, char** argv){
    if(argc != 2){
        std::cout << "Error: este programa requiere exactamente un parámetro, la dirección del fichero a comprimir." << endl;
        return 1;
    }

    char * filename = argv[1];
    ifstream f = ifstream(filename);

    // Fichero -> Tabla de frecuencias de los caracteres
    tabla_frecuencias<char> frecs = construir_tabla_frecuencias(f);

    // Tabla de frecuencias -> Árbol de Huffman
    ahuff<char> a = ahuff_desde_frecuencias(frecs);


    // Árbol de Huffman -> tabla de códigos
    tabla<char,codigo_h> cods = tabla_vacia<char,codigo_h>();
    tabla_codigos(a, cods, codigo_vacio());

    // Comprimir datos
    vector<bool> datos = comprimir(cods, f);

    stringstream s = optimizar_codigo(datos);

    // Visualizar resultados
    ahuff_graphviz("ahuff.dot", a);
    // cout << "Tabla de frecuencias:\n" << frecs << "\n\n";
    // cout << "Tabla de códigos:\n" << cods << "\n";
    cout << "N: " << consultar(cods, 'N') << "\n";
    cout << "Datos:\n" << s.str() << "\n";
    return 0;
}
