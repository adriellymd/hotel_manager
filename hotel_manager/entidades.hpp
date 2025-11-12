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

/**
 * @class Reserva
 * @brief representa uma reserva de hotel no sistema.
 */
class Reserva {
private:
    Codigo codigo; /**< código único da reserva */
    Data check_in; /**< data de entrada do hóspede */
    Data check_out; /**< data de saída do hóspede */
    Pessoa hospede; /**< hóspede que realizou a reserva */
    Quarto quarto; /**< quarto reservado */
    Dinheiro valor_total; /**< valor total da reserva */
public:
    Reserva() = default;
    Reserva(const Codigo &cod, const Data &in, const Data &out,
            const Pessoa &hosp, const Quarto &quart, const Dinheiro &valor); /**< construtor com atributos */

    // Métodos de acesso
    void set_codigo(const Codigo &cod); /**< define o código da reserva */
    Codigo get_codigo() const; /**< retorna o código da reserva */

    void set_check_in(const Data &in); /**< define a data de check-in */
    Data get_check_in() const; /**< retorna a data de check-in */

    void set_check_out(const Data &out); /**< define a data de check-out */
    Data get_check_out() const; /**< retorna a data de check-out */

    void set_hospede(const Pessoa &hosp); /**< define o hóspede */
    Pessoa get_hospede() const; /**< retorna o hóspede */

    void set_quarto(const Quarto &quart); /**< define o quarto */
    Quarto get_quarto() const; /**< retorna o quarto */

    void set_valor_total(const Dinheiro &valor); /**< define o valor total */
    Dinheiro get_valor_total() const; /**< retorna o valor total */
};

/**
 * @class Hóspede
 * @brief representa um hóspede no sistema.
 */

class Hospede {
private:
    Endereco endereco; /**< endereço de residência do hóspede */
    Cartao cartao; /** número de cartão do hóspede */

public:
    Hospede() = default;
    Hospede(const Endereco &e, const Cartao &c); /**< construtor com atributos */

    void set_endereco(const Endereco &e); /**< define o endereço */
    Endereco get_endereco() const; /**< retorna o endereço */
    void set_cartao(const Cartao &c); /**< define o cartão */
    Cartao get_cartao() const; /**< retorna o cartao */
};

#endif // ENTIDADES_HPP_INCLUDED
