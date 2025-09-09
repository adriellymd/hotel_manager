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
        int capacidade; /**< valor da capacidade. */
    public:
        Capacidade(int v); /**< constrói com valor inicial. */
        void def_capacidade(int v); /**< define o valor da capacidade. */
        int get_capacidade() const; /**< retorna o valor da capacidade. */
};

/**
 * @class cartao
 * @brief representa um cartão identificado por um número válido.
 */
class Cartao {
    private:
        string cartao; /**< número do cartão. */
        bool luhn(const string &num) const; /**< valida o número usando o algoritmo luhn (interno). */
    public:
        Cartao(string n); /**< constrói um cartão com o número fornecido. */
        void def_cartao(string n); /**< define o número do cartão. */
        string get_cartao() const; /**< retorna o número do cartão. */
};

/**
 * @class senha
 * @brief representa uma senha de 5 caracteres com regras especificas
 *
 * regras:
 * - 1 letra minuscula, 1 letra maiuscula, 1 digito, 1 caracter especial (!"#$%&?)
 * - letras nao podem ser consecutivas
 * - digitos nao podem ser consecutivos
 */
class Senha {
    private:
        string senha; /**< senha */
        bool regras(const string &s) const; /**< verifica regras da senha */
    public:
        Senha(string s); /**< construtor valida e armazena */
        void def_senha(string s); /**< define valor e valida */
        string get_senha() const; /**< retorna a senha */
};

/**
 * @class email
 * @brief representa um endereço de email válido.
 */
class Email {
    private:
        string email; /**< email */
    public:
        Email(string s); /**< construtor valida e armazena */
        void def_email(string s); /**< define valor e valida */
        string get_email() const; /**< retorna o email */
        bool validar(const string &s) const; /**< verifica regras do email */
};

#endif // DOMINIOS_HPP_INCLUDED
