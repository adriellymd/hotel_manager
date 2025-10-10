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
