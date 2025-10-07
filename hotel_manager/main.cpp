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
