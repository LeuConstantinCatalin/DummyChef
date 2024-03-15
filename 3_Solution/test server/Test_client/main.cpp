// #include "mainwindow.h"

// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     MainWindow w;
//     w.show();
//     return a.exec();
// }

#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>

#include <QApplication>
#include"login.h"
//#include"signup.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LOGIN l;
    //SignUp s;
    l.show();
    l.start();
    // QObject::connect(&s, &SignUp::signUpClosed, [&]() {
    //     QString username=s.getUsername();
    //     // qDebug() <<username;
    //     QTcpSocket socket;
    //     socket.connectToHost("127.0.0.1", 54000); // Adresa IP și portul serverului

    //     if (socket.waitForConnected()) {
    //         qDebug() << "Conectat cu succes la server!";
    //         QString numeDeCautat = username; // Numele pe care vrem să-l căutăm

    //         // Trimite cererea către server
    //         //QString cerere = "CautaNume|" + numeDeCautat;
    //         QString cerere = "InsereazaDate|" + numeDeCautat;
    //         socket.write(cerere.toUtf8());
    //         socket.waitForBytesWritten();

    //         // Așteaptă răspunsul de la server
    //         // socket.waitForReadyRead();
    //         // QString response = socket.readAll().trimmed();
    //         // qDebug() << "Răspuns de la server:" << response;
    //         while (true) {
    //             socket.waitForReadyRead();
    //             QString response = socket.readAll().trimmed();
    //             if (response.isEmpty()) {
    //                 break; // Ieși din buclă dacă nu mai sunt date de primit
    //             }
    //             qDebug() << "Răspuns parțial de la server:" << response;
    //         }
    //     } else {
    //         qDebug() << "Conectarea la server a eșuat!";
    //     }

    // });
    return a.exec();
}
