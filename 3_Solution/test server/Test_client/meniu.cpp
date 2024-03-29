// meniu.cpp
#include "meniu.h"
#include "login.h"

Meniu::Meniu(QWidget *parent) :
    QWidget(parent),
    button1(new QPushButton("Log Out")),
    button2(new QPushButton("Rețete")),
    button3(new QPushButton("ListaDeCumparaturi"))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);



    // Setează lățimea fixă a widget-ului Meniu
    setFixedWidth(100);  // Widget-ul Meniu va avea o lățime fixă de 100 de pixeli

    // Conectare semnalele butoanelor la slot-urile corespunzătoare
    connect(button1, &QPushButton::clicked, this, &Meniu::handleButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &Meniu::handleButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &Meniu::handleButton3Clicked);
}

Meniu::~Meniu()
{
    delete button1;
    delete button2;
    delete button3;
}

void Meniu::handleButton1Clicked()
{
    emit logoutClicked(); // Emite semnalul atunci când butonul de logout este apăsat
}

void Meniu::handleButton2Clicked()
{
    emit reteteClicked();
}

void Meniu::handleButton3Clicked()
{
    emit listaDeIngredienteClicked();
}
