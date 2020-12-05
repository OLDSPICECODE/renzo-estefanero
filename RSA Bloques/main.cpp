#include <vector>
#include <iostream>
#include "NTL/ZZ.h"
#include <string>
#include<sstream>

using namespace NTL;
using namespace std;

class RSA_BLOQUES {
    ZZ p, q, N, e, d, phi_N; // e==calve publica
    ZZ clv;
    int bt;
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
public:
    RSA_BLOQUES(int bits);
    RSA_BLOQUES(ZZ Ne, ZZ clvp);
    RSA_BLOQUES(ZZ N_1, ZZ e_1, ZZ d_1 );
    vector<ZZ> criba(ZZ mayor, ZZ menor);
    ZZ explosion_modular(ZZ base, ZZ exponente, ZZ mod);
    ZZ modulo(ZZ a, ZZ b);
    bool euclides(ZZ a, ZZ b);
    bool test_prim(ZZ numero);
    ZZ generar_primo(int bits);
    vector<ZZ> euclides_plus(ZZ a, ZZ b);
    ZZ inversa(ZZ e, ZZ N);
    string cifrar(string messenger);
    string descifrado(string msg);
};

RSA_BLOQUES::RSA_BLOQUES(ZZ N_1, ZZ e_1, ZZ d_1) {
    N = N_1;
    e = e_1;
    d = d_1;
}

RSA_BLOQUES::RSA_BLOQUES(int bits) {
    srand(time(NULL));
    ZZ aux = ZZ(1);
    ZZ aux_aux = aux;
    bt = bits;
    bits /= 2;
    while (bits > 1) {
        aux *= 2;
        bits -= 1;
    }
    vector<ZZ> primos_random = criba(aux - 1, aux / 2);
    p = primos_random[rand()%primos_random.size()];
    q = primos_random[rand() % primos_random.size()];
    while (q == p ) {
        q= primos_random[rand() % primos_random.size()];
    }
    N = p * q;
    phi_N = (p - 1) * (q - 1);
    e = primos_random[rand() % primos_random.size()];
    while (!euclides(e,phi_N)) {
        e = primos_random[rand() % primos_random.size()];
    }
    d = inversa(e, phi_N);
    std::cout << N << endl << e << endl;
    cout << d << endl;
}
RSA_BLOQUES::RSA_BLOQUES(ZZ Ne, ZZ clvp) {
    N = Ne;
    clv = clvp;
}
vector<ZZ> RSA_BLOQUES::criba(ZZ mayor, ZZ menor) {
    ZZ intervalo = (mayor - menor) + 1;
    int primos = 2;
    bool agregar = true;
    vector<ZZ> numero_primos;
    while (menor <= mayor) {
        agregar = true;
        primos = 2;
        while (primos * primos < mayor) {
            if (menor % primos == 0) {
                agregar = false;
                break;
            }
            primos += 1;
        }
        if (agregar) {
            numero_primos.push_back(menor);
        }
        menor += 1;
    }
    return numero_primos;
}
ZZ RSA_BLOQUES::explosion_modular(ZZ base, ZZ exponente, ZZ mod) {
    ZZ exp = ZZ(1);
    while (exponente > 0) {
        if (modulo(exponente, ZZ(2)) == 1) {
            exp = modulo((exp * base), mod);
        }
        base = (base * base) % mod;
        exponente = (exponente / 2);
    }
    return exp;
}
ZZ RSA_BLOQUES::modulo(ZZ a, ZZ b) {
    ZZ aux = a / b;
    ZZ residuo = a - (aux * b);
    if (residuo < 0) {
        residuo += b;
    }
    return residuo;
}
bool RSA_BLOQUES::euclides(ZZ a, ZZ b) {
    ZZ q;
    ZZ r_1 = a;
    ZZ r_2 = b;
    ZZ r;
    while (r_2 > 0) {
        q = r_1 / r_2;
        r = r_1 - (q * r_2);
        r_1 = r_2;
        r_2 = r;
    }
    if (r_1 == 1) {
        return true;
    }
    else {
        return false;
    }
}
ZZ RSA_BLOQUES::generar_primo(int bits) {
   srand(time(NULL));
    vector<ZZ> premo;
    int exponente = bt / 2;
    ZZ numero = ZZ(2);
    ZZ aux = numero;
    while (exponente > 0) {
        numero *= aux;
        exponente -= 1;
    }
    premo = criba(numero - 1, numero / 2);
    int random = rand() % premo.size();
    return premo[random];
    
}

