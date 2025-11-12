#include <iostream>
#include "dominios.hpp"
#include "entidades.hpp"
using namespace std;

int main()
{
    // -------- Capacidade --------
    try{Capacidade c1(3);cout << "Capacidade criada: " << c1.get_capacidade() << endl;}
    catch (const invalid_argument &e){cerr << "Erro c1: " << e.what() << endl;}

    try{Capacidade c2(5);cout << "Capacidade criada: " << c2.get_capacidade() << endl;}
    catch (const invalid_argument &e){cerr << "Erro c2: " << e.what() << endl;}

    // -------- Cartao --------
    try{Cartao cartao1("4539578763621486");cout << "Cartao criado: " << cartao1.get_cartao() << endl;}
    catch (const invalid_argument &e){cerr << "Erro cartao1: " << e.what() << endl;}

    try{Cartao cartao2("1234567812345678");cout << "Cartao criado: " << cartao2.get_cartao() << endl;}
    catch (const invalid_argument &e){cerr << "Erro cartao2: " << e.what() << endl;}

    // -------- Senha --------
    try{Senha s1("a1B!j");cout << "Senha criada: " << s1.get_senha() << endl;}
    catch (const invalid_argument &e){cerr << "Erro s1: " << e.what() << endl;}

    try{Senha s2("aB11!");cout << "Senha criada: " << s2.get_senha() << endl;}
    catch (const invalid_argument &e){cerr << "Erro s2: " << e.what() << endl;}

    // -------- Email --------
    try{Email e1("usuario-valido@dominio.com");cout << "Email criado: " << e1.get_email() << endl;}
    catch (const invalid_argument &e){cerr << "Erro e1: " << e.what() << endl;}

    try{Email e2("..invalido@dominio");cout << "Email criado: " << e2.get_email() << endl;}
    catch (const invalid_argument &e){cerr << "Erro e2: " << e.what() << endl;}

    // -------- Nome --------
    try{Nome n1("Pedro Ferreira");cout << "Nome criado: " << n1.get_nome() << endl;}
    catch (const invalid_argument &e){cerr << "Erro n1: " << e.what() << endl;}

    try{Nome n2("kali123");cout << "Nome criado: " << n2.get_nome() << endl;}
    catch (const invalid_argument &e){cerr << "Erro n2: " << e.what() << endl;}

    // -------- Ramal --------
    try{Ramal r1(12);cout << "Ramal criado: " << r1.get_ramal() << endl;}
    catch (const invalid_argument &e){cerr << "Erro r1: " << e.what() << endl;}

    try{Ramal r2(60);cout << "Ramal criado: " << r2.get_ramal() << endl;}
    catch (const invalid_argument &e){cerr << "Erro r2: " << e.what() << endl;}

    // -------- Numero --------
    try{Numero num1(123);cout << "Numero criado: " << num1.get_numero() << endl;}
    catch (const invalid_argument &e){cerr << "Erro num1: " << e.what() << endl;}

    try{Numero num2(1000);cout << "Numero criado: " << num2.get_numero() << endl;}
    catch (const invalid_argument &e){cerr << "Erro num2: " << e.what() << endl;}

    // -------- Endereco --------
    try {
        Endereco end1("Rua das Flores, 123");
        cout << "Endereco criado: " << end1.get_endereco() << endl;
    } catch (const invalid_argument &e) {
        cerr << "Erro end1: " << e.what() << endl;
    }

    // -------- Data --------
    try {
        Data data1("15-MAR-2024");
        cout << "Data criada: " << data1.get_data() << endl;
    } catch (const invalid_argument &e) {
        cerr << "Erro data1: " << e.what() << endl;
    }

    // -------- Telefone --------
    try{Telefone t1("99999-9999");cout << "Telefone criado: " << t1.get_telefone() << endl;}
    catch (const invalid_argument &e){cerr << "Erro t1: " << e.what() << endl;}

    try{Telefone t2("+12345678912345");cout << "Telefone criado: " << t2.get_telefone() << endl;}
    catch (const invalid_argument &e){cerr << "Erro t2: " << e.what() << endl;}

    // -------- Dinheiro --------
    try{Dinheiro d1("2000000,00");cout << "Dinheiro criado: " << d1.get_dinheiro() << endl;}
    catch (const invalid_argument &e){cerr << "Erro d1: " << e.what() << endl;}

    try{Dinheiro d2("999,99");cout << "Dinheiro criado: " << d2.get_dinheiro() << endl;}
    catch (const invalid_argument &e){cerr << "Erro d2: " << e.what() << endl;}

    // -------- Código --------
    try{Codigo codigo1("0325");cout << "Codigo criado: " << codigo1.get_codigo() << endl;}
    catch (const invalid_argument &e){cerr << "Erro codigo1: " << e.what() << endl;}

    try{Codigo codigo2("a123456789");cout << "Codigo criado: " << codigo2.get_codigo() << endl;}
    catch (const invalid_argument &e){cerr << "Erro codigo2: " << e.what() << endl;}

    // ENTIDADES -------------------------------------------------------------------------------------

    try{
        Nome n1("Fulano");
        Email e1("fulano@email.com");
        Pessoa p1(n1, e1);
        cout << "Pessoa criada: " << p1.get_nome().get_nome() << ", " << p1.get_email().get_email() << "\n";
    }
    catch (const invalid_argument &e){cerr << "Pessoa inválida: " << e.what() << endl;}

    return 0;
}

