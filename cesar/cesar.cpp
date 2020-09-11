#include <iostream>
#include<string>

#include"func_aux.h"
#include"div_ent.h"
#include"cesar_char.h"

using namespace std;

class cesar {
    string palabra;
    int desplazamiento;
    string abc;
public:
    cesar();
    string cifrar(string palabra, int numero);
    string descifrar(string palabra, int numero);
};

cesar::cesar() {
    abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
}

string cesar::cifrar(string palabra, int numero) {
    int pos;
    string msg = "";
    for (int i = 0; i < palabra.size(); i++) {
        pos = abc.find(palabra[i]);
        pos += desplazamiento;
        pos = modulo(pos, abc.size());
        msg += abc[pos];
    }
    return msg;
}

string cesar::descifrar(string palabra, int numero) {
    int pos;
    string msg = "";
    for (int i = 0; i < palabra.size(); i++) {
        pos = abc.find(palabra[i]);
        pos -= desplazamiento;
        if (pos < 0) {
            pos = (abc.size() + pos);
        }
        msg += abc[pos];
    }
    return msg;
}

int main(){
    string palabra;
    int numero;
    cout << "ingresa la palabra: " << endl;
    cin.ignore();
    getline(cin, palabra);
    cout << "ingresa el desplazamiento: " << endl;
    cin >> numero;
    cesar prueba;
    cin.ignore();
    cout << prueba.cifrar(palabra, numero) << endl;
    cout << "ingresa la palabra: " << endl;
    cin.ignore();
    getline(cin, palabra);
    cout << "ingresa el desplazamiento: " << endl;
    cin >> numero;
    cesar prueba_2;
    cout << prueba_2.descifrar(palabra, numero);
}
