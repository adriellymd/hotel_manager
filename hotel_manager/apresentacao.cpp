#include <bits/stdc++.h>
#include "apresentacao.hpp"
using namespace std;

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ApresentacaoAutenticacao::executar() {
    int opcao;
    do {
        cout << "\n--- SISTEMA DE GESTAO DE HOTEIS ---" << endl;
        cout << "1. Criar conta" << endl;
        cout << "2. Fazer login" << endl;
        cout << "0. Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        limparBuffer();

        switch(opcao) {
            case 1: criarConta(); break;
            case 2: if(fazerLogin()) return; break;
            case 0: cout << "Encerrando..." << endl; break;
            default: cout << "Invalid!" << endl;
        }
    } while(opcao != 0);
}

void ApresentacaoAutenticacao::criarConta() {
    cout << "\n--- CRIAR CONTA ---" << endl;
    try {
        string nome, email, senha;
        int ramal;

        cout << "Nome: ";
        getline(cin, nome);
        cout << "Email: ";
        getline(cin, email);
        cout << "Senha: ";
        getline(cin, senha);
        cout << "Ramal: ";
        cin >> ramal;
        limparBuffer();

        Pessoa pessoa{Nome(nome), Email(email)};
        Gerente gerente{Ramal(ramal), Senha(senha)};

        Resultado resultado = servicoGerente->criar(pessoa, gerente);
        if(resultado == Resultado::SUCESSO) cout << "Conta criada com sucesso!" << endl;
        else if(resultado == Resultado::EMAIL_JA_EXISTE) cout << "Erro: Email ja cadastrado!" << endl;
        else cout << "Erro ao criar conta!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

bool ApresentacaoAutenticacao::fazerLogin() {
    cout << "\n--- LOGIN ---" << endl;
    try {
        string email, senha;
        cout << "Email: ";
        getline(cin, email);
        cout << "Senha: ";
        getline(cin, senha);

        Email e{email};
        Senha s{senha};

        if(servicoAuth->autenticar(e, s)) {
            emailAutenticado = new Email(e);
            cout << "Login realizado com sucesso!" << endl;
            return 1;
        }
        else {
            cout << "Email ou senha incorretos!" << endl;
            return 0;
        }
    }
    catch(const invalid_argument &e) {
        cout << "Erro: " << e.what() << endl;
        return 0;
    }
}

// ----- ApresentacaoGerente -----
void ApresentacaoGerente::menuGerente() {
    int opcao;
    do {
        cout << "\n--- MENU GERENTE ---" << endl;
        cout << "1. Ver meus dados" << endl;
        cout << "2. Editar meus dados" << endl;
        cout << "3. Excluir conta" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        limparBuffer();

        switch(opcao) {
            case 1: lerDados(); break;
            case 2: editarDados(); break;
            case 3: excluirConta(); return;
            case 0: break;
            default: cout << "Invalido!" << endl;
        }
    } while(opcao != 0);
}

void ApresentacaoGerente::lerDados() {
    cout << "\n--- MEUS DADOS ---" << endl;
    Pessoa pessoa;
    Gerente gerente;

    if(servico->ler(*emailLogado, pessoa, gerente) == Resultado::SUCESSO) {
        cout << "Nome: " << pessoa.get_nome().get_nome() << endl;
        cout << "Email: " << pessoa.get_email().get_email() << endl;
        cout << "Ramal: " << gerente.get_ramal().get_ramal() << endl;
    }
    else cout << "Erro ao buscar dados!" << endl;
}

void ApresentacaoGerente::editarDados() {
    cout << "\n--- EDITAR DADOS ---" << endl;
    try {
        string nome, senha;
        int ramal;

        cout << "Novo nome: ";
        getline(cin, nome);
        cout << "Nova senha: ";
        getline(cin, senha);
        cout << "Novo ramal: ";
        cin >> ramal;
        limparBuffer();

        Pessoa pessoa{Nome(nome), *emailLogado};
        Gerente gerente{Ramal(ramal), Senha(senha)};

        if(servico->editar(*emailLogado, pessoa, gerente) == Resultado::SUCESSO) cout << "Dados atualizados com sucesso!" << endl;
        else cout << "Erro ao atualizar dados!" << endl;
    }
    catch(const invalid_argument &e) {
        cout << "Erro: " << e.what() << endl;
    }
}

void ApresentacaoGerente::excluirConta() {
    cout << "\n--- EXCLUIR CONTA ---" << endl;
    cout << "Tem certeza? (s/n): ";
    char conf;
    cin >> conf;
    limparBuffer();

    if(conf == 'S' || conf == 's') {
        if(servico->excluir(*emailLogado) == Resultado::SUCESSO) cout << "Conta excluida com sucesso!" << endl;
        else cout << "Erro ao excluir conta!" << endl;
    }
}

// ----- ApresentacaoHotel -----
void ApresentacaoHotel::menuHotel() {
    int opcao;
    do {
        cout << "\n--- MENU HOTEL ---" << endl;
        cout << "1. Criar hotel" << endl;
        cout << "2. Ver dados do hotel" << endl;
        cout << "3. Editar hotel" << endl;
        cout << "4. Excluir hotel" << endl;
        cout << "5. Listar meus hoteis" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        limparBuffer();

        switch(opcao) {
            case 1: criar(); break;
            case 2: ler(); break;
            case 3: editar(); break;
            case 4: excluir(); break;
            case 5: listar(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void ApresentacaoHotel::criar() {
    cout << "\n--- CRIAR HOTEL ---" << endl;
    try {
        string nome, endereco, telefone, codigo;

        cout << "Nome: ";
        getline(cin, nome);
        cout << "Endereco: ";
        getline(cin, endereco);
        cout << "Telefone : ";
        getline(cin, telefone);
        cout << "Codigo : ";
        getline(cin, codigo);

        Hotel hotel{Nome(nome), Endereco(endereco), Telefone(telefone), Codigo(codigo)};

        Resultado resultado = servico->criar(hotel, *emailLogado);
        if(resultado == Resultado::SUCESSO) cout << "Hotel criado com sucesso!" << endl;
        else if(resultado == Resultado::CODIGO_JA_EXISTE) cout << "Erro: Codigo ja existe!" << endl;
        else cout << "Erro ao criar hotel!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoHotel::ler() {
    cout << "\n--- VER HOTEL ---" << endl;
    try {
        string codigo;
        cout << "Codigo do hotel: ";
        getline(cin, codigo);

        Hotel hotel;
        if(servico->ler(Codigo{codigo}, hotel) == Resultado::SUCESSO) { // ✔ corrigido
            cout << "Nome: " << hotel.get_nome().get_nome() << endl;
            cout << "Endereco: " << hotel.get_endereco().get_endereco() << endl;
            cout << "Telefone: " << hotel.get_telefone().get_telefone() << endl;
            cout << "Codigo: " << hotel.get_codigo().get_codigo() << endl;
        }
        else cout << "Hotel nao encontrado!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoHotel::editar() {
    cout << "\n--- EDITAR HOTEL ---" << endl;
    try {
        string codigo, nome, endereco, telefone;
        cout << "Codigo do hotel: ";
        getline(cin, codigo);
        cout << "Novo nome: ";
        getline(cin, nome);
        cout << "Novo endereco: ";
        getline(cin, endereco);
        cout << "Novo telefone: ";
        getline(cin, telefone);

        Hotel hotel{Nome(nome), Endereco(endereco), Telefone(telefone), Codigo(codigo)};

        if(servico->editar(Codigo{codigo}, hotel) == Resultado::SUCESSO) cout << "Hotel atualizado com sucesso!" << endl;
        else cout << "Erro ao atualizar hotel!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoHotel::excluir() {
    cout << "\n--- EXCLUIR HOTEL ---" << endl;
    try {
        string codigo;
        cout << "Codigo do hotel: ";
        getline(cin, codigo);

        if(servico->excluir(Codigo{codigo}) == Resultado::SUCESSO) cout << "Hotel excluido com sucesso!" << endl;
        else cout << "Erro ao excluir hotel!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoHotel::listar() {
    cout << "\n--- MEUS HOTEIS ---" << endl;
    vector<Hotel> hoteis = servico->listar(*emailLogado);

    if(hoteis.empty()) cout << "Nenhum hotel cadastrado." << endl;
    else {
        for(const auto &hotel : hoteis) {
            cout << "\nCodigo: " << hotel.get_codigo().get_codigo() << endl;
            cout << "Nome: " << hotel.get_nome().get_nome() << endl;
            cout << "Endereco: " << hotel.get_endereco().get_endereco() << endl;
            cout << "Telefone: " << hotel.get_telefone().get_telefone() << endl;
            cout << "---" << endl;
        }
    }
}

// ----- ApresentacaoPrincipal -----
void ApresentacaoPrincipal::executar() {
    apAuth->executar();
    if(apAuth->getEmailAutenticado() != nullptr) menuPrincipal();
}

void ApresentacaoPrincipal::menuPrincipal() {
    int opcao;
    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Gerenciar minha conta" << endl;
        cout << "2. Gerenciar hoteis" << endl;
        cout << "3. Gerenciar quartos" << endl;
        cout << "4. Gerenciar reservas" << endl;
        cout << "5. Gerenciar hospedes" << endl;
        cout << "0. Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        limparBuffer();

        switch(opcao) {
            case 1: apGerente->menuGerente(); break;
            case 2: apHotel->menuHotel(); break;
            case 3: apQuarto->menuQuarto(); break;
            case 4: apReserva->menuReserva(); break;
            case 5: apHospede->menuHospede(); break;
            case 0: cout << "Saindo..." << endl; break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

// ----- ApresentacaoQuarto -----
void ApresentacaoQuarto::menuQuarto() {
    int opcao;
    do {
        cout << "\n--- MENU QUARTO ---" << endl;
        cout << "1. Criar quarto" << endl;
        cout << "2. Ver dados do quarto" << endl;
        cout << "3. Editar quarto" << endl;
        cout << "4. Excluir quarto" << endl;
        cout << "5. Listar quartos de um hotel" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        limparBuffer();

        switch(opcao) {
            case 1: criar(); break;
            case 2: ler(); break;
            case 3: editar(); break;
            case 4: excluir(); break;
            case 5: listar(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void ApresentacaoQuarto::criar() {
    cout << "\n--- CRIAR QUARTO ---" << endl;
    try {
        string codigoHotel, diaria;
        int numeroQuarto, capacidade, ramal;

        cout << "Codigo do hotel: ";
        getline(cin, codigoHotel);
        cout << "Numero do quarto: ";
        cin >> numeroQuarto;
        cout << "Capacidade: ";
        cin >> capacidade;
        limparBuffer();
        cout << "Diaria: ";
        getline(cin, diaria);
        cout << "Ramal: ";
        cin >> ramal;
        limparBuffer();

        Quarto quarto{Numero(numeroQuarto), Capacidade(capacidade), Dinheiro(diaria), Ramal(ramal)};

        Resultado resultado = servico->criar(quarto, Codigo{codigoHotel});
        if(resultado == Resultado::SUCESSO) cout << "Quarto criado com sucesso!" << endl;
        else if(resultado == Resultado::CODIGO_JA_EXISTE) cout << "Erro: Numero de quarto ja existe neste hotel!" << endl;
        else cout << "Erro ao criar quarto!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoQuarto::ler() {
    cout << "\n--- VER QUARTO ---" << endl;
    try {
        string codigoHotel;
        int numeroQuarto;
        cout << "Codigo do hotel: ";
        getline(cin, codigoHotel);
        cout << "Numero do quarto: ";
        cin >> numeroQuarto;
        limparBuffer();

        Quarto quarto;
        if(servico->ler(Numero{numeroQuarto}, Codigo{codigoHotel}, quarto) == Resultado::SUCESSO) {
            cout << "Numero: " << quarto.get_numero().get_numero() << endl;
            cout << "Capacidade: " << quarto.get_capacidade().get_capacidade() << " pessoa(s)" << endl;

            int dinheiroInt = quarto.get_diaria().get_dinheiro();
            cout << "Diaria: R$ " << (dinheiroInt / 100) << "," << (dinheiroInt % 100 < 10 ? "0" : "") << (dinheiroInt % 100) << endl;
            cout << "Ramal: " << quarto.get_ramal().get_ramal() << endl;
        }
        else cout << "Quarto nao encontrado!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoQuarto::editar() {
    cout << "\n--- EDITAR QUARTO ---" << endl;
    try {
        string codigoHotel, diaria;
        int numeroQuarto, capacidade, ramal;

        cout << "Codigo do hotel: ";
        getline(cin, codigoHotel);
        cout << "Numero do quarto: ";
        cin >> numeroQuarto;
        cout << "Nova capacidade: ";
        cin >> capacidade;
        limparBuffer();
        cout << "Nova diaria: ";
        getline(cin, diaria);
        cout << "Novo ramal: ";
        cin >> ramal;
        limparBuffer();

        Quarto quarto{Numero(numeroQuarto), Capacidade(capacidade), Dinheiro(diaria), Ramal(ramal)};

        if(servico->editar(Numero{numeroQuarto}, Codigo{codigoHotel}, quarto) == Resultado::SUCESSO)
            cout << "Quarto atualizado com sucesso!" << endl;
        else cout << "Erro ao atualizar quarto!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoQuarto::excluir() {
    cout << "\n--- EXCLUIR QUARTO ---" << endl;
    try {
        string codigoHotel;
        int numeroQuarto;
        cout << "Codigo do hotel: ";
        getline(cin, codigoHotel);
        cout << "Numero do quarto: ";
        cin >> numeroQuarto;
        limparBuffer();

        if(servico->excluir(Numero{numeroQuarto}, Codigo{codigoHotel}) == Resultado::SUCESSO)
            cout << "Quarto excluido com sucesso!" << endl;
        else cout << "Erro ao excluir quarto!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoQuarto::listar() {
    cout << "\n--- QUARTOS DO HOTEL ---" << endl;
    try {
        string codigoHotel;
        cout << "Codigo do hotel: ";
        getline(cin, codigoHotel);

        vector<Quarto> quartos = servico->listar(Codigo{codigoHotel});

        if(quartos.empty()) cout << "Nenhum quarto cadastrado neste hotel." << endl;
        else {
            for(const auto &quarto : quartos) {
                cout << "\nNumero: " << quarto.get_numero().get_numero() << endl;
                cout << "Capacidade: " << quarto.get_capacidade().get_capacidade() << " pessoa(s)" << endl;

                // Formatar dinheiro para exibição
                int dinheiroInt = quarto.get_diaria().get_dinheiro();
                cout << "Diaria: R$ " << (dinheiroInt / 100) << ","
                     << (dinheiroInt % 100 < 10 ? "0" : "") << (dinheiroInt % 100) << endl;
                cout << "Ramal: " << quarto.get_ramal().get_ramal() << endl;
                cout << "---" << endl;
            }
        }
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

// ----- ApresentacaoReserva -----
void ApresentacaoReserva::menuReserva() {
    int opcao;
    do {
        cout << "\n--- MENU RESERVA ---" << endl;
        cout << "1. Criar reserva" << endl;
        cout << "2. Ver dados da reserva" << endl;
        cout << "3. Editar reserva" << endl;
        cout << "4. Excluir reserva" << endl;
        cout << "5. Listar reservas de um hotel" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        limparBuffer();

        switch(opcao) {
            case 1: criar(); break;
            case 2: ler(); break;
            case 3: editar(); break;
            case 4: excluir(); break;
            case 5: listar(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void ApresentacaoReserva::criar() {
    cout << "\n--- CRIAR RESERVA ---" << endl;
    try {
        string codigoReserva, codigoHotel, emailHospede;
        string dataInicio, dataFim, valorTotal;
        int numeroQuarto;

        cout << "Codigo da reserva (10 caracteres): ";
        getline(cin, codigoReserva);
        cout << "Codigo do hotel: ";
        getline(cin, codigoHotel);
        cout << "Numero do quarto: ";
        cin >> numeroQuarto;
        limparBuffer();
        cout << "Email do hospede: ";
        getline(cin, emailHospede);
        cout << "Data de inicio: ";
        getline(cin, dataInicio);
        cout << "Data de fim: ";
        getline(cin, dataFim);
        cout << "Valor total: ";
        getline(cin, valorTotal);

        Pessoa hospede;
        Hospede hospedeData;
        if(servicoHospede->ler(Email{emailHospede}, hospede, hospedeData) != Resultado::SUCESSO) {
            cout << "Erro: Hospede nao encontrado!" << endl;
            return;
        }

        Quarto quarto;
        quarto.set_numero(Numero(numeroQuarto));
        Reserva reserva{Codigo(codigoReserva), Data(dataInicio), Data(dataFim), hospede, quarto, Dinheiro(valorTotal)};

        Resultado resultado = servico->criar(reserva, Codigo{codigoHotel});
        if(resultado == Resultado::SUCESSO) cout << "Reserva criada com sucesso!" << endl;
        else if(resultado == Resultado::CODIGO_JA_EXISTE) cout << "Erro: Codigo de reserva ja existe!" << endl;
        else if(resultado == Resultado::CONFLITO_RESERVA) cout << "Erro: Quarto ja reservado neste periodo!" << endl;
        else cout << "Erro ao criar reserva!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoReserva::ler() {
    cout << "\n--- VER RESERVA ---" << endl;
    try {
        string codigoReserva;
        cout << "Codigo da reserva: ";
        getline(cin, codigoReserva);

        Reserva reserva;
        if(servico->ler(Codigo{codigoReserva}, reserva) == Resultado::SUCESSO) {
            cout << "Codigo: " << reserva.get_codigo().get_codigo() << endl;
            cout << "Data inicio: " << reserva.get_check_in().get_data() << endl;
            cout << "Data fim: " << reserva.get_check_out().get_data() << endl;
            cout << "Hospede: " << reserva.get_hospede().get_email().get_email() << endl;

            int dinheiroInt = reserva.get_valor_total().get_dinheiro();
            cout << "Valor: R$ " << (dinheiroInt / 100) << "," << (dinheiroInt % 100 < 10 ? "0" : "") << (dinheiroInt % 100) << endl;
        }
        else cout << "Reserva nao encontrada!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoReserva::editar() {
    cout << "\n--- EDITAR RESERVA ---" << endl;
    try {
        string codigoReserva, codigoHotel, dataInicio, dataFim, valorTotal, emailHospede;
        int numeroQuarto;

        cout << "Codigo da reserva: ";
        getline(cin, codigoReserva);
        cout << "Codigo do hotel: ";
        getline(cin, codigoHotel);
        cout << "Numero do quarto: ";
        cin >> numeroQuarto;
        limparBuffer();
        cout << "Email do hospede: ";
        getline(cin, emailHospede);
        cout << "Nova data de inicio: ";
        getline(cin, dataInicio);
        cout << "Nova data de fim: ";
        getline(cin, dataFim);
        cout << "Novo valor total: ";
        getline(cin, valorTotal);

        Pessoa hospede;
        Hospede hospedeData;
        if(servicoHospede->ler(Email{emailHospede}, hospede, hospedeData) != Resultado::SUCESSO) {
            cout << "Erro: Hospede nao encontrado!" << endl;
            return;
        }

        Quarto quarto;
        quarto.set_numero(Numero(numeroQuarto));
        Reserva reserva{Codigo(codigoReserva), Data(dataInicio), Data(dataFim), hospede, quarto, Dinheiro(valorTotal)};

        if(servico->editar(Codigo{codigoReserva}, reserva, Codigo{codigoHotel}) == Resultado::SUCESSO)
            cout << "Reserva atualizada com sucesso!" << endl;
        else cout << "Erro ao atualizar reserva!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoReserva::excluir() {
    cout << "\n--- EXCLUIR RESERVA ---" << endl;
    try {
        string codigoReserva;
        cout << "Codigo da reserva: ";
        getline(cin, codigoReserva);

        if(servico->excluir(Codigo{codigoReserva}) == Resultado::SUCESSO)
            cout << "Reserva excluida com sucesso!" << endl;
        else cout << "Erro ao excluir reserva!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoReserva::listar() {
    cout << "\n--- RESERVAS DO HOTEL ---" << endl;
    try {
        string codigoHotel;
        cout << "Codigo do hotel: ";
        getline(cin, codigoHotel);

        vector<Reserva> reservas = servico->listar(Codigo{codigoHotel});

        if(reservas.empty()) cout << "Nenhuma reserva cadastrada para este hotel." << endl;
        else {
            for(const auto &reserva : reservas) {
                cout << "\nCodigo: " << reserva.get_codigo().get_codigo() << endl;
                cout << "Data inicio: " << reserva.get_check_in().get_data() << endl;
                cout << "Data fim: " << reserva.get_check_out().get_data() << endl;
                cout << "Hospede: " << reserva.get_hospede().get_email().get_email() << endl;

                int dinheiroInt = reserva.get_valor_total().get_dinheiro();
                cout << "Valor: R$ " << (dinheiroInt / 100) << "," << (dinheiroInt % 100 < 10 ? "0" : "") << (dinheiroInt % 100) << endl;
                cout << "---" << endl;
            }
        }
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

// ----- ApresentacaoHospede -----
void ApresentacaoHospede::menuHospede() {
    int opcao;
    do {
        cout << "\n--- MENU HOSPEDE ---" << endl;
        cout << "1. Criar hospede" << endl;
        cout << "2. Ver dados do hospede" << endl;
        cout << "3. Editar hospede" << endl;
        cout << "4. Excluir hospede" << endl;
        cout << "5. Listar todos os hospedes" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        limparBuffer();

        switch(opcao) {
            case 1: criar(); break;
            case 2: ler(); break;
            case 3: editar(); break;
            case 4: excluir(); break;
            case 5: listar(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void ApresentacaoHospede::criar() {
    cout << "\n--- CRIAR HOSPEDE ---" << endl;
    try {
        string nome, email, endereco, cartao;

        cout << "Nome: ";
        getline(cin, nome);
        cout << "Email: ";
        getline(cin, email);
        cout << "Endereco: ";
        getline(cin, endereco);
        cout << "Cartao (16 digitos): ";
        getline(cin, cartao);

        Pessoa pessoa{Nome(nome), Email(email)};
        Hospede hospede{Endereco(endereco), Cartao(cartao)};

        Resultado resultado = servico->criar(pessoa, hospede);
        if(resultado == Resultado::SUCESSO) cout << "Hospede criado com sucesso!" << endl;
        else if(resultado == Resultado::EMAIL_JA_EXISTE) cout << "Erro: Email ja cadastrado!" << endl;
        else cout << "Erro ao criar hospede!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoHospede::ler() {
    cout << "\n--- VER HOSPEDE ---" << endl;
    try {
        string email;
        cout << "Email do hospede: ";
        getline(cin, email);

        Pessoa pessoa;
        Hospede hospede;
        if(servico->ler(Email{email}, pessoa, hospede) == Resultado::SUCESSO) {
            cout << "Nome: " << pessoa.get_nome().get_nome() << endl;
            cout << "Email: " << pessoa.get_email().get_email() << endl;
            cout << "Endereco: " << hospede.get_endereco().get_endereco() << endl;
            cout << "Cartao: " << hospede.get_cartao().get_cartao() << endl;
        }
        else cout << "Hospede nao encontrado!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoHospede::editar() {
    cout << "\n--- EDITAR HOSPEDE ---" << endl;
    try {
        string email, nome, endereco, cartao;

        cout << "Email do hospede: ";
        getline(cin, email);
        cout << "Novo nome: ";
        getline(cin, nome);
        cout << "Novo endereco: ";
        getline(cin, endereco);
        cout << "Novo cartao: ";
        getline(cin, cartao);

        Pessoa pessoa{Nome(nome), Email(email)};
        Hospede hospede{Endereco(endereco), Cartao(cartao)};

        if(servico->editar(Email{email}, pessoa, hospede) == Resultado::SUCESSO)
            cout << "Hospede atualizado com sucesso!" << endl;
        else cout << "Erro ao atualizar hospede!" << endl;
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoHospede::excluir() {
    cout << "\n--- EXCLUIR HOSPEDE ---" << endl;
    try {
        string email;
        cout << "Email do hospede: ";
        getline(cin, email);

        cout << "Tem certeza? (s/n): ";
        char conf;
        cin >> conf;
        limparBuffer();

        if(conf == 'S' || conf == 's') {
            if(servico->excluir(Email{email}) == Resultado::SUCESSO) cout << "Hospede excluido com sucesso!" << endl;
            else cout << "Erro ao excluir hospede!" << endl;
        }
    }
    catch(const invalid_argument &e) {cout << "Erro: " << e.what() << endl;}
}

void ApresentacaoHospede::listar() {
    cout << "\n--- TODOS OS HOSPEDES ---" << endl;
    vector<pair<Pessoa, Hospede>> hospedes = servico->listar();

    if(hospedes.empty()) cout << "Nenhum hospede cadastrado." << endl;
    else {
        for(int i = 0; i < (int)hospedes.size(); i++) {
            cout << "\nNome: " << hospedes[i].first.get_nome().get_nome() << endl;
            cout << "Email: " << hospedes[i].first.get_email().get_email() << endl;
            cout << "Endereco: " << hospedes[i].second.get_endereco().get_endereco() << endl;
            cout << "Cartao: " << hospedes[i].second.get_cartao().get_cartao() << endl;
            cout << "---" << endl;
        }
    }
}