cout << "\n=== TESTE RESERVA ===" << endl;
try {
    // Criar domínios para a reserva
    Codigo codigoReserva("abc123def4"); // 10 caracteres alfanuméricos
    Data checkin("15-MAR-2024");
    Data checkout("20-MAR-2024");

    // Criar hóspede
    Nome nomeHospede("Joao Silva");
    Email emailHospede("joao@email.com");
    Pessoa hospede(nomeHospede, emailHospede);

    // Criar quarto
    Numero numeroQuarto(101);
    Capacidade capQuarto(2);
    Dinheiro diaria("150,00"); // Formato string
    Ramal ramalQuarto(25);
    Quarto quarto(numeroQuarto, capQuarto, diaria, ramalQuarto);

    // Criar valor total da reserva (5 diárias)
    Dinheiro valorTotal("750,00");

    // Criar reserva
    Reserva reserva(codigoReserva, checkin, checkout, hospede, quarto, valorTotal);

    cout << "✅ Reserva criada com sucesso!" << endl;
    cout << "Código: " << reserva.get_codigo().get_codigo() << endl;
    cout << "Check-in: " << reserva.get_check_in().get_data() << endl;
    cout << "Check-out: " << reserva.get_check_out().get_data() << endl;
    cout << "Hóspede: " << reserva.get_hospede().get_nome().get_nome() << endl;
    cout << "Quarto: " << reserva.get_quarto().get_numero().get_numero() << endl;
    cout << "Valor total: " << reserva.get_valor_total().get_dinheiro() << " centavos" << endl;

} catch (const invalid_argument &e) {
    cerr << "❌ Erro na reserva: " << e.what() << endl;
}

// -------- Teste Reserva Inválida --------
try {
    Codigo codigoInvalido("ABC!23DEF4"); // Caractere especial inválido
    Data checkin("15-MAR-2024");
    Data checkout("20-MAR-2024");
    Nome nomeHospede("Maria Santos");
    Email emailHospede("maria@email.com");
    Pessoa hospede(nomeHospede, emailHospede);
    Numero numeroQuarto(102);
    Capacidade capQuarto(3);
    Dinheiro diaria("200,00");
    Ramal ramalQuarto(30);
    Quarto quarto(numeroQuarto, capQuarto, diaria, ramalQuarto);
    Dinheiro valorTotal("1000,00");

    Reserva reservaInvalida(codigoInvalido, checkin, checkout, hospede, quarto, valorTotal);
    cout << "Reserva inválida criada: " << reservaInvalida.get_codigo().get_codigo() << endl;

} catch (const invalid_argument &e) {
    cerr << "✅ Erro esperado em reserva inválida: " << e.what() << endl;
}
