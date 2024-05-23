#include "serverconector.h"

ServerConector* ServerConector::instance=nullptr;
QTcpSocket ServerConector::socket;

ServerConector& ServerConector::createServerConector()
{
    if(instance==nullptr)
    {
        instance=new ServerConector();
        qDebug()<<"Am creat un ServerConector\n";
        connectToServer();
    }
    else
        qDebug()<<"Exista deja un ServerConector";
    return *instance;
}

void ServerConector::deleteServerConector()
{
    if(instance!=nullptr)
    {
        delete instance;
        instance=nullptr;
        qDebug()<<"Am distrus un ServerConector\n";
        disconnectFromServer();
    }else
        qDebug()<<"Nu exista un ServerConector de distrus\n";

}

void ServerConector::connectToServer()
{
    //127.0.0.1
    //172.16.39.35
    //192.168.57.125
    socket.connectToHost("127.0.0.1", 12345); // Adresa IP și portul serverului

    if (socket.waitForConnected()) {
        qDebug() << "Conectat cu succes la server!\n";
    }
    else
    {
        qDebug() << "Eroare de conectare la server!";
    }
}

void ServerConector::send_message(const QString& cerere)
{
    if (socket.state() == QAbstractSocket::ConnectedState){
    socket.write(cerere.toUtf8());
    socket.waitForBytesWritten();
    }else{
        qDebug()<<"Neconectat la server pt trimitere";
        QCoreApplication::exit();}
}

QString ServerConector::receive_message()
{
    if (socket.state() == QAbstractSocket::ConnectedState){
        QString response;
        socket.waitForReadyRead();
        response = socket.readAll().trimmed();
        qDebug() << "Răspuns de la server:" << response;
        return response;
    }else{
        qDebug()<<"Neconectat la server pt primire";
        QCoreApplication::exit();}
    return "!";
}

void ServerConector::disconnectFromServer()
{
    if (socket.state() == QAbstractSocket::ConnectedState) {
        socket.disconnectFromHost();
        if (socket.state() == QAbstractSocket::UnconnectedState) {
            qDebug() << "Deconectat de la server cu succes!";
        } else {
            qDebug() << "Eroare la deconectarea de la server!";
        }
    } else {
        qDebug() << "Nu sunteți conectat la server!";
    }
}
//ServerConector::ServerConector() {}
