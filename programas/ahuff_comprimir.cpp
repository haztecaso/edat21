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

using ecod = entrada<char, codigo_h>;

stringstream codificar_tabla(tabla<char,codigo_h> tabla_codigos){
    stringstream s;
    vector<ecod> v = vector<ecod>();
    inorden(tabla_codigos, v);
    for (ecod e: v) s << e.clave << ":" << e.valor << ";";
    s << ";;";
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

stringstream optimizar_codigo(vector<bool> codigo){
    stringstream s;
    long num_bits = codigo.size();
    unsigned char c;
    long inic;
    s << num_bits << ";";
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


int main(int argc, char** argv){
    if(argc != 2){
        std::cout << "Error: este programa requiere exactamente un parámetro, la dirección del fichero a comprimir." << endl;
        return 1;
    }

    string filename = string(argv[1]);
    ifstream f = ifstream(filename);

    cout << "- Generando tabla de frecuencias" << endl;
    tabla_frecuencias<char> frecs = construir_tabla_frecuencias(f);

    cout << "- Generando Árbol de Huffman" << endl;
    ahuff<char> a = ahuff_desde_frecuencias(frecs);

    // Guarda el árbol de huffman en formato .dot. Muy útil para debuguear el
    // código. Para compilar el gráfico hay que ejecutar el siguiente comando
    // (del paquete graphviz): dot -Tpng -O ahuff.dot
    cout << "- Generando ahuff.dot" << endl;
    ahuff_graphviz("ahuff.dot", a);

    cout << "- Generando tabla de códigos de Huffman" << endl;
    tabla<char,codigo_h> cods = tabla_vacia<char,codigo_h>();
    tabla_codigos(a, cods, codigo_vacio());

    cout << "- Comprimiendo fichero y codificando tabla de códigos" << endl;
    stringstream codigos_codificados = codificar_tabla(cods);
    vector<bool> codigo = comprimir(cods, f);
    stringstream datos = optimizar_codigo(codigo);


    string ofilename = filename + ".huff";
    cout << "- Guardando fichero comprimido en " << ofilename << endl;
    ofstream of = ofstream(ofilename);
    of << codigos_codificados.rdbuf();
    of << datos.rdbuf();

    return 0;
}
