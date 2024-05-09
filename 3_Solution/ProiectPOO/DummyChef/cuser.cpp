#include "cuser.h"
#include "ui_cuser.h"
//#include "login.h"
#include"signfactory.h"
#include"userfactory.h"
#include"serverconector.h"

CUser::CUser(QString userN,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CUser)
{
    username=userN;
    //creere ui
    ui->setupUi(this);

    MenuTitle= new QLabel("Menu",this);
    Retete=new QPushButton("Retete",this);
    ListaDeCumparaturi=new QPushButton("Lista de cumparaturi",this);
    QString wm="Welcome "+ username;
    WelcomeMessage= new QLabel(wm,this);
    LogOut = new QPushButton("LogOut",this);


    // Setarea dimensiunilor și a poziției butonului
    MenuTitle->setGeometry(30, 30, 100, 30);
    Retete->setGeometry(30,80,100,30);
    ListaDeCumparaturi->setGeometry(10,130,140,30);

    WelcomeMessage->setGeometry(100,30,200,30);

    LogOut->setGeometry(265,30,100,30);

    MenuTitle->setAlignment(Qt::AlignCenter);

    WelcomeMessage->setAlignment(Qt::AlignCenter);

    connect(Retete, &QPushButton::clicked, this, &CUser::retete_clicked);
    connect(LogOut, &QPushButton::clicked, this, &CUser::logOut_clicked);
    connect(ListaDeCumparaturi, &QPushButton::clicked, this, &CUser::listaDeCumparaturi_clicked);
}

void CUser::logOut_clicked()
{
    this->close();
    ServerConector::deleteServerConector();
    //ServerConector::send_message("ion");
   // const QString  r= ServerConector::receive_message();
   // qDebug()<<r<<"\n";
    //Login::deleteLogin();
    //UserFactory::deleteUser();
    SignFactory::deleteSign();
    UserFactory::deleteUser();
    //Login::createLogin().show();
    SignFactory::createSign(" ","LOGIN").show();
    //Login::deleteLogin();

}
CUser::~CUser()
{
    delete ui;
}
