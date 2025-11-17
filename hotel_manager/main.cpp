#include <bits/stdc++.h>
#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "conteiners.hpp"
#include "servicos.hpp"
#include "apresentacao.hpp"
using namespace std;

int main() {
    cout << "----------------------------------------" << endl;
    cout << "              HOTEL MANAGER" << endl;
    cout << "----------------------------------------" << endl;

    DatabaseManager dbManager("hotel_system.db");

    if(!dbManager.conectar()) {
        cerr << "ERRO: Nao foi possivel conectar ao banco de dados!" << endl;
        return 1;
    }
    cout << "Banco de dados conectado com sucesso!" << endl;

    ContainerGerenteSQLite containerGerente(dbManager);
    ContainerHotelSQLite containerHotel(dbManager);
    ContainerQuartoSQLite containerQuarto(dbManager);
    ContainerReservaSQLite containerReserva(dbManager);
    ContainerHospedeSQLite containerHospede(dbManager);

    ServicoAutenticacaoSQLite servicoAuth(containerGerente);
    ServicoGerenteSQLite servicoGerente(containerGerente);
    ServicoHotelSQLite servicoHotel(containerHotel, containerGerente);
    ServicoQuartoSQLite servicoQuarto(containerQuarto, containerHotel);
    ServicoReservaSQLite servicoReserva(containerReserva, containerQuarto, containerHotel);
    ServicoHospedeSQLite servicoHospede(containerHospede);

    ApresentacaoAutenticacao apAuth(&servicoAuth, &servicoGerente);

    cout << "\nSistema iniciado. Bem-vindo!" << endl;
    cout << "----------------------------------------\n" << endl;

    apAuth.executar();

    if(apAuth.getEmailAutenticado() != nullptr) {
        ApresentacaoGerente apGerente(&servicoGerente, apAuth.getEmailAutenticado());
        ApresentacaoHotel apHotel(&servicoHotel, apAuth.getEmailAutenticado());
        ApresentacaoQuarto apQuarto(&servicoQuarto, apAuth.getEmailAutenticado());
        ApresentacaoReserva apReserva(&servicoReserva, &servicoHospede, apAuth.getEmailAutenticado());
        ApresentacaoHospede apHospede(&servicoHospede);
        ApresentacaoPrincipal apPrincipal(&apAuth, &apGerente, &apHotel, &apQuarto, &apReserva, &apHospede);
        apPrincipal.menuPrincipal();
    }

    cout << "\n----------------------------------------" << endl;
    cout << "Sistema encerrado" << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}
