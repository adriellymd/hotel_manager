#include <bits/stdc++.h>
#include "dominios.hpp"
using namespace std;

// -------- Capacidade --------
Capacidade::Capacidade(int v) {
    def_capacidade(v);
}

void Capacidade::def_capacidade(int v) {
    if(v < 1 || v > 4) {
        throw std::invalid_argument("Capacidade deve ser 1, 2, 3 ou 4.");
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

// -------- Email --------
Email::Email(string s) {
    def_email(s);
}

void Email::def_email(string s) {
    if(!validar(s)) throw invalid_argument("Email invalido");
    email = s;
}

string Email::get_email() const {
    return email;
}

bool Email::validar(const string &s) const {
    if((int)s.size() > 320) return 0;

    size_t id = s.find('@');
    if(id == string::npos || id != s.rfind('@')) return 0;

    string local = s.substr(0, id), dom = s.substr(id + 1);

    if(local.empty() || (int)local.size() > 64) return 0;
    if(local.front() == '.' || local.front() == '-' || local.back() == '.' || local.back() == '-') return 0;

    for(int i = 0; i < (int)local.size(); i++) {
        char c = local[i];
        if(!(isalpha(c) || isdigit(c) || c == '.' || c == '-')) return 0;
        if((c == '.' || c == '-') && (i+1 < (int)local.size())) {
            char nextC = local[i+1];
            if(nextC == '.' || nextC == '-') return 0;
        }
    }

    if(dom.empty() || (int)dom.size() > 255) return 0;

    int j = 0;
    for(int i = 0; i <= (int)dom.size(); i++) {
        if(i == (int)dom.size() || dom[i] == '.') {
            string cur = dom.substr(j, i - j);
            if(cur.empty()) return 0;
            if(cur.front() == '-' || cur.back() == '-') return 0;
            for(char c : cur) {
                if(!(isalpha(c) || isdigit(c) || c == '-')) return 0;
            }
            j = i+1;
        }
    }
    return 1;
}

// -------- Nome --------
Nome::Nome(string n) {
    def_nome(n);
}

void Nome::validar(const string &n) const {
    if(n.size() < 5 || n.size() > 20) {
        throw invalid_argument("Nome deve ter entre 5 e 20 caracteres.");
    }
    if(n.front() == ' ' || n.back() == ' ') {
        throw invalid_argument("Nome nao pode comecar ou terminar com espaco.");
    }
    for(size_t i = 0; i < n.size(); i++) {
        char c = n[i];
        if(!(isalpha(c) || c == ' ')) {
            throw invalid_argument("Nome so pode conter letras e espacos.");
        }
        if(c == ' ' && (i+1 < n.size() && !isalpha(n[i+1]))) {
            throw invalid_argument("Espaco deve ser seguido por letra.");
        }
    }
    bool novaPalavra = true;
    for(char c : n) {
        if(novaPalavra && isalpha(c) && !isupper(c)) {
            throw invalid_argument("Primeira letra de cada termo deve ser maiuscula.");
        }
        novaPalavra = (c == ' ');
    }
}

void Nome::def_nome(string n) {
    validar(n);
    nome = n;
}

string Nome::get_nome() const {
    return nome;
}

// -------- Ramal --------
Ramal::Ramal(int r) {
    def_ramal(r);
}

void Ramal::validar(int r) const {
    if(r < 0 || r > 50) {
        throw invalid_argument("Ramal deve estar entre 00 e 50.");
    }
}

void Ramal::def_ramal(int r) {
    validar(r);
    ramal = r;
}

int Ramal::get_ramal() const {
    return ramal;
}

// -------- Numero --------
Numero::Numero(int n) {
    def_numero(n);
}

void Numero::validar(int n) const {
    if(n < 1 || n > 999) {
        throw invalid_argument("Numero deve estar entre 001 e 999.");
    }
}

void Numero::def_numero(int n) {
    validar(n);
    numero = n;
}

int Numero::get_numero() const {
    return numero;
}








