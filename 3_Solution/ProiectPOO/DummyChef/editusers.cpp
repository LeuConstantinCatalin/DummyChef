#include "editusers.h"
#include "ui_editusers.h"
#include"editviewfactory.h"

#include"userfactory.h"


#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include<QVBoxLayout>
#include<QScrollArea>

#include <QComboBox>

#include "serverconector.h"

editUsers::editUsers(QString action,int nr,QWidget *parent)
    : CeditView(action,nr,parent),
    //QWidget(parent)
     ui(new Ui::editUsers)
{
    ui->setupUi(this);
    createView(action);
}

editUsers::~editUsers()
{
    delete ui;
}

void editUsers::addMiniBox(const QString& us, QVBoxLayout* contentLayout, QWidget* contentWidget)
{
    qDebug()<<us<<Qt::endl;
    QLineEdit *username = new QLineEdit("Username: " + us, contentWidget);
    username->setReadOnly(true);
    contentLayout->addWidget(username);

    QString ty=ServerConector::receive_message();
    QLineEdit *type = new QLineEdit("Type: " + ty, contentWidget);
    type->setReadOnly(true);
    contentLayout->addWidget(type);

    //QString type=ServerConector::receive_message();
    QComboBox *comboBox= new QComboBox(this);

    // Add items to the combo box
    comboBox->addItem("utilizator");
    comboBox->addItem("bucatar");
    comboBox->addItem("admin");
    contentLayout->addWidget(comboBox);

    // connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, [=](int index) {
    //     // Codul dvs. care trebuie executat când este activat un element din combobox
    //     // Variabila 'index' reprezintă indexul elementului selectat
    // });

    // Adăugarea butoanelor
    QPushButton *ChangeTypeButton = new QPushButton("ChangeType", contentWidget);
    contentLayout->addWidget(ChangeTypeButton);

    QPushButton *deleteButton = new QPushButton("Delete", contentWidget);
    contentLayout->addWidget(deleteButton);

    // Conectarea butoanelor la slot-urile lor
    connect(ChangeTypeButton, &QPushButton::clicked, [=](){
        // Slot pentru editButton
        // Implementează acțiunea dorită când este apăsat butonul de editare

        QString cerere = "changeType|" + username->text().remove(0, 10);
        ServerConector::send_message(cerere);
        //qDebug()<<cerere;
        ServerConector::send_message(comboBox->currentText());
        const QString raspuns=ServerConector::receive_message();
        qDebug()<<raspuns<<"\n";
        if(raspuns=="Modificat")

        {
            this->close();
            int n=nr;
            qDebug()<<"n= "<<n;
            editViewFactory::deleteEditView();
            //nr=10;
            //qDebug()<<"nr= "<<nr<<"\n nr+="<<nr/10;


            editViewFactory::createEditView("editUsers",n).show();
            //qDebug()<<"nr a devenit="<<nr<<"\n\n";
        }
    });
    //int numar=*nr;
    connect(deleteButton, &QPushButton::clicked, [=](){
        // Slot pentru deleteButton
        // Implementează acțiunea dorită când este apăsat butonul de ștergere

        QString cerere = "stergeUser|" + username->text().remove(0, 10);
        qDebug()<<cerere<<"\n";
        ServerConector::send_message(cerere);
        const QString raspuns=ServerConector::receive_message();
        qDebug()<<raspuns<<"\n";
        if(raspuns=="Sters")
        {
            contentLayout->removeWidget(username);
            contentLayout->removeWidget(type);
            contentLayout->removeWidget(ChangeTypeButton);
            contentLayout->removeWidget(comboBox);
            contentLayout->removeWidget(deleteButton);

            delete username;
            delete type;
            delete comboBox;
            delete ChangeTypeButton;
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

