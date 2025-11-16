#include <bits/stdc++.h>
#include "dominios.hpp"
using namespace std;

// -------- Capacidade --------
Capacidade::Capacidade(int v) {
    set_capacidade(v);
}

void Capacidade::set_capacidade(int v) {
    if(v < 1 || v > 4) {
        throw std::invalid_argument("Capacidade deve ser 1, 2, 3 ou 4.");
    }
    capacidade = v;
}

int Capacidade::get_capacidade() const {
    return capacidade;
}

// -------- Cartao --------
Cartao::Cartao(string n) {
    set_cartao(n);
}

bool Cartao::luhn(const string &num) const {
    int soma = 0, alternar = 0;
    for(int i = num.size() - 1; i >= 0; i--) {
        int digito = num[i] - '0';
        if(alternar) {
            digito *= 2;
            if(digito > 9) digito -= 9;
        }
        soma += digito;
        alternar = !alternar;
    }
    return (soma % 10 == 0);
}

void Cartao::set_cartao(string n) {
    if(n.size() != 16) {
        throw invalid_argument("Cartao deve ter exatamente 16 digitos.");
    }
    for(char c : n) {
        if(!isdigit(c)) {
            throw invalid_argument("Cartao deve conter apenas digitos.");
        }
    }
    if(!luhn(n)) {
        throw invalid_argument("Cartao invalido pelo algoritmo de Luhn.");
    }
    cartao = n;
}

string Cartao::get_cartao() const {
    return cartao;
}

// -------- Senha --------
Senha::Senha(string s) {
    set_senha(s);
}

bool Senha::validar(const string &s) const {
    if(s.size() != 5)
        throw invalid_argument("Senha deve ter exatamente 5 caracteres.");

    bool minn = false, mai = false, dig = false, esp = false;
    char prev = 'n';

    for(char c : s) {
        char cur;

        if(isalpha(c)) {
            cur = 'l';
            if(islower(c)) minn = 1;
            else mai = 1;
        }
        else if(isdigit(c)) { dig = true; cur = 'd'; }
        else if(string("!\"#$%&?").find(c) != string::npos) { esp = true; cur = 'e'; }
        else throw invalid_argument("Senha contem caractere invalido.");

        if((prev == cur) && (cur == 'l' || cur == 'd'))
            throw invalid_argument("Senha nao pode ter letras ou digitos consecutivos.");

        prev = cur;
    }

    if(!minn) throw invalid_argument("Senha deve conter ao menos uma letra minuscula.");
    if(!mai) throw invalid_argument("Senha deve conter ao menos uma letra maiuscula.");
    if(!dig) throw invalid_argument("Senha deve conter ao menos um digito.");
    if(!esp) throw invalid_argument("Senha deve conter ao menos um caractere especial (!\"#$%&?).");

    return true;
}

void Senha::set_senha(string s) {
    if(!validar(s)) throw invalid_argument("Senha invalida");
    senha = s;
}

string Senha::get_senha() const {
    return senha;
}

// -------- Email --------
Email::Email(string s) {
    set_email(s);
}

bool Email::validar(const string &s) const {
    if((int)s.size() > 320) throw invalid_argument("Email excede 320 caracteres.");

    size_t id = s.find('@');
    if(id != s.rfind('@')) throw invalid_argument("Email nao pode conter mais de um '@'.");
    if(id == string::npos) throw invalid_argument("Email deve conter '@'.");

    string local = s.substr(0, id), dom = s.substr(id + 1);

    if(local.empty() || (int)local.size() > 64) throw invalid_argument("Parte local invalida.");
    if(local.front() == '.' || local.front() == '-' || local.back() == '.' || local.back() == '-') throw invalid_argument("Parte local nao pode comecar ou terminar com '.' ou '-'.");

    for(int i = 0; i < (int)local.size(); i++) {
        char c = local[i];
        if(!(isalpha(c) || isdigit(c) || c == '.' || c == '-')) throw invalid_argument("Parte local contem caractere invalido.");
        if((c == '.' || c == '-') && (i+1 < (int)local.size())) {
            char nextC = local[i+1];
            if(nextC == '.' || nextC == '-') throw invalid_argument("Parte local contem '.' ou '-' consecutivos.");
        }
    }

    if(dom.empty() || (int)dom.size() > 255) throw invalid_argument("Dominio invalido.");

    int j = 0;
    for(int i = 0; i <= (int)dom.size(); i++) {
        if(i == (int)dom.size() || dom[i] == '.') {
            string cur = dom.substr(j, i - j);
            if(cur.empty()) throw invalid_argument("Dominio contem pontos consecutivos.");
            if(cur.front() == '-' || cur.back() == '-') throw invalid_argument("Segmento do dominio nao pode comecar ou terminar com '-'.");
            for(char c : cur) {
                if(!(isalpha(c) || isdigit(c) || c == '-')) throw invalid_argument("Dominio contem caractere invalido.");
            }
            j = i+1;
        }
    }
    return true;
}

