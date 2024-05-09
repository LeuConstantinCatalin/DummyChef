#include "signfactory.h"

#include "login.h"
#include "signup.h"
SignFactory::SignFactory() {}



ISign* SignFactory::instance=nullptr;
ISign& SignFactory::createSign(QString mess,QString type)
{
    if(instance==nullptr)
    {
        if(type=="LOGIN"){
            instance=new Login(mess);
            qDebug()<<"am creat un nou Login\n";
        }
        else
            if(type=="SIGNUP"){
                instance= new SignUp(mess);
                qDebug()<<"am creat un nou signUP\n";
            }else
        {
             qDebug()<<"Exista deja un sign\n";
        }
    }

    return* instance;
}

void SignFactory::deleteSign()
{
    if(instance!=nullptr)
    {
        delete instance;
        instance=nullptr;
        qDebug()<<"am distrus un sign\n";
    }
}
