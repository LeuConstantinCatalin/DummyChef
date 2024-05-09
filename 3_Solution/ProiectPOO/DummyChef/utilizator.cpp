#include "utilizator.h"
//#include "ui_utilizator.h"
#include"serverconector.h"

// Utilizator* Utilizator::instance=nullptr;

// Utilizator* Utilizator::createUtilizator(QString userN)
// {
//     if(instance==nullptr)
//         instance=new Utilizator(userN);
//     return instance;
// }

// void Utilizator::deleteUtilizator()
// {
//     if(instance!=nullptr)
//     {
//         delete instance;
//         instance=nullptr;
//     }
// }

Utilizator::Utilizator(QString userN,QWidget *parent)
    : CUser(userN,parent)

{
}

Utilizator::~Utilizator()
{
    //delete ui;
}

void Utilizator::retete_clicked()
{
    //ServerConector::send_message("retete");

    //ServerConector::receive_message();


    //qDebug()<<"Salut";
}
