#include <iostream>
#include "dominios.hpp"

using namespace std;

int main() {
    try {
        Capacidade c1(3);
        cout << "Capacidade criada: " << c1.get_valor() << endl;

        Capacidade c2(5);  // inválido
        cout << "Capacidade criada: " << c2.get_valor() << endl;
    }
    catch (const invalid_argument &e) {
        cerr << "Erro: " << e.what() << endl;
    }

    return 0;
}
