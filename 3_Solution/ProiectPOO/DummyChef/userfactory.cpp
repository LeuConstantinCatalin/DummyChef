#include "userfactory.h"
#include"admin.h"
//UserFactory::UserFactory() {}



IUser* UserFactory::instance=nullptr;
IUser& UserFactory::createUser(QString type, QString username)
{
    if(instance==nullptr)
    {
        if(type=="utilizator"){
            instance=new Utilizator(username);
            qDebug()<<"am creat un nou Utilizator\n";
        }
        else
            if(type=="bucatar"){
                instance=new Bucatar(username);
                qDebug()<<"am creat un nou Bucatar\n";
            }
        else
            if(type=="admin"){
                instance=new Admin(username);
                qDebug()<<"am creat un nou Admin\n";
            }
            // {
            //     qDebug()<<"Exista deja un User\n";
            // }
    }

    return* instance;
}


void UserFactory::deleteUser()
{
    if(instance!=nullptr)
    {
        delete instance;
        instance=nullptr;
        qDebug()<<"am distrus un User\n";
    }
}
