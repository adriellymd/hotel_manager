#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <bits/stdc++.h>
using namespace std;

/**
 * @class capacidade
 * @brief representa a capacidade de algo como um valor inteiro.
 */
class Capacidade
{
    private:
        int capacidade; /**< valor da capacidade. */
    public:
        Capacidade(int v);          /**< constrói com valor inicial. */
        void def_capacidade(int v); /**< define o valor da capacidade. */
        int get_capacidade() const; /**< retorna o valor da capacidade. */
};

/**
 * @class cartao
 * @brief representa um cartão identificado por um número válido.
 */
class Cartao
{
    private:
        string cartao;                      /**< número do cartão. */
        bool luhn(const string &num) const; /**< valida o número usando o algoritmo luhn (interno). */
    public:
        Cartao(string n);          /**< constrói um cartão com o número fornecido. */
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
class Senha
{
    private:
        string senha;                       /**< senha */
        bool regras(const string &s) const; /**< verifica regras da senha */
    public:
        Senha(string s);          /**< construtor valida e armazena */
        void def_senha(string s); /**< define valor e valida */
        string get_senha() const; /**< retorna a senha */
};

/**
 * @class email
 * @brief representa um endereço de email válido.
 */
class Email
{
    private:
        string email; /**< email */
    public:
        Email(string s);                     /**< construtor valida e armazena */
        void def_email(string s);            /**< define valor e valida */
        string get_email() const;            /**< retorna o email */
        bool validar(const string &s) const; /**< verifica regras do email */
};

/**
 * @class nome
 * @brief representa um nome valido(5 a 20 caracteres).
 */
class Nome
{
    private:
        string nome;                         /**< nome armazenado */
        void validar(const string &n) const; /**< valida regras do nome */
    public:
        Nome(string n);          /**< construtor valida e armazena */
        void def_nome(string n); /**< define o nome */
        string get_nome() const; /**< retortna o nome */
};

/**
 * @class Ramal
 * @brief representa um ramal valido (00 a 50).
 */
class Ramal
{
private:
    int ramal;                 /**< valor do ramal */
    void validar(int r) const; /**< valida intervalo do ramal */
public:
    Ramal(int r);          /**< construtor valida e armazena */
    void def_ramal(int r); /**< define o ramal */
    int get_ramal() const; /**< retorna o ramal */
};

/**
 * @class Numero
 * @brief representa um número valido (001 a 999).
 */
class Numero
{
private:
    int numero;                /**< valor do número */
    void validar(int n) const; /**< valida intervalo do número */
public:
    Numero(int n);          /**< construtor valida e armazena */
    void def_numero(int n); /**< define o número */
    int get_numero() const; /**< retorna o número */
};

#endif // DOMINIOS_HPP_INCLUDED
