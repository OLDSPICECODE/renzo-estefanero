int modulo(int a, int b) {
	int aux = a / b;
	int residuo = a - (aux * b);
	if (residuo < 0) {
		residuo += b;
	}
	return residuo;
}