#include <iostream>
#include<string>

using namespace std;

class cesar_2 {
    string abc;
public:
    cesar_2();
    string cifrar(string palabra, int numero);
    string descifrar(string palabra, int numero);
};

cesar_2::cesar_2() {
    abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
}

string cesar_2::cifrar(string palabra, int numero) {
    int pos;
    int i = 0, j = 0;
    string msg = "";
    char letra;
    char apoyo = abc[j];
    letra = palabra[i];
    while (letra != NULL) {
        while (apoyo != letra) {
            j += 1;
            apoyo = abc[j];
        }
        pos = j;
        j = 0;
        pos += numero;
        pos = pos % abc.size();
        msg += abc[pos];
        i += 1;
        letra = palabra[i];
    }
    return msg;
}

string cesar_2::descifrar(string palabra, int numero) {
    int pos;
    int i = 0, j = 0;
    string msg = "";
    char letra;
    char apoyo = abc[j];
    letra = palabra[i];
    while (letra != NULL) {
        while (apoyo != letra) {
            j += 1;
            apoyo = abc[j];
        }
        pos = j;
        j = 0;
        pos -= numero;
        if (pos < 0) {
            pos = (abc.size() + pos);
        }
        msg += abc[pos];
        i += 1;
        letra = palabra[i];
    }
    return msg;
}

int apoyo() {
    string palabra;
    int numero;
    cout << "ingresa la palabra: " << endl;
    getline(cin, palabra);
    cout << "ingresa el desplazamiento: " << endl;
    cin >> numero;
    cesar_2 uno;
    cout << uno.cifrar(palabra, numero) << endl;
    cout << "ingresa la palabra: " << endl;
    cin.ignore();
    getline(cin, palabra);
    cout << "ingresa el desplazamiento: " << endl;
    cin >> numero;
    cout << uno.descifrar(palabra, numero) << endl;
}