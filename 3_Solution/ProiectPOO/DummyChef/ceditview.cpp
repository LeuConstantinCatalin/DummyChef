#include "ceditview.h"
#include "ui_ceditview.h"

//#include "addbucatari2.h"
#include"editviewfactory.h"

#include"userfactory.h"

#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include<QVBoxLayout>
#include<QScrollArea>

#include "serverconector.h"

CeditView::CeditView(QString action,int n,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::editView)
      //nr=n;
{
    ui->setupUi(this);
    nr=n;
    qDebug()<<"nr="<<nr<<"\n\n";
   // createView(action);
    // connect(this, &CeditView::userDeleted, this, &CeditView::updateUserNr);
}



CeditView::~CeditView()
{
    delete ui;
}

void CeditView::addMiniBox(const QString& us, QVBoxLayout* contentLayout, QWidget* contentWidget)
{
    // qDebug()<<us<<Qt::endl;
    // QLineEdit *username = new QLineEdit(us, contentWidget);
    // username->setReadOnly(true);
    // contentLayout->addWidget(username);



    // // Adăugarea butoanelor
    // QPushButton *addButton = new QPushButton("ADD", contentWidget);
    // contentLayout->addWidget(addButton);

    // QPushButton *deleteButton = new QPushButton("Delete", contentWidget);
    // contentLayout->addWidget(deleteButton);

    // // Conectarea butoanelor la slot-urile lor
    // connect(addButton, &QPushButton::clicked, [=](){
    //     // Slot pentru editButton
    //     // Implementează acțiunea dorită când este apăsat butonul de editare

    //     QString cerere = "AddBucatarU|" + username->text();
    //     ServerConector::send_message(cerere);
    //     qDebug()<<cerere;
    //     const QString raspuns=ServerConector::receive_message();
    //     qDebug()<<raspuns<<"\n";
    //     if(raspuns=="Adaugat")

    //     {
    //         qDebug()<<raspuns;
    //         contentLayout->removeWidget(username);
    //         contentLayout->removeWidget(addButton);
    //         contentLayout->removeWidget(deleteButton);

    //         delete username;
    //         delete addButton;
    //         delete deleteButton;

    //         contentWidget->adjustSize();

    //         if(nr>0)
    //             nr--;
    //         else
    //             nr=0;
    //         //qDebug()<<"nr a devenit="<<nr<<"\n\n";
    //     }
    // });
    // //int numar=*nr;
    // connect(deleteButton, &QPushButton::clicked, [=](){
    //     // Slot pentru deleteButton
    //     // Implementează acțiunea dorită când este apăsat butonul de ștergere

    //     QString cerere = "StergeBucatar|" + username->text();;
    //     ServerConector::send_message(cerere);
    //     const QString raspuns=ServerConector::receive_message();
    //     qDebug()<<raspuns<<"\n";
    //     if(raspuns=="Sters")
    //     {
    //         contentLayout->removeWidget(username);
    //         contentLayout->removeWidget(addButton);
    //         contentLayout->removeWidget(deleteButton);

    //         delete username;
    //         delete addButton;
    //         delete deleteButton;

    //         contentWidget->adjustSize();

    //         if(nr>0)
    //             nr--;
    //         else
    //             nr=0;
    //         //qDebug()<<"nr a devenit="<<nr<<"\n\n";
    //     }

    // });
    // //nr--;
    qDebug()<<"d\n";
}


void CeditView::createView(QString action)
{
    // Creăm un QScrollArea
    // Permite QScrollArea să ajusteze dimensiunea widget-ului în funcție de necesitate
    QScrollArea *scrollArea = new QScrollArea(this);
    setLayout(new QVBoxLayout(this));
    layout()->addWidget(scrollArea);

    // Creăm un widget pentru conținutul interfeței
    QWidget *contentWidget = new QWidget;
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);

    // Adăugarea titlului
    QLabel *titleLabel = new QLabel("MENIU EDITARE", contentWidget);
    contentLayout->addWidget(titleLabel);
    QPushButton *MENUButton = new QPushButton("MENU", contentWidget);
    contentLayout->addWidget(MENUButton);
    connect(MENUButton, &QPushButton::clicked, [=](){
        // Slot pentru MENUButton

        this->close();
        UserFactory::createUser("utilizator","MENU").show();
        editViewFactory::deleteEditView();

    });

    QString rezultat = action + QString::number(nr);
    ServerConector::send_message(rezultat);
    QString message= ServerConector::receive_message();
    int counter=message.toInt();
    message= ServerConector::receive_message();
    int nrmax=message.toInt();

    qDebug()<<counter;
    //ServerConector::send_message("WAIT");
    for (int i = 0; i < counter; ++i) {
        // Adăugarea câmpului de editare de text cu drept doar de citire
        QString us=ServerConector::receive_message();
        //ServerConector::send_message("WAIT");
        addMiniBox(us,contentLayout,contentWidget);
    }
    QPushButton *BACKButton = new QPushButton("<BACK", contentWidget);
    contentLayout->addWidget(BACKButton);
    connect(BACKButton, &QPushButton::clicked, [=](){
        // Slot pentru MENUButton

        this->close();
        int aux;
        if(nr>=10)
            aux=nr-10;
        else
            aux=0;
        editViewFactory::deleteEditView();
        editViewFactory::createEditView(action,aux).show();

        //m->show();


    });

    QPushButton *NEXTButton = new QPushButton("NEXT>", contentWidget);
    contentLayout->addWidget(NEXTButton);
    connect(NEXTButton, &QPushButton::clicked, [=](){
        // Slot pentru MENUButton

        this->close();
        int aux=nr+counter;
        editViewFactory::deleteEditView();
        editViewFactory::createEditView(action,aux).show();

       // m->show();


    });
    int nn=nr+counter;
    if(nn==nrmax)
    {
        NEXTButton->hide();
    }

    if(nr==0)
    {
        BACKButton->hide();
    }


    // Setăm widgetul de conținut al QScrollArea
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);
}
