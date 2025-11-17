#include <bits/stdc++.h>
#include "conteiners.hpp"


using namespace std;

// ----- DatabaseManager -----
DatabaseManager::DatabaseManager(const string& path) : db(nullptr), dbPath(path) {}

DatabaseManager::~DatabaseManager() {
    desconectar();
}

bool DatabaseManager::conectar() {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if(rc != SQLITE_OK) {
        cerr << "Erro ao abrir banco: " << sqlite3_errmsg(db) << endl;
        return 0;
    }
    return criarTabelas();
}

void DatabaseManager::desconectar() {
    if(db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::executarSQL(const string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if(rc != SQLITE_OK) {
        cerr << "Erro SQL: " << errMsg << endl;
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}

bool DatabaseManager::criarTabelas() {
    string sql = R"(
        CREATE TABLE IF NOT EXISTS gerentes (
            email TEXT PRIMARY KEY,
            nome TEXT NOT NULL,
            ramal INTEGER NOT NULL,
            senha TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS hoteis (
            codigo TEXT PRIMARY KEY,
            nome TEXT NOT NULL,
            endereco TEXT NOT NULL,
            telefone TEXT NOT NULL,
            email_gerente TEXT NOT NULL,
            FOREIGN KEY (email_gerente) REFERENCES gerentes(email) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS quartos (
            numero INTEGER NOT NULL,
            codigo_hotel TEXT NOT NULL,
            capacidade INTEGER NOT NULL,
            diaria INTEGER NOT NULL,
            ramal INTEGER NOT NULL,
            PRIMARY KEY (numero, codigo_hotel),
            FOREIGN KEY (codigo_hotel) REFERENCES hoteis(codigo) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS hospedes (
            email TEXT PRIMARY KEY,
            nome TEXT NOT NULL,
            endereco TEXT NOT NULL,
            cartao TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS reservas (
            codigo TEXT PRIMARY KEY,
            check_in TEXT NOT NULL,
            check_out TEXT NOT NULL,
            email_hospede TEXT NOT NULL,
            codigo_hotel TEXT NOT NULL,
            numero_quarto INTEGER NOT NULL,
            valor_total INTEGER NOT NULL,
            FOREIGN KEY (email_hospede) REFERENCES hospedes(email) ON DELETE CASCADE,
            FOREIGN KEY (codigo_hotel, numero_quarto) REFERENCES quartos(codigo_hotel, numero) ON DELETE CASCADE
        );

        CREATE INDEX IF NOT EXISTS idx_hoteis_gerente ON hoteis(email_gerente);
        CREATE INDEX IF NOT EXISTS idx_quartos_hotel ON quartos(codigo_hotel);
        CREATE INDEX IF NOT EXISTS idx_reservas_hotel ON reservas(codigo_hotel);
    )";

    return executarSQL(sql);
}

// ----- ContainerGerenteSQLite -----
bool ContainerGerenteSQLite::adicionar(const Pessoa& pessoa, const Gerente& gerente) {
    string sql = "INSERT INTO gerentes (email, nome, ramal, senha) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_text(stmt, 1, pessoa.get_email().get_email().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pessoa.get_nome().get_nome().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, gerente.get_ramal().get_ramal());
    sqlite3_bind_text(stmt, 4, gerente.get_senha().get_senha().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerGerenteSQLite::buscar(const Email& email, Pessoa& pessoa, Gerente& gerente) {
    string sql = "SELECT nome, ramal, senha FROM gerentes WHERE email = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_text(stmt, 1, email.get_email().c_str(), -1, SQLITE_TRANSIENT);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int ramal = sqlite3_column_int(stmt, 1);
            string senha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            pessoa.set_nome(Nome(nome));
            pessoa.set_email(email);
            gerente.set_ramal(Ramal(ramal));
            gerente.set_senha(Senha(senha));

            sqlite3_finalize(stmt);
            return 1;
        }
        catch (...) {
            sqlite3_finalize(stmt);
            return 0;
        }
    }

    sqlite3_finalize(stmt);
    return 0;
}

bool ContainerGerenteSQLite::atualizar(const Email& email, const Pessoa& pessoa, const Gerente& gerente) {
    string sql = "UPDATE gerentes SET nome = ?, ramal = ?, senha = ? WHERE email = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, pessoa.get_nome().get_nome().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, gerente.get_ramal().get_ramal());
    sqlite3_bind_text(stmt, 3, gerente.get_senha().get_senha().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, email.get_email().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerGerenteSQLite::remover(const Email& email) {
    string sql = "DELETE FROM gerentes WHERE email = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}

    sqlite3_bind_text(stmt, 1, email.get_email().c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerGerenteSQLite::existe(const Email& email) {
    string sql = "SELECT COUNT(*) FROM gerentes WHERE email = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, email.get_email().c_str(), -1, SQLITE_TRANSIENT);

    bool existe = 0;
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return existe;
}

// ----- ContainerHotelSQLite -----
bool ContainerHotelSQLite::adicionar(const Hotel& hotel, const Email& emailGerente) {
    string sql = "INSERT INTO hoteis (codigo, nome, endereco, telefone, email_gerente) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, hotel.get_codigo().get_codigo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hotel.get_nome().get_nome().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, hotel.get_endereco().get_endereco().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, hotel.get_telefone().get_telefone().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, emailGerente.get_email().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerHotelSQLite::buscar(const Codigo& codigo, Hotel& hotel) {
    string sql = "SELECT nome, endereco, telefone FROM hoteis WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}

    sqlite3_bind_text(stmt, 1, codigo.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            string endereco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string telefone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            hotel.set_nome(Nome(nome));
            hotel.set_endereco(Endereco(endereco));
            hotel.set_telefone(Telefone(telefone));
            hotel.set_codigo(codigo);

            sqlite3_finalize(stmt);
            return 1;
        }
        catch (...) {
            sqlite3_finalize(stmt);
            return 0;
        }
    }

    sqlite3_finalize(stmt);
    return 0;
}

bool ContainerHotelSQLite::atualizar(const Codigo& codigo, const Hotel& hotel) {
    string sql = "UPDATE hoteis SET nome = ?, endereco = ?, telefone = ? WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}

    sqlite3_bind_text(stmt, 1, hotel.get_nome().get_nome().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hotel.get_endereco().get_endereco().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, hotel.get_telefone().get_telefone().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, codigo.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerHotelSQLite::remover(const Codigo& codigo) {
    string sql = "DELETE FROM hoteis WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_text(stmt, 1, codigo.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerHotelSQLite::existe(const Codigo& codigo) {
    string sql = "SELECT COUNT(*) FROM hoteis WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, codigo.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    bool existe = 0;
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return existe;
}

vector<Hotel> ContainerHotelSQLite::listarPorGerente(const Email& emailGerente) {
    vector<Hotel> hoteis;
    string sql = "SELECT codigo, nome, endereco, telefone FROM hoteis WHERE email_gerente = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return hoteis;}

    sqlite3_bind_text(stmt, 1, emailGerente.get_email().c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            string codigo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string endereco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string telefone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

            Hotel hotel{Nome(nome), Endereco(endereco), Telefone(telefone), Codigo(codigo)};
            hoteis.push_back(hotel);
        }
        catch (...) {}
    }

    sqlite3_finalize(stmt);
    return hoteis;
}

string ContainerHotelSQLite::obterEmailGerente(const Codigo& codigoHotel) {
    string sql = "SELECT email_gerente FROM hoteis WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return "";}

    sqlite3_bind_text(stmt, 1, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    string email;
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return email;
}

// ----- ContainerQuartoSQLite -----
bool ContainerQuartoSQLite::adicionar(const Quarto& quarto, const Codigo& codigoHotel) {
    string sql = "INSERT INTO quartos (numero, codigo_hotel, capacidade, diaria, ramal) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_int(stmt, 1, quarto.get_numero().get_numero());
    sqlite3_bind_text(stmt, 2, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, quarto.get_capacidade().get_capacidade());
    sqlite3_bind_int(stmt, 4, quarto.get_diaria().get_dinheiro());
    sqlite3_bind_int(stmt, 5, quarto.get_ramal().get_ramal());

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerQuartoSQLite::buscar(const Numero& numero, const Codigo& codigoHotel, Quarto& quarto) {
    string sql = "SELECT capacidade, diaria, ramal FROM quartos WHERE numero = ? AND codigo_hotel = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}

    sqlite3_bind_int(stmt, 1, numero.get_numero());
    sqlite3_bind_text(stmt, 2, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            int capacidade = sqlite3_column_int(stmt, 0);
            int diaria = sqlite3_column_int(stmt, 1);
            int ramal = sqlite3_column_int(stmt, 2);

            ostringstream oss;
            oss << (diaria / 100) << "," << (diaria % 100 < 10 ? "0" : "") << (diaria % 100);

            quarto.set_numero(numero);
            quarto.set_capacidade(Capacidade(capacidade));
            quarto.set_diaria(Dinheiro(oss.str()));
            quarto.set_ramal(Ramal(ramal));

            sqlite3_finalize(stmt);
            return 1;
        }
        catch (...) {
            sqlite3_finalize(stmt);
            return 0;
        }
    }

    sqlite3_finalize(stmt);
    return 0;
}

bool ContainerQuartoSQLite::atualizar(const Numero& numero, const Codigo& codigoHotel, const Quarto& quarto) {
    string sql = "UPDATE quartos SET capacidade = ?, diaria = ?, ramal = ? WHERE numero = ? AND codigo_hotel = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_int(stmt, 1, quarto.get_capacidade().get_capacidade());
    sqlite3_bind_int(stmt, 2, quarto.get_diaria().get_dinheiro());
    sqlite3_bind_int(stmt, 3, quarto.get_ramal().get_ramal());
    sqlite3_bind_int(stmt, 4, numero.get_numero());
    sqlite3_bind_text(stmt, 5, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerQuartoSQLite::remover(const Numero& numero, const Codigo& codigoHotel) {
    string sql = "DELETE FROM quartos WHERE numero = ? AND codigo_hotel = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_int(stmt, 1, numero.get_numero());
    sqlite3_bind_text(stmt, 2, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerQuartoSQLite::existe(const Numero& numero, const Codigo& codigoHotel) {
    string sql = "SELECT COUNT(*) FROM quartos WHERE numero = ? AND codigo_hotel = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_int(stmt, 1, numero.get_numero());
    sqlite3_bind_text(stmt, 2, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    bool existe = 0;
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return existe;
}

vector<Quarto> ContainerQuartoSQLite::listarPorHotel(const Codigo& codigoHotel) {
    vector<Quarto> quartos;
    string sql = "SELECT numero, capacidade, diaria, ramal FROM quartos WHERE codigo_hotel = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return quartos;}
    sqlite3_bind_text(stmt, 1, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            int numero = sqlite3_column_int(stmt, 0);
            int capacidade = sqlite3_column_int(stmt, 1);
            int diaria = sqlite3_column_int(stmt, 2);
            int ramal = sqlite3_column_int(stmt, 3);

            ostringstream oss;
            oss << (diaria / 100) << "," << (diaria % 100 < 10 ? "0" : "") << (diaria % 100);

            Quarto quarto{Numero(numero), Capacidade(capacidade), Dinheiro(oss.str()), Ramal(ramal)};
            quartos.push_back(quarto);
        }
        catch (...) {}
    }

    sqlite3_finalize(stmt);
    return quartos;
}

// ----- ContainerReservaSQLite -----
bool ContainerReservaSQLite::adicionar(const Reserva& reserva, const Codigo& codigoHotel, const Numero& numeroQuarto) {
    string sql = "INSERT INTO reservas (codigo, check_in, check_out, email_hospede, codigo_hotel, numero_quarto, valor_total) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, reserva.get_codigo().get_codigo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, reserva.get_check_in().get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, reserva.get_check_out().get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, reserva.get_hospede().get_email().get_email().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, numeroQuarto.get_numero());
    sqlite3_bind_int(stmt, 7, reserva.get_valor_total().get_dinheiro());

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerReservaSQLite::buscar(const Codigo& codigo, Reserva& reserva) {
    string sql = "SELECT check_in, check_out, email_hospede, codigo_hotel, numero_quarto, valor_total FROM reservas WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, codigo.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            string checkIn = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            string checkOut = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string emailHosp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int valorTotal = sqlite3_column_int(stmt, 5);

            ostringstream oss;
            oss << (valorTotal / 100) << "," << (valorTotal % 100 < 10 ? "0" : "") << (valorTotal % 100);

            Pessoa hospede;
            hospede.set_email(Email(emailHosp));
            Quarto quarto;
            reserva.set_codigo(codigo);
            reserva.set_check_in(Data(checkIn));
            reserva.set_check_out(Data(checkOut));
            reserva.set_hospede(hospede);
            reserva.set_quarto(quarto);
            reserva.set_valor_total(Dinheiro(oss.str()));

            sqlite3_finalize(stmt);
            return 1;
        }
        catch (...) {
            sqlite3_finalize(stmt);
            return 0;
        }
    }

    sqlite3_finalize(stmt);
    return 0;
}

bool ContainerReservaSQLite::atualizar(const Codigo& codigo, const Reserva& reserva, const Codigo& codigoHotel, const Numero& numeroQuarto) {
    string sql = "UPDATE reservas SET check_in = ?, check_out = ?, email_hospede = ?, "
                 "codigo_hotel = ?, numero_quarto = ?, valor_total = ? WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, reserva.get_check_in().get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, reserva.get_check_out().get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, reserva.get_hospede().get_email().get_email().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, numeroQuarto.get_numero());
    sqlite3_bind_int(stmt, 6, reserva.get_valor_total().get_dinheiro());
    sqlite3_bind_text(stmt, 7, codigo.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerReservaSQLite::remover(const Codigo& codigo) {
    string sql = "DELETE FROM reservas WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, codigo.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerReservaSQLite::existe(const Codigo& codigo) {
    string sql = "SELECT COUNT(*) FROM reservas WHERE codigo = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, codigo.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    bool existe = 0;
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return existe;
}

vector<Reserva> ContainerReservaSQLite::listarPorHotel(const Codigo& codigoHotel) {
    vector<Reserva> reservas;
    string sql = "SELECT codigo, check_in, check_out, email_hospede, numero_quarto, valor_total FROM reservas WHERE codigo_hotel = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return reservas;}
    sqlite3_bind_text(stmt, 1, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            string codigo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            string checkIn = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string checkOut = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string emailHosp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            int valorTotal = sqlite3_column_int(stmt, 5);

            ostringstream oss;
            oss << (valorTotal / 100) << "," << (valorTotal % 100 < 10 ? "0" : "") << (valorTotal % 100);

            Pessoa hospede;
            hospede.set_email(Email(emailHosp));
            Quarto quarto;
            Reserva reserva(Codigo(codigo), Data(checkIn), Data(checkOut), hospede, quarto, Dinheiro(oss.str()));
            reservas.push_back(reserva);
        }
        catch (...) {}
    }

    sqlite3_finalize(stmt);
    return reservas;
}

bool ContainerReservaSQLite::verificarConflito(const Numero& numeroQuarto, const Codigo& codigoHotel, const Data& checkIn, const Data& checkOut, const Codigo& codigoReservaExcluir) {
    string sql = "SELECT COUNT(*) FROM reservas WHERE "
                 "codigo_hotel = ? AND numero_quarto = ? AND "
                 "codigo != ? AND "
                 "((check_in <= ? AND check_out > ?) OR "
                 " (check_in < ? AND check_out >= ?) OR "
                 " (check_in >= ? AND check_out <= ?));";

    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 1;}
    sqlite3_bind_text(stmt, 1, codigoHotel.get_codigo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, numeroQuarto.get_numero());
    sqlite3_bind_text(stmt, 3, codigoReservaExcluir.get_codigo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, checkIn.get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, checkIn.get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, checkOut.get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, checkOut.get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, checkIn.get_data().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 9, checkOut.get_data().c_str(), -1, SQLITE_TRANSIENT);

    bool conflito = 0;
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        conflito = sqlite3_column_int(stmt, 0) > 0;
    }
    sqlite3_finalize(stmt);
    return conflito;
}

// ----- ContainerHospedeSQLite -----
bool ContainerHospedeSQLite::adicionar(const Pessoa& pessoa, const Hospede& hospede) {
    string sql = "INSERT INTO hospedes (email, nome, endereco, cartao) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, pessoa.get_email().get_email().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pessoa.get_nome().get_nome().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, hospede.get_endereco().get_endereco().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, hospede.get_cartao().get_cartao().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool ContainerHospedeSQLite::buscar(const Email& email, Pessoa& pessoa, Hospede& hospede) {
    string sql = "SELECT nome, endereco, cartao FROM hospedes WHERE email = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, email.get_email().c_str(), -1, SQLITE_TRANSIENT);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            string endereco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string cartao = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            pessoa.set_nome(Nome(nome));
            pessoa.set_email(email);
            hospede.set_endereco(Endereco(endereco));
            hospede.set_cartao(Cartao(cartao));

            sqlite3_finalize(stmt);
            return 1;
        }
        catch (...) {
            sqlite3_finalize(stmt);
            return 0;
        }
    }

    sqlite3_finalize(stmt);
    return 0;
}

bool ContainerHospedeSQLite::atualizar(const Email& email, const Pessoa& pessoa, const Hospede& hospede) {
    string sql = "UPDATE hospedes SET nome = ?, endereco = ?, cartao = ? WHERE email = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, pessoa.get_nome().get_nome().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hospede.get_endereco().get_endereco().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, hospede.get_cartao().get_cartao().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, email.get_email().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool ContainerHospedeSQLite::remover(const Email& email) {
    string sql = "DELETE FROM hospedes WHERE email = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, email.get_email().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool ContainerHospedeSQLite::existe(const Email& email) {
    string sql = "SELECT COUNT(*) FROM hospedes WHERE email = ?;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return 0;}
    sqlite3_bind_text(stmt, 1, email.get_email().c_str(), -1, SQLITE_TRANSIENT);

    bool existe = 0;
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }
    sqlite3_finalize(stmt);
    return existe;
}

vector<pair<Pessoa, Hospede>> ContainerHospedeSQLite::listarTodos() {
    vector<pair<Pessoa, Hospede>> hospedes;
    string sql = "SELECT email, nome, endereco, cartao FROM hospedes;";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(dbManager.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {return hospedes;}

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        try {
            string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string endereco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string cartao = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

            Pessoa pessoa{Nome(nome), Email(email)};
            Hospede hospede{Endereco(endereco), Cartao(cartao)};

            hospedes.push_back(make_pair(pessoa, hospede));
        }
        catch (...) {}
    }
    sqlite3_finalize(stmt);
    return hospedes;
}
