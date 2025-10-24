#ifndef INTERFACES_H
#define INTERFACES_H

#include <bits/stdc++.h>
#include "entidades.hpp"
using namespace std;


class servico_gerente {
public:
    virtual ~servico_gerente() = default;

    virtual bool criar_gerente(const Gerente& g) = 0;
    virtual bool autenticar_gerente(const Ramal& r, const Senha& s) const = 0;
    virtual Gerente obter_gerente_ramal(const Ramal& r) const = 0;
    virtual bool atualizar_gerente(const Gerente& g) = 0;
    virtual bool remover_gerente(const Ramal& r) = 0;
};


#endif
