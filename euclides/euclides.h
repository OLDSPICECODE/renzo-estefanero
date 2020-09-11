int euclides(int a, int b) {
    int q;
    int r_1 = a;
    int r_2 = b;
    int r;
    while (r_2 > 0) {
        q = r_1 / r_2;
        r = r_1 - (q * r_2);
        r_1 = r_2;
        r_2 = r;
    }
    return r_1;
}