void Email::set_email(string s) {
    if(!validar(s)) throw invalid_argument("Email invalido");
    email = s;
}

string Email::get_email() const {
    return email;
}

// -------- Nome --------
Nome::Nome(string n) {
    set_nome(n);
}

void Nome::validar(const string &n) const {
    if(n.size() < 5 || n.size() > 20) {
        throw invalid_argument("Nome deve ter entre 5 e 20 caracteres.");
    }
    if(n.front() == ' ' || n.back() == ' ') {
        throw invalid_argument("Nome nao pode comecar ou terminar com espaco.");
    }
    for(size_t i = 0; i < n.size(); i++) {
        char c = n[i];
        if(!(isalpha(c) || c == ' ')) {
            throw invalid_argument("Nome so pode conter letras e espacos.");
        }
        if(c == ' ' && (i+1 < n.size() && !isalpha(n[i+1]))) {
            throw invalid_argument("Espaco deve ser seguido por letra.");
        }
    }
    bool novaPalavra = true;
    for(char c : n) {
        if(novaPalavra && isalpha(c) && !isupper(c)) {
            throw invalid_argument("Primeira letra de cada termo deve ser maiuscula.");
        }
        novaPalavra = (c == ' ');
    }
}

void Nome::set_nome(string n) {
    validar(n);
    nome = n;
}

string Nome::get_nome() const {
    return nome;
}

// -------- Ramal --------
Ramal::Ramal(int r) {
    set_ramal(r);
}

void Ramal::validar(int r) const {
    if(r < 0 || r > 50) {
        throw invalid_argument("Ramal deve estar entre 00 e 50.");
    }
}

void Ramal::set_ramal(int r) {
    validar(r);
    ramal = r;
}

int Ramal::get_ramal() const {
    return ramal;
}

// -------- Numero --------
Numero::Numero(int n) {
    set_numero(n);
}

void Numero::validar(int n) const {
    if(n < 1 || n > 999) {
        throw invalid_argument("Numero deve estar entre 001 e 999.");
    }
}

void Numero::set_numero(int n) {
    validar(n);
    numero = n;
}

int Numero::get_numero() const {
    return numero;
}

// -------- Endereco --------
Endereco::Endereco(string e) {
    set_endereco(e);
}

void Endereco::validar(const string &e) const {
    // Verifica tamanho
    if (e.size() < 5 || e.size() > 30) {
        throw invalid_argument("Endereco deve ter entre 5 e 30 caracteres.");
    }
    char primeiro = e[0];
    char ultimo = e[e.size() - 1];
    if (primeiro == ',' || primeiro == '.' || primeiro == ' ' ||
        ultimo == ',' || ultimo == '.' || ultimo == ' ') {
        throw invalid_argument("Endereco nao pode comecar ou terminar com virgula, ponto ou espaco.");
    }
    for (size_t i = 0; i < e.size(); i++) {
        char c = e[i];

        if (!(isalnum(c) || c == ',' || c == '.' || c == ' ')) {
            throw invalid_argument("Endereco contem caractere invalido.");
        }
        if (i < e.size() - 1) {
            char next = e[i + 1];

            if (c == ',' && (next == ',' || next == '.')) {
                throw invalid_argument("Virgula nao pode ser seguida por virgula ou ponto.");
            }
            if (c == '.' && (next == ',' || next == '.')) {
                throw invalid_argument("Ponto nao pode ser seguido por virgula ou ponto.");
            }
            if (c == ' ' && !isalnum(next)) {
                throw invalid_argument("Espaco em branco deve ser seguido por letra ou digito.");
            }
        }
    }
}
void Endereco::set_endereco(string e) {
    validar(e);
    endereco = e;
}
string Endereco::get_endereco() const {
    return endereco;
}

