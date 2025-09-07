#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <bits/stdc++.h>
using namespace std;

/**
 * @class capacidade
 * @brief representa a capacidade de algo como um valor inteiro.
 */
class Capacidade {
private:
    int valor; /**< valor da capacidade. */

public:
    Capacidade(int v); /**< constrói com valor inicial. */
    void def_valor(int v); /**< define o valor da capacidade. */
    int get_valor() const; /**< retorna o valor da capacidade. */
};

/**
 * @class cartao
 * @brief representa um cartão identificado por um número válido.
 */
class Cartao {
private:
    string numero; /**< número do cartão. */

    bool luhn(const string &num) const; /**< valida o número usando o algoritmo luhn (interno). */

public:
    Cartao(string n); /**< constrói um cartão com o número fornecido. */
    void def_numero(string n); /**< define o número do cartão. */
    string get_numero() const; /**< retorna o número do cartão. */
};

#endif // DOMINIOS_HPP_INCLUDED
