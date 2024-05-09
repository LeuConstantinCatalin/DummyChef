// // login.cpp
//#include"signup.h"
#include "login.h"

#include "signfactory.h"

#include "serverconector.h"
#include "userfactory.h"
#include <QDebug>
// Login* Login::instancel=nullptr;

// Login& Login::createLogin()
// {
//     if(instancel==nullptr)
//     {
//         instancel=new Login();
//         qDebug()<<"Am creat un Login\n";
//     }
//     else
//         qDebug()<<"Exista deja un Login";
//     return *instancel;
// }

// void Login::deleteLogin()
// {
//     if(instancel!=nullptr)
//     {
//         //ServerConector::deleteServerConector();
//         delete instancel;
//         instancel=nullptr;

//         qDebug()<<"Am distrus un Login\n";
//     }else
//         qDebug()<<"Nu exista un Login de distrus\n";

// }
Login::Login(QString mess,QWidget *parent)
    : Sig(mess,parent)
{
    action->setText("Login");
    other->setText("SignUp");

    // comboBox = new QComboBox(this);
    // comboBox->addItem("utilizator");
    comboBox->addItem("admin");
    // comboBox->addItem("bucatar");
    // comboBox->setGeometry(240, 150, 100, 30);
    // connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, &Login::comboBoxActivated);
}

// void Login::comboBoxActivated()
// {
//     type=comboBox->currentText();
//     qDebug()<<type;
//     // Implementează acțiunea pentru selectarea unei opțiuni din combobox aici
// }

void Login::otherButtonClicked()
{
    this->close();
    //Login::deleteLogin();
    SignFactory::deleteSign();
   // ServerConector::deleteServerConector();
    //SignUp::createSignUp().show();
    SignFactory::createSign(" ","SIGNUP").show();



    //delete this;
}

void Login::actionButtonClicked()
{
    ServerConector::createServerConector();
    //ServerConector::connectToServer();
    QString username=usernameInput->text();
    QString password=passwordInput->text();
    QString cerere = "Login|" + username+"|"+password+"|"+type;
    ServerConector::send_message(cerere);
    const QString raspuns=ServerConector::receive_message();
    qDebug()<<raspuns<<"\n";
    if(raspuns=="Gasit")
    {
        this->close();
        //if(type=="utilizator")
        UserFactory::createUser(type,username).show();


        SignFactory::deleteSign();
       // Utilizator* u =new Utilizator(username);
        //u->show();

    }
    else
    {
        this->close();
        ServerConector::deleteServerConector();
        //Login::deleteLogin();
        SignFactory::deleteSign();
        //Login::createLogin().show();
         SignFactory::createSign("DATELE INTRODUSE SUNT INCORECTE","LOGIN").show();
    }
    //ServerConector::send_message("ion");
   // const QString  r= ServerConector::receive_message();
     //qDebug()<<r<<"\n";
}
