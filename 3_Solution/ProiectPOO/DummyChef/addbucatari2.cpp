#include "addbucatari2.h"
#include "ui_addbucatari2.h"


#include"editviewfactory.h"

#include"userfactory.h"

#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include<QVBoxLayout>
#include<QScrollArea>

#include "serverconector.h"

addBucatari2::addBucatari2(QString action,int nr,QWidget *parent)
    : CeditView(action,nr,parent)
    , ui(new Ui::addBucatari2)
{
    ui->setupUi(this);
    createView(action);
}

addBucatari2::~addBucatari2()
{
    delete ui;
}

void addBucatari2::addMiniBox(const QString& us, QVBoxLayout* contentLayout, QWidget* contentWidget)
{
    qDebug()<<us<<Qt::endl;
    QLineEdit *username = new QLineEdit(us, contentWidget);
    username->setReadOnly(true);
    contentLayout->addWidget(username);



    // Adăugarea butoanelor
    QPushButton *addButton = new QPushButton("ADD", contentWidget);
    contentLayout->addWidget(addButton);

    QPushButton *deleteButton = new QPushButton("Delete", contentWidget);
    contentLayout->addWidget(deleteButton);

    // Conectarea butoanelor la slot-urile lor
    connect(addButton, &QPushButton::clicked, [=](){
        // Slot pentru editButton
        // Implementează acțiunea dorită când este apăsat butonul de editare

        QString cerere = "AddBucatarU|" + username->text();
        ServerConector::send_message(cerere);
        qDebug()<<cerere;
        const QString raspuns=ServerConector::receive_message();
        qDebug()<<raspuns<<"\n";
        if(raspuns=="Adaugat")

        {
            qDebug()<<raspuns;
            contentLayout->removeWidget(username);
            contentLayout->removeWidget(addButton);
            contentLayout->removeWidget(deleteButton);

            delete username;
            delete addButton;
            delete deleteButton;

            contentWidget->adjustSize();

            if(nr>0)
                nr--;
            else
                nr=0;
            //qDebug()<<"nr a devenit="<<nr<<"\n\n";
        }
    });
    //int numar=*nr;
    connect(deleteButton, &QPushButton::clicked, [=](){
        // Slot pentru deleteButton
        // Implementează acțiunea dorită când este apăsat butonul de ștergere

        QString cerere = "StergeBucatar|" + username->text();;
        ServerConector::send_message(cerere);
        const QString raspuns=ServerConector::receive_message();
        qDebug()<<raspuns<<"\n";
        if(raspuns=="Sters")
        {
            contentLayout->removeWidget(username);
            contentLayout->removeWidget(addButton);
            contentLayout->removeWidget(deleteButton);

            delete username;
            delete addButton;
            delete deleteButton;

            contentWidget->adjustSize();

            if(nr>0)
                nr--;
            else
                nr=0;
            //qDebug()<<"nr a devenit="<<nr<<"\n\n";
        }

    });
    //nr--;
}

