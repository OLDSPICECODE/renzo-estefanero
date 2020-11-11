#include<iostream>
#include<string>
#include<time.h>
#include"euclides.h"
#include "euclides_plus.h"
#include"func_aux.h"

using namespace std;

class RSA {
	string abc;
	long long int p, q;
	unsigned long long int N;
	long long int phi_N;
	long long int Clav_pub;
	long long int Clav_priv;
public:
	RSA(int a, int b);
	long long int get_N();
	long long int get_clv_priv();
	long long int cifrado(string palabra, long long int a, long long int b);
	string descifrado(long long int palabra, long long int clv_priv, long long int Ne);
};

RSA::RSA(int a,int b) {
	srand(time(NULL));
	abc = "abcdefghijklmnopqrstuvwxyz().0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ,+-";
	p = a;
	q = b;
	N = p * q;
	phi_N = (p - 1) * (q - 1);
	Clav_pub = (rand() % phi_N + 1) + 1;
	while (euclides(Clav_pub, phi_N) != 1) {
		Clav_pub = (rand() % phi_N + 1) + 1;
		cout << Clav_pub << endl;
	}
	Clav_priv = euclides_plus(Clav_pub, phi_N);
	cout << Clav_priv << endl;
	cout << N << endl << Clav_pub << endl;
}

long long int RSA::get_N() {
	return N;
}

long long int RSA::get_clv_priv() {
	return Clav_priv;
}

long long int RSA::cifrado(string palabra,long long int a,long long int b) {
	Clav_pub = a;
	N = b;
	string cfr = "";
	unsigned long long int pos = abc.find(palabra);
	//cout <<endl<< pos << endl;
	long long int aux = Clav_pub;
	long long int pos_2;
	pos_2 = expo_mod(pos, Clav_pub, N);
	return pos_2;

}

string RSA::descifrado(long long int palabra, long long int clv_priv, long long int Ne) {
	int help = expo_mod(palabra, clv_priv, Ne);
	cout << help <<endl;
	string lol = "";
	lol = abc[help];
	return lol;
}