// -------- Data --------
Data::Data(string d) {
    set_data(d);
}
bool Data::ehBissexto(int ano) const {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}
void Data::validar(const string &d) const {
    if (d.size() != 11) {
        throw invalid_argument("Data deve estar no formato DD-MMM-AAAA (11 caracteres).");
    }
    if (d[2] != '-' || d[6] != '-') {
        throw invalid_argument("Data deve usar hifens como separadores (DD-MMM-AAAA).");
    }
    string dia_str = d.substr(0, 2);
    string mes_str = d.substr(3, 3);
    string ano_str = d.substr(7, 4);

    int dia;
    try {
        dia = stoi(dia_str);
    } catch (...) {
        throw invalid_argument("Dia da data deve ser um numero.");
    }
    int ano;
    try {
        ano = stoi(ano_str);
    } catch (...) {
        throw invalid_argument("Ano da data deve ser um numero.");
    }
    if (ano < 2000 || ano > 2999) {
        throw invalid_argument("Ano deve estar entre 2000 e 2999.");
    }
    vector<string> meses_validos = {"JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
                                   "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};
    string mes_upper = mes_str;
    transform(mes_upper.begin(), mes_upper.end(), mes_upper.begin(), ::toupper);

    auto it = find(meses_validos.begin(), meses_validos.end(), mes_upper);
    if (it == meses_validos.end()) {
        throw invalid_argument("Mes invalido. Use: JAN, FEV, MAR, ABR, MAI, JUN, JUL, AGO, SET, OUT, NOV, DEZ.");
    }
    int mes_index = distance(meses_validos.begin(), it) + 1;

    vector<int> dias_por_mes = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes_index == 2 && ehBissexto(ano)) {
        dias_por_mes[1] = 29;
    }
    if (dia < 1 || dia > dias_por_mes[mes_index - 1]) {
        throw invalid_argument("Dia invalido para o mes especificado.");
    }
    if (mes_str != mes_upper) {
        throw invalid_argument("Mes deve estar em letras maiusculas.");
    }
}

void Data::set_data(string d) {
    validar(d);
    data = d;
}

string Data::get_data() const {
    return data;
}

// -------- Telefone --------
Telefone::Telefone(string t) {
    set_telefone(t);
}

bool Telefone::validar(string t) {
    if(t[0] != '+') {
        throw invalid_argument("Telefone invalido. Deve comecar com +.");
    }

    if(t.size() != 15) {
        throw invalid_argument("Telefone invalido. Deve conter exatamente 14 digitos alem do simbolo +.");
    }

    for(int i = 1; i < t.size(); i++) {
        if(!isdigit(t[i])) {
            throw invalid_argument("Telefone invalido. Deve conter apenas numeros apos o simbolo +.");
        }
    }

    return true;

}

void Telefone::set_telefone(string t) {
    validar(t);
    telefone = t;
}

string Telefone::get_telefone() const {
    return telefone;
}

// -------- Dinheiro --------
Dinheiro::Dinheiro(string d) {
    set_dinheiro(d);
}

bool Dinheiro::validar(string d) {
    string string_int = "";
    int parte_inteira = 0;

    for(int i = 0; i < d.size(); i++) {
        if(isdigit(d[i])) {
            string_int += d[i];
        } else {
            if(d[i] != ',') {
                throw invalid_argument("Dinheiro invalido. Digite apenas numeros. Use uma virgula para os centavos");
            }
        }

        if(d[i] == ',') {
            if(string_int == "") {
                throw invalid_argument("Dinheiro invalido. Deve conter pelo menos um digito antes da virgula (o digito pode ser 0).");
            }

            int parte_inteira = stoi(string_int);

            if(parte_inteira > 1000000) {
                throw invalid_argument("Dinheiro invalido. Nao deve ultrapassar um milhao.");
            }

            break;
        }
    }

    if(d[d.size()-3] != ',') {
        throw invalid_argument("Dinheiro invalido. Use duas casas decimais.");
    } else {
        if(parte_inteira == 1000000) {
            if(d[d.size()-2] != '0' or d[d.size()-1] != '0') {
                throw invalid_argument("Dinheiro invalido. Nao deve ultrapassar um milhao.");
            }
        }
    }

    return true;

}

void Dinheiro::set_dinheiro(string d) {
    validar(d);
    string temp = d;
    d[d.size()-3] = '.';
    this->dinheiro = static_cast<int>(stof(temp) * 100);
}

int Dinheiro::get_dinheiro() const{
    return dinheiro;
}

// -------- C�digo --------
Codigo::Codigo(string c) {
    set_codigo(c);
}

bool Codigo::validar(string c) {
    for(int i = 0; i < c.size(); i++) {
        if(!isdigit(c[i]) && !islower(c[i])) {
            throw invalid_argument("Codigo invalido. Deve conter apenas numeros ou letras minusculas.");
        }
    }

    if(c.size() != 10) {
        throw invalid_argument("Codigo invalido. Deve conter exatamente 10 caracteres.");
    }

    return true;
}

void Codigo::set_codigo(string c) {
    validar(c);
    codigo = c;
}

string Codigo::get_codigo() const {
    return codigo;
}
