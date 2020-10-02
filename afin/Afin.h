#include<string>
#include<time.h>
#include<iostream>
#include"euclides_plus.h"
#include"func_aux.h"

using namespace std;

class Afin_Sin_Fin {
	string abcd;
	int A;
	int B;
public:
	Afin_Sin_Fin();
	string cifrar(string palabra);
	void descifrar(string palabra);
};

Afin_Sin_Fin::Afin_Sin_Fin() {
	abcd = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
	srand(time(NULL));
	A = rand() % abcd.size();
	while (euclides_plus(abcd.size(), A) != 1) {
		A = rand() % abcd.size();
	}
	B = rand() % abcd.length();
}

string Afin_Sin_Fin::cifrar(string palabra) {
	int pos = 0;
	string codificado = "";
	for (int i = 0; i < palabra.length(); i++) {
		pos = abcd.find(palabra[i]);
		pos = (A * pos) + B;
		pos = modulo(pos, abcd.length());
		codificado += abcd[pos];
	}
	cout << A << endl << B << endl;
	return codificado;
}

void Afin_Sin_Fin::descifrar(string palabra) {
	//A = a;
	//B = b;
	int pose = 0;
	string pal = "";
	for (int i = 0; i < palabra.length(); i++) {
		pose = abcd.find(palabra[i]);
		pose -= B;
		pose *= (euclides_plus(A, abcd.length()));
		pose = modulo(pose, abcd.length());
		pal += abcd[pose];
	}
	cout << pal;
}