#include <bits/stdc++.h>
#include "entidades.hpp"
using namespace std;

// -------- Pessoa --------
Pessoa::Pessoa(const Nome &n, const Email &e) : nome(n), email(e) {}
void Pessoa::set_nome(const Nome &n) {nome = n;}
Nome Pessoa::get_nome() const {return nome;}

void Pessoa::set_email(const Email &e) {email = e;}
Email Pessoa::get_email() const {return email;}

// -------- Gerente --------
Gerente::Gerente(const Ramal &r, const Senha &s) : ramal(r), senha(s) {}
void Gerente::set_ramal(const Ramal &r) {ramal = r;}
Ramal Gerente::get_ramal() const {return ramal;}

void Gerente::set_senha(const Senha &s) {senha = s;}
Senha Gerente::get_senha() const {return senha;}

// -------- Hotel --------
Hotel::Hotel(const Nome &n, const Endereco &e,const Telefone &t,const Codigo &c) : nome(n), endereco(e), telefone(t),codigo(c) {}
void Hotel::set_nome(const Nome &n) {nome = n;}
Nome Hotel::get_nome() const {return nome;}

void Hotel::set_endereco(const Endereco &e) {endereco = e;}
Endereco Hotel::get_endereco() const {return endereco;}

void Hotel::set_telefone(const Telefone &t) {telefone = t;}
Telefone Hotel::get_telefone() const {return telefone;}

void Hotel::set_codigo(const Codigo &c) {codigo = c;}
Codigo Hotel::get_codigo() const {return codigo;}

// -------- Quarto --------
Quarto::Quarto(const Numero &n, const Capacidade &c,const Dinheiro &d,const Ramal &r) : numero(n), capacidade(c) , diaria(d) ,ramal(r) {}
void Quarto::set_numero(const Numero &n) {numero = n;}
Numero Quarto::get_numero() const {return numero;}

void Quarto::set_capacidade(const Capacidade &c) {capacidade = c;}
Capacidade Quarto::get_capacidade() const {return capacidade;}

void Quarto::set_diaria(const Dinheiro& d) {diaria = d;}
Dinheiro Quarto::get_diaria() const {return diaria;}

void Quarto::set_ramal(const Ramal &r) {ramal = r;}
Ramal Quarto::get_ramal() const {return ramal;}

// -------- Reserva --------
Reserva::Reserva(const Codigo &cod, const Data &in, const Data &out, 
                 const Pessoa &hosp, const Quarto &quart, const Dinheiro &valor)
    : codigo(cod), check_in(in), check_out(out), hospede(hosp), quarto(quart), valor_total(valor) {}

void Reserva::set_codigo(const Codigo &cod) {
    codigo = cod;
}

Codigo Reserva::get_codigo() const {
    return codigo;
}

void Reserva::set_check_in(const Data &in) {
    check_in = in;
}

Data Reserva::get_check_in() const {
    return check_in;
}

void Reserva::set_check_out(const Data &out) {
    check_out = out;
}

Data Reserva::get_check_out() const {
    return check_out;
}

void Reserva::set_hospede(const Pessoa &hosp) {
    hospede = hosp;
}

Pessoa Reserva::get_hospede() const {
    return hospede;
}

void Reserva::set_quarto(const Quarto &quart) {
    quarto = quart;
}

Quarto Reserva::get_quarto() const {
    return quarto;
}

void Reserva::set_valor_total(const Dinheiro &valor) {
    valor_total = valor;
}

Dinheiro Reserva::get_valor_total() const {
    return valor_total;
}
