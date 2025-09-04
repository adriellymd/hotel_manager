#include <iostream>
#include <stdexcept>
#include "dominios.hpp"

// Capacidade -----
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
