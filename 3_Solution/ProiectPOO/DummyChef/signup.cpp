//#include "signup.h"
//#include "login.h"
#include<signup.h>
#include"userfactory.h"
#include"signfactory.h"
#include "serverconector.h"


// SignUp* SignUp::instances=nullptr;

// SignUp& SignUp::createSignUp()
// {
//     if(instances==nullptr)
//     {
//         instances=new SignUp();
//         qDebug()<<"Am creat un SignUp\n";
//     }
//     else
//         qDebug()<<"Exista deja un SignUp";
//     return *instances;
// }

// void SignUp::deleteSignUp()
// {
//     if(instances!=nullptr)
//     {
//         ServerConector::deleteServerConector();
//         delete instances;
//         instances=nullptr;
//         qDebug()<<"Am distrus un SignUp\n";
//     }else
//         qDebug()<<"Nu exista un SignUp de distrus\n";

// }


SignUp::SignUp(QString mess, QWidget *parent)
    : Sig(mess,parent)
{
    action->setText("SignUp");
    other->setText("Login");
}

void SignUp::otherButtonClicked()
{
    this->close();
    SignFactory::deleteSign();
    //SignUp::deleteSignUp();
    SignFactory::createSign(" ","LOGIN").show();
    //Login::createLogin().show();

}


void SignUp::actionButtonClicked()
{
    if(type=="utilizator")
    {ServerConector::createServerConector();
    //ServerConector::connectToServer();
    QString username=usernameInput->text();
    QString password=passwordInput->text();
    QString cerere = "SignUp|" + username+"|"+password+"|"+type;
    ServerConector::send_message(cerere);
    const QString raspuns=ServerConector::receive_message();
    qDebug()<<raspuns;
    if(raspuns=="Inserat")
    {
        this->close();
        //SignUp::deleteSignUp();

       // Utilizator* u =new Utilizator(username);
        //u->show();
        //if(type=="utilizator")
           {UserFactory::createUser(type,username).show();
            SignFactory::deleteSign();}
        // else
        // {
        //     ServerConector::deleteServerConector();
        //     //SignUp::deleteSignUp();
        //     SignFactory::deleteSign();
        //     // Login::createLogin().show();
        //     SignFactory::createSign("ASTEPTATI CA UN ADMIN SA VA APROBE CEREREA","LOGIN").show();
        // }

    }
    else
    {
        this->close();
        ServerConector::deleteServerConector();
        //SignUp::deleteSignUp();
        SignFactory::deleteSign();
        // Login::createLogin().show();
        SignFactory::createSign("USERNAMEUL DEJA EXISTA","SIGNUP").show();
    }
    }
    else
        {
            this->close();
            SignFactory::deleteSign();
            SignFactory::createSign("ASTEPTATI SA SE APROBE CEREREA","LOGIN").show();
        }
}