bool RSA_BLOQUES::test_prim(ZZ numero) {
    ZZ aux = ZZ(8);
    if (explosion_modular(aux, numero, numero) != aux) {
        return false;
    }
    return true;
}

vector<ZZ> RSA_BLOQUES::euclides_plus(ZZ a, ZZ b) {
    vector<ZZ> invrt;
    ZZ r_1 = a; // residuo
    ZZ r_2 = b;
    ZZ s_1 = ZZ(1); // x
    ZZ s_2 = ZZ(0);
    ZZ t_1 = ZZ(0); // y
    ZZ t_2 = ZZ(1);
    ZZ q = ZZ(0);
    ZZ r = ZZ(0);
    ZZ s = ZZ(0);
    ZZ t = ZZ(0);
    bool rtn = false;
    while (!rtn) {
        invrt.clear();
        while (r_2 > 0) {
            q = r_1 / r_2;
            r = r_1 % r_2;
            r_1 = r_2;
            r_2 = r;
            s = s_1 - (q * s_2);
            s_1 = s_2;
            s_2 = s;
            t = t_1 - (q * t_2);
            t_1 = t_2;
            t_2 = t;
        }
        if (r_1 == 1) {
            if (s_1 < 0) {
                s_1 += b;
            }
            rtn = true;
        }
        else {
            r_1 = generar_primo(16);
        }
    }
    invrt.push_back(s_1);
    invrt.push_back(t_1);
    invrt.push_back(r_1);
    return invrt;
}
ZZ RSA_BLOQUES::inversa(ZZ e, ZZ N) {
    vector<ZZ> resultados;
    resultados = euclides_plus(e, N);
    return resultados[0];
}
string RSA_BLOQUES::cifrar(string messenger) {
    string aux_abc = to_string(abc.size());
    int cifras_abc = aux_abc.size();
    stringstream valor_grande;
    valor_grande << N;
    string cifras = valor_grande.str();
    int cifras_N = cifras.size();
    int bloques_N = cifras.size() - 1;
    int pos;
    ZZ valor = ZZ(0);
    string aux_numeros = "";
    string numeros = "";
    string bloques = "";
    string msg = "";
    for (int i = 0; i < messenger.size(); i++) {
        aux_numeros = "";
        pos = abc.find(messenger[i]);
        aux_numeros += to_string(pos);
        while (aux_numeros.size() < cifras_abc) {
            aux_numeros = ('0' + aux_numeros);
        }
        numeros += aux_numeros;
    }
    cout << numeros << endl;
    aux_numeros = to_string(abc.find('w'));
    while (numeros.size() % bloques_N != 0) {
        numeros += aux_numeros[numeros.size() % 2];
    }
    cout << numeros << endl;
    vector<string> block;
    for(int i = 0; i < numeros.size(); i++){
        bloques += numeros[i];
        if(bloques.size() == bloques_N){
            block.push_back(bloques);
            bloques = "";
        }
    }
    for(int i = 0; i < block.size(); i++){
        string aux = block[i];
        ZZ ayuda = ZZ(1);
        for (int j = aux.size() - 1; j >= 0; j--) {
            int help = to_int(aux[j]) - '0';
            valor += (help * ayuda);
            ayuda *= 10;
        }
        valor = explosion_modular(valor, e, N);
        stringstream valor_grande;
        valor_grande << valor;
        bloques = valor_grande.str();
        while (bloques.size() < cifras_N) {
            bloques = ('0' + bloques);
        }
        msg += bloques;
        valor = ZZ(0);
    }
    cout << msg << endl;
    return msg;
}
string RSA_BLOQUES::descifrado(string msg) {
    string aux_abc = to_string(abc.size());
    int cifras_abc = aux_abc.size();
    stringstream valor_grande;
    valor_grande << N;
    string cifras = valor_grande.str();
    int cifras_N = cifras.size();
    int bloques_N = cifras.size() - 1;
    int pos;
    string bloque = "";
    string numero = "";
    string result = "";
    vector<string>cuadrados;
    ZZ valor = ZZ(0);
    for(int i = 0; i < msg.size(); i++){
        bloque += msg[i];
        if(bloque.size() == cifras_N){
            cuadrados.push_back(bloque);
            bloque = "";
        }
    }
    for(int i = 0; i < cuadrados.size(); i++){
        bloque = cuadrados[i];
        ZZ ayuda = ZZ(1);
        for (int j = bloque.size() - 1; j >= 0; j--) {
            int help = to_int(bloque[j]) - '0';
            valor += (help * ayuda);
            ayuda *= 10;
        }
        valor = explosion_modular(valor, d, N);
        stringstream valor_grande;
        valor_grande << valor;
        bloque = valor_grande.str();
        while (bloque.size() < bloques_N) {
            bloque = ('0' + bloque);
        }
        result += bloque;
        valor = ZZ(0);
    }
    cout << result << endl;
   
    vector<string>letras;
    bloque = "";
    for(int i = 0; i < result.size(); i++){
        bloque += result[i];
        if(bloque.size() == cifras_abc){
            letras.push_back(bloque);
            bloque = "";
        }
    }
    result = "";
    for(int i = 0; i < letras.size(); i ++){
        pos = stoi(letras[i]);
        result += (abc[pos]);
    }

    return result;
}

