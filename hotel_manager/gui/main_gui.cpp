#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include "entidades.hpp"

// g++ main_gui.cpp ../entidades.cpp ../dominios.cpp -I.. -o cadastro $(pkg-config --cflags --libs Qt6Widgets)
// ./cadastro
// GUI de teste

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include "entidades.hpp"

// g++ main_gui.cpp ../entidades.cpp ../dominios.cpp -I.. -o cadastro $(pkg-config --cflags --libs Qt6Widgets)
// GUI de teste

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget w; w.setWindowTitle("Cadastro");
    QVBoxLayout *l = new QVBoxLayout(&w);

    QLineEdit *n = new QLineEdit(); n->setPlaceholderText("Nome"); l->addWidget(n);
    QLineEdit *e = new QLineEdit(); e->setPlaceholderText("Email"); l->addWidget(e);

    QLineEdit *r = new QLineEdit(); r->setPlaceholderText("Ramal"); l->addWidget(r);
    QLineEdit *senhaInput = new QLineEdit(); senhaInput->setPlaceholderText("Senha"); l->addWidget(senhaInput);

    QPushButton *b = new QPushButton("Cadastrar"); l->addWidget(b);
    QLabel *saida = new QLabel(); l->addWidget(saida);

    QObject::connect(b, &QPushButton::clicked, [&](){
        try {
            Pessoa p(Nome(n->text().toStdString()), Email(e->text().toStdString()));
            int ramalInt = r->text().toInt();
            Gerente g(Ramal(ramalInt), Senha(senhaInput->text().toStdString()));

            saida->setText("Nome: "+QString::fromStdString(p.get_nome().get_nome())+
                           "\nEmail: "+QString::fromStdString(p.get_email().get_email())+
                           "\nRamal: "+QString::number(g.get_ramal().get_ramal())+
                           "\nSenha: "+QString::fromStdString(g.get_senha().get_senha()));
        }
        catch(std::invalid_argument &ex) {saida->setText("Erro: "+QString(ex.what()));}
    });

    w.show();
    return a.exec();
}

