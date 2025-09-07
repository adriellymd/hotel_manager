#include <bits/stdc++.h>
#include "dominios.hpp"
using namespace std;

// -------- Capacidade --------
Capacidade::Capacidade(int v) {
    def_valor(v);
}

void Capacidade::def_valor(int v) {
    if (v < 1 || v > 4) {
        throw std::invalid_argument("Capacidade deve ser 1, 2, 3 ou 4."); //exceções
    }
    valor = v;
}

int Capacidade::get_valor() const {
    return valor;
}

// -------- Cartao --------
Cartao::Cartao(string n) {
    def_numero(n);
}

void Cartao::def_numero(string n) {
    if(n.size() != 16) {
        throw invalid_argument("Cartao deve ter exatamente 16 digitos.");
    }
    for(char c : n) {
        if(!isdigit(c)) {
            throw invalid_argument("Cartao deve conter apenas digitos.");
        }
    }
    if(!luhn(n)) {
        throw invalid_argument("Cartao invalido pelo algoritmo de Luhn.");
    }
    numero = n;
}

string Cartao::get_numero() const {
    return numero;
}

bool Cartao::luhn(const string &num) const {
    int soma = 0, alternar = 0;
    for(int i = num.size() - 1; i >= 0; i--) {
        int digito = num[i] - '0';
        if(alternar) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        soma += digito;
        alternar = !alternar;
    }
    return (soma % 10 == 0);
}

