#ifndef SERVERCONECTOR_H
#define SERVERCONECTOR_H
//#include<iostream>
#include <QDebug>
#include <QTcpSocket>
#include <QApplication>
//#include<iostream>
class ServerConector
{
private:
    static QTcpSocket socket;
    static ServerConector* instance;
    ServerConector(){qDebug()<<"Am creat ServerConector-ul\n";};
    ~ServerConector(){qDebug()<<"Am distrus ServerConector-ul\n";};
    static void connectToServer();
    static void disconnectFromServer();
public:

    static ServerConector& createServerConector();
    static void deleteServerConector();

    static void send_message(const QString& cerere);
    static QString receive_message();



};

#endif // SERVERCONECTOR_H
