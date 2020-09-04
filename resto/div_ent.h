#include<iostream>

using namespace std;

void aux() {
	int a, q = 0, n, r;
	cout << "a=(qxn)+r";
	cout << endl << "ingresa a: ";
	cin >> a;
	cout << "ingresa n: ";
	cin >> n;
	while (true) {
		if (a > 0) {
			q += 1;
			r = a - (q * n);
			if (r < 0) {
				r = a - ((q -= 1) * n);
				break;
			}
		}
		else {
			q -= 1;
			r = a - (q * n);
			if (r > 0) {
				break;
			}

		}
	}
	cout << a << " = " << q << "*" << n << " + " << r << endl;
}