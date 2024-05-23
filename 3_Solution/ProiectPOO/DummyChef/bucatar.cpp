#include "bucatar.h"
#include <QVBoxLayout>
#include <QDialog>
//#include "ui_bucatar.h"

Bucatar::Bucatar(QString userN,QWidget *parent)
    : Utilizator(userN,parent)

{
    AlterRetete=new QPushButton("ModificaRetete",this);
    AlterRetete->setGeometry(20,180,130,30);
    connect(AlterRetete, &QPushButton::clicked, this, &Bucatar::alterRetete_clicked);
}

void Bucatar::alterRetete_clicked()
{
    qDebug() << "Button clicked";
/*
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int index = buttonsList.indexOf(button);
    if (index == -1 || index >= listaRetete.size()) return;
    Reteta &reteta = listaRetete[index]; // Referință către reteta corespunzătoare butonului apăsat
*/  int index = listaButoaneRetete->currentRow();
    if (index >= 0 ) {
        ModificareRetetaGUI *modificaRetetaGUI = new ModificareRetetaGUI(listaRetete[index], this);
        modificaRetetaGUI->show();
    } else {
        Reteta r; // Sau orice altă logică pentru cazul în care nu există nicio retetă selectată
        ModificareRetetaGUI *modificaRetetaGUI = new ModificareRetetaGUI(r, this);
        modificaRetetaGUI->show();
        listaRetete.push_back(r);
    }
}


Bucatar::~Bucatar()
{
    //delete ui;
}
