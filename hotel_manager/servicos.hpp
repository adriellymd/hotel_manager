#ifndef SERVICOS_HPP_INCLUDED
#define SERVICOS_HPP_INCLUDED

#include "interfaces.hpp"
#include "conteiners.hpp"

/**
 * @class ServicoAutenticacaoSQLite
 * @brief Implementa autenticação de gerentes
 */
class ServicoAutenticacaoSQLite : public IServicoAutenticacao {
private:
    ContainerGerenteSQLite &containerGerente;

public:
    ServicoAutenticacaoSQLite(ContainerGerenteSQLite &cg) : containerGerente(cg) {}
    bool autenticar(const Email &email, const Senha &senha) override;
};

/**
 * @class ServicoGerenteSQLite
 * @brief Implementa operações com gerentes
 */
class ServicoGerenteSQLite : public IServicoGerente {
private:
    ContainerGerenteSQLite &containerGerente;

public:
    ServicoGerenteSQLite(ContainerGerenteSQLite &cg) : containerGerente(cg) {}

    Resultado criar(const Pessoa &pessoa, const Gerente &gerente) override;
    Resultado ler(const Email &email, Pessoa &pessoa, Gerente &gerente) override;
    Resultado editar(const Email &email, const Pessoa &pessoa, const Gerente &gerente) override;
    Resultado excluir(const Email &email) override;
};

/**
 * @class ServicoHotelSQLite
 * @brief Implementa operações com hotéis
 */
class ServicoHotelSQLite : public IServicoHotel {
private:
    ContainerHotelSQLite &containerHotel;
    ContainerGerenteSQLite &containerGerente;

public:
    ServicoHotelSQLite(ContainerHotelSQLite &ch, ContainerGerenteSQLite &cg)
        : containerHotel(ch), containerGerente(cg) {}

    Resultado criar(const Hotel &hotel, const Email &emailGerente) override;
    Resultado ler(const Codigo &codigo, Hotel &hotel) override;
    Resultado editar(const Codigo &codigo, const Hotel &hotel) override;
    Resultado excluir(const Codigo &codigo) override;
    vector<Hotel> listar(const Email &emailGerente) override;
};

/**
 * @class ServicoQuartoSQLite
 * @brief Implementa operações com quartos
 */
class ServicoQuartoSQLite : public IServicoQuarto {
private:
    ContainerQuartoSQLite &containerQuarto;
    ContainerHotelSQLite &containerHotel;

public:
    ServicoQuartoSQLite(ContainerQuartoSQLite &cq, ContainerHotelSQLite &ch)
        : containerQuarto(cq), containerHotel(ch) {}

    Resultado criar(const Quarto &quarto, const Codigo &codigoHotel) override;
    Resultado ler(const Numero &numero, const Codigo &codigoHotel, Quarto &quarto) override;
    Resultado editar(const Numero &numero, const Codigo &codigoHotel, const Quarto &quarto) override;
    Resultado excluir(const Numero &numero, const Codigo &codigoHotel) override;
    vector<Quarto> listar(const Codigo &codigoHotel) override;
};

/**
 * @class ServicoReservaSQLite
 * @brief Implementa operações com reservas
 */
class ServicoReservaSQLite : public IServicoReserva {
private:
    ContainerReservaSQLite &containerReserva;
    ContainerQuartoSQLite &containerQuarto;
    ContainerHotelSQLite &containerHotel;

public:
    ServicoReservaSQLite(ContainerReservaSQLite &cr, ContainerQuartoSQLite &cq, ContainerHotelSQLite &ch)
        : containerReserva(cr), containerQuarto(cq), containerHotel(ch) {}

    Resultado criar(const Reserva &reserva, const Codigo &codigoHotel) override;
    Resultado ler(const Codigo &codigo, Reserva &reserva) override;
    Resultado editar(const Codigo &codigo, const Reserva &reserva, const Codigo &codigoHotel) override;
    Resultado excluir(const Codigo &codigo) override;
    vector<Reserva> listar(const Codigo &codigoHotel) override;
    bool verificarConflito(const Numero &numeroQuarto, const Codigo &codigoHotel,
                          const Data &checkIn, const Data &checkOut,
                          const Codigo &codigoReservaExcluir = Codigo("")) override;
};

/**
 * @class ServicoHospedeSQLite
 * @brief Implementa operações com hóspedes
 */
class ServicoHospedeSQLite : public IServicoHospede {
private:
    ContainerHospedeSQLite &containerHospede;

public:
    ServicoHospedeSQLite(ContainerHospedeSQLite &ch) : containerHospede(ch) {}

    Resultado criar(const Pessoa &pessoa, const Hospede &hospede) override;
    Resultado ler(const Email &email, Pessoa &pessoa, Hospede &hospede) override;
    Resultado editar(const Email &email, const Pessoa &pessoa, const Hospede &hospede) override;
    Resultado excluir(const Email &email) override;
    vector<pair<Pessoa, Hospede>> listar() override;
};

#endif // SERVICOS_HPP_INCLUDED
