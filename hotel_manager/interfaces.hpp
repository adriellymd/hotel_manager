#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "dominios.hpp"
#include "entidades.hpp"
#include <vector>
using namespace std;

// ----- CÓDIGOS DE RESULTADO -----
enum class Resultado {
    SUCESSO, FALHA, EMAIL_JA_EXISTE, EMAIL_NAO_ENCONTRADO, 
    CODIGO_JA_EXISTE, CODIGO_NAO_ENCONTRADO, AUTENTICACAO_FALHOU, CONFLITO_RESERVA
};

// ----- INTERFACES CAMADA DE SERVIÇO -----

/**
 * @interface IServicoAutenticacao
 * @brief interface para autenticação de gerentes
 */
class IServicoAutenticacao {
  public:
      virtual ~IServicoAutenticacao() = default;
      /**
       * @brief Autentica gerente no sistema
       * @param email Email do gerente
       * @param senha Senha do gerente
       * @return true se autenticação bem-sucedida
       */
      virtual bool autenticar(const Email &email, const Senha &senha) = 0;
};

/**
 * @interface IServicoGerente
 * @brief interface para operações com gerentes
 */
class IServicoGerente {
  public:
      virtual ~IServicoGerente() = default;
      virtual Resultado criar(const Pessoa &pessoa, const Gerente &gerente) = 0;
      virtual Resultado ler(const Email &email, Pessoa &pessoa, Gerente &gerente) = 0;
      virtual Resultado editar(const Email &email, const Pessoa &pessoa, const Gerente &gerente) = 0;
      virtual Resultado excluir(const Email &email) = 0;
};

/**
 * @interface IServicoHotel
 * @brief interface para operações com hotéis
 */
class IServicoHotel {
  public:
      virtual ~IServicoHotel() = default;
      virtual Resultado criar(const Hotel &hotel, const Email &emailGerente) = 0;
      virtual Resultado ler(const Codigo &codigo, Hotel &hotel) = 0;
      virtual Resultado editar(const Codigo &codigo, const Hotel &hotel) = 0;
      virtual Resultado excluir(const Codigo &codigo) = 0;
      virtual vector<Hotel> listar(const Email &emailGerente) = 0;
};

/**
 * @interface IServicoQuarto
 * @brief interface para operações com quartos
 */
class IServicoQuarto {
public:
    virtual ~IServicoQuarto() = default;
    virtual Resultado criar(const Quarto &quarto, const Codigo &codigoHotel) = 0;
    virtual Resultado ler(const Numero &numero, const Codigo &codigoHotel, Quarto &quarto) = 0;
    virtual Resultado editar(const Numero &numero, const Codigo &codigoHotel, const Quarto &quarto) = 0;
    virtual Resultado excluir(const Numero &numero, const Codigo &codigoHotel) = 0;
    virtual vector<Quarto> listar(const Codigo &codigoHotel) = 0;
};

/**
 * @interface IServicoReserva
 * @brief interface para operações com reservas
 */
class IServicoReserva {
public:
    virtual ~IServicoReserva() = default;
    // CORRIGIDO: Adicionado parâmetro codigoHotel
    virtual Resultado criar(const Reserva &reserva, const Codigo &codigoHotel) = 0;
    virtual Resultado ler(const Codigo &codigo, Reserva &reserva) = 0;
    // CORRIGIDO: Adicionado parâmetro codigoHotel
    virtual Resultado editar(const Codigo &codigo, const Reserva &reserva, const Codigo &codigoHotel) = 0;
    virtual Resultado excluir(const Codigo &codigo) = 0;
    virtual vector<Reserva> listar(const Codigo &codigoHotel) = 0;
    virtual bool verificarConflito(const Numero &numeroQuarto, const Codigo &codigoHotel, const Data &checkIn, const Data &checkOut, const Codigo &codigoReservaExcluir = Codigo("")) = 0;
};

/**
 * @interface IServicoHospede
 * @brief Interface para operações com hóspedes
 */
class IServicoHospede {
  public:
      virtual ~IServicoHospede() = default;
      
      virtual Resultado criar(const Pessoa &pessoa, const Hospede &hospede) = 0;
      virtual Resultado ler(const Email &email, Pessoa &pessoa, Hospede &hospede) = 0;
      virtual Resultado editar(const Email &email, const Pessoa &pessoa, const Hospede &hospede) = 0;
      virtual Resultado excluir(const Email &email) = 0;
      virtual vector<pair<Pessoa, Hospede>> listar() = 0;
};

// ----- INTERFACES CAMADA DE APRESENTAÇÃO -----
/**
 * @interface IApresentacaoAutenticacao
 * @brief interface para apresentação de autenticação
 */
class IApresentacaoAutenticacao {
  public:
      virtual ~IApresentacaoAutenticacao() = default;
      virtual void executar() = 0;
};
/**
 * @interface IApresentacaoGerente
 * @brief interface para apresentação de gerentes
 */
class IApresentacaoGerente {
  public:
      virtual ~IApresentacaoGerente() = default;
      virtual void menuGerente() = 0;
};
/**
 * @interface IApresentacaoHotel
 * @brief interface para apresentação de hotéis
 */
class IApresentacaoHotel {
  public:
      virtual ~IApresentacaoHotel() = default;
      virtual void menuHotel() = 0;
};

/**
 * @interface IApresentacaoQuarto
 * @brief interface para apresentação de quartos
 */
class IApresentacaoQuarto {
  public:
      virtual ~IApresentacaoQuarto() = default;
      virtual void menuQuarto() = 0;
};

/**
 * @interface IApresentacaoReserva
 * @brief interface para apresentação de reservas
 */
class IApresentacaoReserva {
  public:
      virtual ~IApresentacaoReserva() = default;
      virtual void menuReserva() = 0;
};

/**
 * @interface IApresentacaoHospede
 * @brief interface para apresentação de hóspedes
 */
class IApresentacaoHospede {
  public:
      virtual ~IApresentacaoHospede() = default;
      virtual void menuHospede() = 0;
};

#endif // INTERFACES_HPP_INCLUDED
