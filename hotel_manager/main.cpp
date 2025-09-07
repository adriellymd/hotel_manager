#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    // -------- Capacidade --------
    try {Capacidade c1(3); cout << "Capacidade criada: " << c1.get_valor() << endl;}
    catch (const invalid_argument &e) { cerr << "Erro c1: " << e.what() << endl;}

    try {Capacidade c2(5); cout << "Capacidade criada: " << c2.get_valor() << endl;}
    catch (const invalid_argument &e) { cerr << "Erro c2: " << e.what() << endl;}

    // -------- Cartao --------
    try {Cartao cartao1("4539578763621486"); cout << "Cartao criado: " << cartao1.get_numero() << endl;}
    catch (const invalid_argument &e) { cerr << "Erro cartao1: " << e.what() << endl;}

    try {Cartao cartao2("1234567812345678"); cout << "Cartao criado: " << cartao2.get_numero() << endl;}
    catch (const invalid_argument &e) { cerr << "Erro cartao2: " << e.what() << endl;}

    return 0;
}
