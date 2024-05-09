// //#include "mainwindow.h"

// #include "serverconector.h"
// #include <QApplication>
// #include "login.h"
// //#include "sign.h"
// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     //MainWindow w;
//     //w.show();
//     // ServerConector::createServerConector();
//     // ServerConector::connectToServer();
//     // QString cerere = "CautaNume|ion";
//     // ServerConector::send_message(cerere);
//     // qDebug()<<ServerConector::receive_message();
//     // ServerConector::disconnectFromServer();
//     // ServerConector::send_message(cerere);

//         Login l;
//     // l.show();
//     //Sign s;
//     //s.show();

//     return a.exec();
// }

// main.cpp
#include <QApplication>
//#include "login.h"
//#include "serverconector.h"
//#include "utilizator.h"

#include"signfactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   SignFactory::createSign(" ","LOGIN").show();
    //SignFactory::createSign("LOGIN");
   // SignFactory::createSign("LOGIN");
    //Login::createLogin().show();
   // ServerConector::send_message("salut");
    //ServerConector::receive_message();


    //Utilizator* u= new Utilizator;
    //u->show();

    return a.exec();
}

