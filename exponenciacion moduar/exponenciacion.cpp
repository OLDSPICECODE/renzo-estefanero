#include <iostream>
#include<string>
#include<vector>
//#include"func_aux.h"
//#include"div_ent.h"
//#include"cesar_char.h"
//#include"cesar_normal.h"
//#include"Afin.h"
#include"euclides_plus.h"
//#include"RSA.h"

using namespace std;

int algoritmo_1(int a, int p, int n) {
	int r = 1;
	for (int i = 0; i < p; i++) {
		r = (r * a) % n;
	}
	return r;
}

int algoritmo_2(int N, int g, int A) {
	int a = g;
	int b = 1;
	while (A > 0) {
		if (A % 2 ) {
			b = (b * a) % N;
		}
		a = (a * a) % N;
		A = A / 2;
	}
	return b;
}

void resto_chino(){
    int num_ec;
    cout << "                forma de ecuacion : x = a (mod m)";
    cout << " ingrese el numero de ecuaciones : ";
    cin >> num_ec;
    cout << endl;
    vector<int> a(num_ec), m(num_ec), divisiones(num_ec), inversas(num_ec);
    int x = 0;

    for (int i = 0; i < num_ec; i++){
        cout << "  a" << i + 1 << " : ";
        cin >> a[i];
    }
    cout << endl;
    for (int i = 0; i < num_ec; i++){
        cout << "  m" << i + 1 << " : ";
        cin >> m[i];
    }

    int prod = 1;
    for (int i = 0; i < num_ec; i++){
        prod = m[i];
        divisiones[i] = prod / m[i];
        inversas[i] = euclides_plus(divisiones[i], m[i]);
        x += a[i] * divisiones[i] * inversas[i];
    }
    x %= prod;
    cout << "\n  el valor de x es : " << x << endl;

}

int explosion_modular(int a, int p, int n) {
    if (p == 0)
        return 1;
    if (p % 2 == 0) {
        int t = explosion_modular(a, p / 2, n);
        return (t * t) % n;
    }
    else {
        int t = explosion_modular(a, (p - 1) / 2, n);
        return a * ((t * t) % n) % n;
    }

}

int algoritmo_5(int a, int b, int n) {
    int d = 1;
    int aux = b;
    vector<int> ayuda;
    while (aux / 2 != 0) {
        int digito = aux % 2;
        ayuda.push_back(digito);
        aux /= aux;
    }
    for (int i = 0; i < ayuda.size(); i++) {
        if (ayuda[i] == 1) {
            d = (d * a) % n;
        }
        a = (a * a) % n;
    }
    return d;
}

int expo_mod(int a, int b, int c) {
    int exp = 1;
    int x = a % c;
    while (b > 0) {
        if ((b % 2) == 1) {
            exp = ((exp * x) % c);
        }
        x = ((x * x) % c);
        b = (b / 2);
    }
    return exp;
}

int main(){	
	cout << algoritmo_1(3, 5, 4);
	cout << endl;
	cout << algoritmo_2(4, 3, 5);
	cout << endl;
    resto_chino();
    cout << endl;
    cout << explosion_modular(3, 5, 4);
    cout << endl;
    cout << algoritmo_5(3, 5, 4);
    cout << endl;
    cout << expo_mod(3, 5, 4);
}
