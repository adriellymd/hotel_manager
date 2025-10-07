#include "entidades.hpp"

// -------- Pessoa --------
Pessoa::Pessoa(const Nome &n, const Email &e) : nome(n), email(e) {}
void Pessoa::set_nome(const Nome &n) {nome = n;}
Nome Pessoa::get_nome() const {return nome;}

void Pessoa::set_email(const Email &e) {email = e;}
Email Pessoa::get_email() const {return email;}

