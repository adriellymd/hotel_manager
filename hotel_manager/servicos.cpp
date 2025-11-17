#include "servicos.hpp"
using namespace std;

// ----- ServicoAutenticacaoSQLite -----
bool ServicoAutenticacaoSQLite::autenticar(const Email& email, const Senha& senha) {
    Pessoa pessoa;
    Gerente gerente;

    if(!containerGerente.buscar(email, pessoa, gerente)) {return 0;}
    return gerente.get_senha().get_senha() == senha.get_senha();
}

// ----- ServicoGerenteSQLite -----
Resultado ServicoGerenteSQLite::criar(const Pessoa& pessoa, const Gerente& gerente) {
    if(containerGerente.existe(pessoa.get_email())) {return Resultado::EMAIL_JA_EXISTE;}
    if(containerGerente.adicionar(pessoa, gerente)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

Resultado ServicoGerenteSQLite::ler(const Email& email, Pessoa& pessoa, Gerente& gerente) {
    if(containerGerente.buscar(email, pessoa, gerente)) {return Resultado::SUCESSO;}
    return Resultado::EMAIL_NAO_ENCONTRADO;
}

Resultado ServicoGerenteSQLite::editar(const Email& email, const Pessoa& pessoa, const Gerente& gerente) {
    if(!containerGerente.existe(email)) {return Resultado::EMAIL_NAO_ENCONTRADO;}
    if(containerGerente.atualizar(email, pessoa, gerente)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

Resultado ServicoGerenteSQLite::excluir(const Email& email) {
    if(!containerGerente.existe(email)) {return Resultado::EMAIL_NAO_ENCONTRADO;}
    if(containerGerente.remover(email)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

// ----- ServicoHotelSQLite -----
Resultado ServicoHotelSQLite::criar(const Hotel& hotel, const Email& emailGerente) {
    if(!containerGerente.existe(emailGerente)) {return Resultado::EMAIL_NAO_ENCONTRADO;}
    if(containerHotel.existe(hotel.get_codigo())) {return Resultado::CODIGO_JA_EXISTE;}
    if(containerHotel.adicionar(hotel, emailGerente)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

Resultado ServicoHotelSQLite::ler(const Codigo& codigo, Hotel& hotel) {
    if(containerHotel.buscar(codigo, hotel)) {return Resultado::SUCESSO;}
    return Resultado::CODIGO_NAO_ENCONTRADO;
}

Resultado ServicoHotelSQLite::editar(const Codigo& codigo, const Hotel& hotel) {
    if(!containerHotel.existe(codigo)) {return Resultado::CODIGO_NAO_ENCONTRADO;}
    if(containerHotel.atualizar(codigo, hotel)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

Resultado ServicoHotelSQLite::excluir(const Codigo& codigo) {
    if(!containerHotel.existe(codigo)) {return Resultado::CODIGO_NAO_ENCONTRADO;}
    if(containerHotel.remover(codigo)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

vector<Hotel> ServicoHotelSQLite::listar(const Email& emailGerente) {
    return containerHotel.listarPorGerente(emailGerente);
}

// ----- ServicoQuartoSQLite -----
Resultado ServicoQuartoSQLite::criar(const Quarto& quarto, const Codigo& codigoHotel) {
    if(!containerHotel.existe(codigoHotel)) {return Resultado::CODIGO_NAO_ENCONTRADO;}
    if(containerQuarto.existe(quarto.get_numero(), codigoHotel)) {return Resultado::CODIGO_JA_EXISTE;}
    if(containerQuarto.adicionar(quarto, codigoHotel)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

Resultado ServicoQuartoSQLite::ler(const Numero& numero, const Codigo& codigoHotel, Quarto& quarto) {
    if(containerQuarto.buscar(numero, codigoHotel, quarto)) {return Resultado::SUCESSO;}
    return Resultado::CODIGO_NAO_ENCONTRADO;
}

Resultado ServicoQuartoSQLite::editar(const Numero& numero, const Codigo& codigoHotel, const Quarto& quarto) {
    if(!containerQuarto.existe(numero, codigoHotel)) {return Resultado::CODIGO_NAO_ENCONTRADO;}
    if(containerQuarto.atualizar(numero, codigoHotel, quarto)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

Resultado ServicoQuartoSQLite::excluir(const Numero& numero, const Codigo& codigoHotel) {
    if(!containerQuarto.existe(numero, codigoHotel)) {return Resultado::CODIGO_NAO_ENCONTRADO;}
    if(containerQuarto.remover(numero, codigoHotel)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

vector<Quarto> ServicoQuartoSQLite::listar(const Codigo& codigoHotel) {
    return containerQuarto.listarPorHotel(codigoHotel);
}

// ----- ServicoReservaSQLite -----
Resultado ServicoReservaSQLite::criar(const Reserva& reserva, const Codigo& codigoHotel) {
    // Verifica se o código da reserva já existe
    if(containerReserva.existe(reserva.get_codigo())) {
        return Resultado::CODIGO_JA_EXISTE;
    }

    // Extrai o número do quarto da reserva
    Numero numeroQuarto = reserva.get_quarto().get_numero();

    // Verifica se o hotel existe
    if(!containerHotel.existe(codigoHotel)) {
        return Resultado::CODIGO_NAO_ENCONTRADO;
    }

    // Verifica se o quarto existe naquele hotel
    if(!containerQuarto.existe(numeroQuarto, codigoHotel)) {
        return Resultado::CODIGO_NAO_ENCONTRADO;
    }

    // Verifica se há conflito de datas (quarto já reservado no período)
    if(verificarConflito(numeroQuarto, codigoHotel,
                        reserva.get_check_in(),
                        reserva.get_check_out(),
                        Codigo(""))) {
        return Resultado::CONFLITO_RESERVA;
    }

    // Adiciona a reserva no banco de dados
    if(containerReserva.adicionar(reserva, codigoHotel, numeroQuarto)) {
        return Resultado::SUCESSO;
    }

    return Resultado::FALHA;
}

Resultado ServicoReservaSQLite::ler(const Codigo& codigo, Reserva& reserva) {
    if(containerReserva.buscar(codigo, reserva)) {return Resultado::SUCESSO;}
    return Resultado::CODIGO_NAO_ENCONTRADO;
}

Resultado ServicoReservaSQLite::editar(const Codigo& codigo, const Reserva& reserva, const Codigo& codigoHotel) {
    // Verifica se a reserva existe
    if(!containerReserva.existe(codigo)) {
        return Resultado::CODIGO_NAO_ENCONTRADO;
    }

    // Extrai o número do quarto da reserva
    Numero numeroQuarto = reserva.get_quarto().get_numero();

    // Verifica se o hotel existe
    if(!containerHotel.existe(codigoHotel)) {
        return Resultado::CODIGO_NAO_ENCONTRADO;
    }

    // Verifica se o quarto existe naquele hotel
    if(!containerQuarto.existe(numeroQuarto, codigoHotel)) {
        return Resultado::CODIGO_NAO_ENCONTRADO;
    }

    // Verifica se há conflito de datas (exclui a própria reserva da verificação)
    if(verificarConflito(numeroQuarto, codigoHotel,
                        reserva.get_check_in(),
                        reserva.get_check_out(),
                        codigo)) {
        return Resultado::CONFLITO_RESERVA;
    }

    // Atualiza a reserva no banco de dados
    if(containerReserva.atualizar(codigo, reserva, codigoHotel, numeroQuarto)) {
        return Resultado::SUCESSO;
    }

    return Resultado::FALHA;
}

Resultado ServicoReservaSQLite::excluir(const Codigo& codigo) {
    if(!containerReserva.existe(codigo)) {return Resultado::CODIGO_NAO_ENCONTRADO;}
    if(containerReserva.remover(codigo)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

vector<Reserva> ServicoReservaSQLite::listar(const Codigo& codigoHotel) {
    return containerReserva.listarPorHotel(codigoHotel);
}

bool ServicoReservaSQLite::verificarConflito(const Numero& numeroQuarto, const Codigo& codigoHotel,const Data& checkIn, const Data& checkOut, const Codigo& codigoReservaExcluir) {
    return containerReserva.verificarConflito(numeroQuarto, codigoHotel, checkIn, checkOut, codigoReservaExcluir);
}

// ----- ServicoHospedeSQLite -----
Resultado ServicoHospedeSQLite::criar(const Pessoa& pessoa, const Hospede& hospede) {
    if(containerHospede.existe(pessoa.get_email())) {return Resultado::EMAIL_JA_EXISTE;}
    if(containerHospede.adicionar(pessoa, hospede)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

Resultado ServicoHospedeSQLite::ler(const Email& email, Pessoa& pessoa, Hospede& hospede) {
    if(containerHospede.buscar(email, pessoa, hospede)) {return Resultado::SUCESSO;}
    return Resultado::EMAIL_NAO_ENCONTRADO;
}

Resultado ServicoHospedeSQLite::editar(const Email& email, const Pessoa& pessoa, const Hospede& hospede) {
    if(!containerHospede.existe(email)) {return Resultado::EMAIL_NAO_ENCONTRADO;}
    if(containerHospede.atualizar(email, pessoa, hospede)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

Resultado ServicoHospedeSQLite::excluir(const Email& email) {
    if(!containerHospede.existe(email)) {return Resultado::EMAIL_NAO_ENCONTRADO;}
    if(containerHospede.remover(email)) {return Resultado::SUCESSO;}
    return Resultado::FALHA;
}

vector<pair<Pessoa, Hospede>> ServicoHospedeSQLite::listar() {
    return containerHospede.listarTodos();
}
