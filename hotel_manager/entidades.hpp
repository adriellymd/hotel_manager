#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

#include "dominios.hpp"

/**
 * @class pessoa
 * @brief representa uma pessoa do sistema.
 */
class Pessoa {
private:
    Nome nome; /**< nome da pessoa */
    Email email; /**< email da pessoa (chave primária) */
public:
    Pessoa() = default;
    Pessoa(const Nome &n, const Email &e); /**< construtor com atributos */

    void set_nome(const Nome &n); /**< define o nome */
    Nome get_nome() const; /**< retorna o nome */
    void set_email(const Email &e); /**< define o email */
    Email get_email() const; /**< retorna o email */
};

/**
 * @class gerente
 * @brief representa um gerente do sistema.
 */
class Gerente {
private:
    Ramal ramal; /**< ramal do gerente */
    Senha senha; /**< senha do gerente */
public:
    Gerente() = default;
    Gerente(const Ramal &r, const Senha &s); /**< construtor com atributos */

    void set_ramal(const Ramal &r); /**< define o ramal */
    Ramal get_ramal() const; /**< retorna o ramal */
    void set_senha(const Senha &s); /**< define a senha */
    Senha get_senha() const; /**< retorna a senha */
};

/**
 * @class hotel
 * @brief representa um hotel do sistema.
 */
class Hotel {
private:
    Nome nome; /**< nome do hotel */
    Endereco endereco; /**< endereco do hotel */
    Telefone telefone; /**< telefone do hotel */
    Codigo codigo; /**< codigo do hotel */
public:
    Hotel() = default;
    Hotel(const Nome &n, const Endereco &e,const Telefone &t,const Codigo &c); /**< construtor com atributos */

    void set_nome(const Nome &n); /**< define o nome */
    Nome get_nome() const; /**< retorna o nome */
    void set_endereco(const Endereco &e); /**< define o endereco */
    Endereco get_endereco() const; /**< retorna o endereco */
    void set_telefone(const Telefone &t); /**< define o telefone*/
    Telefone get_telefone() const; /**< retorna o endereco*/
    void set_codigo(const Codigo &c); /**< define o codigo*/
    Codigo get_codigo() const; /**< retorna o codigo*/

};

/**
 * @class quarto
 * @brief representa um quarto do sistema.
 */
class Quarto {
private:
    Numero numero; /**< numero do quarto */
    Capacidade capacidade; /**< capacidade do quarto */
    Dinheiro diaria; /**< diaria do quarto */
    Ramal ramal; /**< ramal do quarto */
public:
    Quarto() = default;
    Quarto(const Numero &n, const Capacidade &c,const Dinheiro &d,const Ramal &r); /**< construtor com atributos */

    void set_numero(const Numero &n); /**< define o numero */
    Numero get_numero() const; /**< retorna o numero */
    void set_capacidade(const Capacidade &c); /**< define a capacidade */
    Capacidade get_capacidade() const; /**< retorna a capacidade */
    void set_diaria(const Dinheiro &d); /**< define a diaria*/
    Dinheiro get_diaria() const; /**< retorna a diaria*/
    void set_ramal(const Ramal &r); /**< define o ramal*/
    Ramal get_ramal() const; /**< retorna o ramal*/

};

#endif // ENTIDADES_HPP_INCLUDED
