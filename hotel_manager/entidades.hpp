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

#endif // ENTIDADES_HPP_INCLUDED