ZZ modulo(ZZ a, ZZ b) {
    ZZ aux = a / b;
    ZZ residuo = a - (aux * b);
    if (residuo < 0) {
        residuo += b;
    }
    return residuo;
}

bool euclides(ZZ a, ZZ b) {
    ZZ q;
    ZZ r_1 = a;
    ZZ r_2 = b;
    ZZ r;
    while (r_2 > 0) {
        q = r_1 / r_2;
        r = r_1 - (q * r_2);
        r_1 = r_2;
        r_2 = r;
    }
    if (r_1 == 1) {
        return true;
    }
    else {
        return false;
    }
}

ZZ explosion_modular(ZZ base, ZZ exponente, ZZ mod) {
    ZZ exp;
    exp = ZZ(1);
    cout << exp << endl;
    while (exponente > 0) {
        if (modulo(exponente, ZZ(2)) == 1) {
            exp = modulo((exp * base), mod);
        }
        cerr << exp << endl;
        base = modulo((base * base), mod);
        exponente = (exponente / 2);
    }
    return exp;
}

ZZ euclides_plus(ZZ a, ZZ b) {
    vector<ZZ> invrt;
    ZZ r_1 = a; // residuo
    ZZ r_2 = b;
    ZZ s_1 = ZZ(1); // x
    ZZ s_2 = ZZ(0);
    ZZ t_1 = ZZ(0); // y
    ZZ t_2 = ZZ(1);
    ZZ q = ZZ(0);
    ZZ r = ZZ(0);
    ZZ s = ZZ(0);
    ZZ t = ZZ(0);
    bool rtn = false;
    while (!rtn) {
        invrt.clear();
        while (r_2 > 0) {
            q = r_1 / r_2;
            r = r_1 % r_2;
            r_1 = r_2;
            r_2 = r;
            s = s_1 - (q * s_2);
            s_1 = s_2;
            s_2 = s;
            t = t_1 - (q * t_2);
            t_1 = t_2;
            t_2 = t;
        }
        if (r_1 == 1) {
            if (s_1 < 0) {
                s_1 += b;
            }
            rtn = true;
        }
    }
    if (r_1 == 1) {
        if (s_1 > 0) {
            return s_1;
        }
        else {
            ZZ aux = s_1 / b;
            ZZ residuo = s_1 - ( b * aux);
            if (residuo < 0) {
                residuo += b;
            }
            return residuo;
        }
    }
    else {
        //cout << "no tiene inversa";
        return ZZ(0);
    }
}

int main() {
    /*E
    d = 77826773
    N = 95726647
    e = 6557
    */
    /*R
    d = 50109461
    N = 65028071
    e = 5885
    */
    /*
    N = 10967535067
    e = 7487898961
    d =
    p = 104723
    q = 104729
    */
    //7487898961 10967535067

    /*
    108000519939650950931882676596323234165195935029234042922428003953075177312671426720582983905044008175722054131259946818675460815776605973063825200017364858692655596224240408300576770498315217000951739234425467065827801382258756304302316192906045796136110099058052708391287814449295704180171810679014061841761
    65537
    20630460795039294668908238526471620130828202551703327636997057867899784011738919863817055640435874976759149727165467968063812715759148727845126076552441985530736108110111448846674540490561546033930081404172567571840034896998711145562737843484995550341922413433773179020847632417716984355077274383505103652573
    */
    ZZ uno , dos , tres;
    cout << "ingresa la clave N:" << endl;
    cin >> uno;
    cout << "ingresa la clave publica:" << endl;
    cin >> dos;
    cout << "ingresa la clave privada:" << endl;
    cin >> tres;
    RSA_BLOQUES tetris(uno, dos, tres);
    string intento = tetris.cifrar("hola mi nombre es renzo estefanero y si funciona esto a ala primera me voy a pegar un tiro");
    cout << endl << endl << endl << intento << endl << endl << endl;
    string funca = tetris.descifrado(intento);
    cout << endl << endl << endl << funca << endl << endl;

}