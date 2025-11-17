#ifndef CONTEINERS_SQLITE_HPP_INCLUDED
#define CONTEINERS_SQLITE_HPP_INCLUDED

#include "dominios.hpp"
#include "entidades.hpp"
#include "sqlite3.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @class DatabaseManager
 * @brief gerencia conexão com SQLite
 */
class DatabaseManager {
  private:
      sqlite3* db;
      string dbPath;
      bool criarTabelas();
      
  public:
      DatabaseManager(const string& path);
      ~DatabaseManager();
      
      bool conectar();
      void desconectar();
      bool executarSQL(const string& sql);
      sqlite3* getDB() {return db;}
};

/**
 * @class ContainerGerenteSQLite
 * @brief container para gerentes usando SQLite
 */
class ContainerGerenteSQLite {
  private:
      DatabaseManager& dbManager;
      
  public:
      ContainerGerenteSQLite(DatabaseManager& db) : dbManager(db) {}
      bool adicionar(const Pessoa& pessoa, const Gerente& gerente);
      bool buscar(const Email& email, Pessoa& pessoa, Gerente& gerente);
      bool atualizar(const Email& email, const Pessoa& pessoa, const Gerente& gerente);
      bool remover(const Email& email);
      bool existe(const Email& email);
};

/**
 * @class ContainerHotelSQLite
 * @brief container para hotéis usando SQLite
 */
class ContainerHotelSQLite {
  private:
      DatabaseManager& dbManager;
      
  public:
      ContainerHotelSQLite(DatabaseManager& db) : dbManager(db) {}
      bool adicionar(const Hotel& hotel, const Email& emailGerente);
      bool buscar(const Codigo& codigo, Hotel& hotel);
      bool atualizar(const Codigo& codigo, const Hotel& hotel);
      bool remover(const Codigo& codigo);
      bool existe(const Codigo& codigo);
      vector<Hotel> listarPorGerente(const Email& emailGerente);
      string obterEmailGerente(const Codigo& codigoHotel);
};

/**
 * @class ContainerQuartoSQLite
 * @brief container para quartos usando SQLite
 */
class ContainerQuartoSQLite {
  private:
      DatabaseManager& dbManager;
      
  public:
      ContainerQuartoSQLite(DatabaseManager& db) : dbManager(db) {}
      bool adicionar(const Quarto& quarto, const Codigo& codigoHotel);
      bool buscar(const Numero& numero, const Codigo& codigoHotel, Quarto& quarto);
      bool atualizar(const Numero& numero, const Codigo& codigoHotel, const Quarto& quarto);
      bool remover(const Numero& numero, const Codigo& codigoHotel);
      bool existe(const Numero& numero, const Codigo& codigoHotel);
      vector<Quarto> listarPorHotel(const Codigo& codigoHotel);
};

/**
 * @class ContainerReservaSQLite
 * @brief container para reservas usando SQLite
 */
class ContainerReservaSQLite {
  private:
      DatabaseManager& dbManager;
      
  public:
      ContainerReservaSQLite(DatabaseManager& db) : dbManager(db) {}
      bool adicionar(const Reserva& reserva, const Codigo& codigoHotel, const Numero& numeroQuarto);
      bool buscar(const Codigo& codigo, Reserva& reserva);
      bool atualizar(const Codigo& codigo, const Reserva& reserva, const Codigo& codigoHotel, const Numero& numeroQuarto);
      bool remover(const Codigo& codigo);
      bool existe(const Codigo& codigo);
      vector<Reserva> listarPorHotel(const Codigo& codigoHotel);
      bool verificarConflito(const Numero& numeroQuarto, const Codigo& codigoHotel,
                            const Data& checkIn, const Data& checkOut,
                            const Codigo& codigoReservaExcluir);
};

/**
 * @class ContainerHospedeSQLite
 * @brief container para hóspedes usando SQLite
 */
class ContainerHospedeSQLite {
  private:
      DatabaseManager& dbManager;
      
  public:
      ContainerHospedeSQLite(DatabaseManager& db) : dbManager(db) {}
      bool adicionar(const Pessoa& pessoa, const Hospede& hospede);
      bool buscar(const Email& email, Pessoa& pessoa, Hospede& hospede);
      bool atualizar(const Email& email, const Pessoa& pessoa, const Hospede& hospede);
      bool remover(const Email& email);
      bool existe(const Email& email);
      vector<pair<Pessoa, Hospede>> listarTodos();
};

#endif // CONTEINERS_SQLITE_HPP_INCLUDED
