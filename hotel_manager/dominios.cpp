#include <bits/stdc++.h>
#include "dominios.hpp"
using namespace std;

// -------- Capacidade --------
Capacidade::Capacidade(int v) {
    def_capacidade(v);
}

void Capacidade::def_capacidade(int v) {
    if(v < 1 || v > 4) {
        throw std::invalid_argument("Capacidade deve ser 1, 2, 3 ou 4."); //exceções
    }
    capacidade = v;
}

int Capacidade::get_capacidade() const {
    return capacidade;
}

// -------- Cartao --------
Cartao::Cartao(string n) {
    def_cartao(n);
}

void Cartao::def_cartao(string n) {
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
    cartao = n;
}

string Cartao::get_cartao() const {
    return cartao;
}

bool Cartao::luhn(const string &num) const {
    int soma = 0, alternar = 0;
    for(int i = num.size() - 1; i >= 0; i--) {
        int digito = num[i] - '0';
        if(alternar) {
            digito *= 2;
            if(digito > 9) digito -= 9;
        }
        soma += digito;
        alternar = !alternar;
    }
    return (soma % 10 == 0);
}

// -------- Senha --------
Senha::Senha(string s) {
    def_senha(s);
}

void Senha::def_senha(string s) {
    if(!regras(s)) throw invalid_argument("Senha invalida");
    senha = s;
}

string Senha::get_senha() const {
    return senha;
}
bool Senha::regras(const string &s) const {
    if(s.size() != 5)
        throw invalid_argument("Senha deve ter exatamente 5 caracteres.");

    bool minn = false, mai = false, dig = false, esp = false;
    char prev = 'n';

    for(char c : s) {
        char cur;

        if(isalpha(c)) {
            cur = 'l';
            if(islower(c)) minn = 1;
            else mai = 1;
        }
        else if(isdigit(c)) { dig = true; cur = 'd'; }
        else if(string("!\"#$%&?").find(c) != string::npos) { esp = true; cur = 'e'; }
        else throw invalid_argument("Senha contem caractere invalido.");

        if((prev == cur) && (cur == 'l' || cur == 'd'))
            throw invalid_argument("Senha nao pode ter letras ou digitos consecutivos.");

        prev = cur;
    }

    if(!minn) throw invalid_argument("Senha deve conter ao menos uma letra minuscula.");
    if(!mai) throw invalid_argument("Senha deve conter ao menos uma letra maiuscula.");
    if(!dig) throw invalid_argument("Senha deve conter ao menos um digito.");
    if(!esp) throw invalid_argument("Senha deve conter ao menos um caractere especial (!\"#$%&?).");

    return true;
}
