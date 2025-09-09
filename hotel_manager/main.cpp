#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    // -------- Capacidade --------
    try {Capacidade c1(3); cout << "Capacidade criada: " << c1.get_capacidade() << endl;}
    catch (const invalid_argument &e) {cerr << "Erro c1: " << e.what() << endl;}

    try {Capacidade c2(5); cout << "Capacidade criada: " << c2.get_capacidade() << endl;}
    catch (const invalid_argument &e) {cerr << "Erro c2: " << e.what() << endl;}

    // -------- Cartao --------
    try {Cartao cartao1("4539578763621486"); cout << "Cartao criado: " << cartao1.get_cartao() << endl;}
    catch (const invalid_argument &e) {cerr << "Erro cartao1: " << e.what() << endl;}

    try {Cartao cartao2("1234567812345678"); cout << "Cartao criado: " << cartao2.get_cartao() << endl;}
    catch (const invalid_argument &e) {cerr << "Erro cartao2: " << e.what() << endl;}

    // -------- Senha --------
    try {Senha s1("a1B!j"); cout << "Senha criada: " << s1.get_senha() << endl;}
    catch (const invalid_argument &e) {cerr << "Erro s1: " << e.what() << endl;}

    try {Senha s2("aB11!"); cout << "Senha criada: " << s2.get_senha() << endl;}
    catch (const invalid_argument &e) {cerr << "Erro s2: " << e.what() << endl;}

    // -------- Email --------
    try {Email e1("usuario-valido@dominio.com"); cout << "Email criado: " << e1.get_email() << endl;}
    catch (const invalid_argument &e) {cerr << "Erro e1: " << e.what() << endl;}

    try {Email e2("..invalido@dominio"); cout << "Email criado: " << e2.get_email() << endl;}
    catch (const invalid_argument &e) {cerr << "Erro e2: " << e.what() << endl;}


    return 0;
}
