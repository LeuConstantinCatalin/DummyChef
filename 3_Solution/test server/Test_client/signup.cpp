#include "signup.h"
#include "ui_signup.h"



SignUp::SignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

QString SignUp::getUsername() const
{
    return username;
}
SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_SignUpButton_clicked()
{
    this->username = ui->username->text();
    emit signUpClosed(); // Emite semnalul atunci când butonul este apăsat și obținerea username-ului este completă
}

void SignUp::start()
{
    QObject::connect(&*this, &SignUp::signUpClosed, [&]() {
        QString username=this->getUsername();
        // qDebug() <<username;
        QTcpSocket socket;
        socket.connectToHost("127.0.0.1", 54000); // Adresa IP și portul serverului
        //127.0.0.1
        if (socket.waitForConnected()) {
            qDebug() << "Conectat cu succes la server!";
            QString numeDeCautat = username; // Numele pe care vrem să-l căutăm

            // Trimite cererea către server
            //QString cerere = "CautaNume|" + numeDeCautat;
            QString cerere = "InsereazaDate|" + numeDeCautat;
            socket.write(cerere.toUtf8());
            socket.waitForBytesWritten();

            // Așteaptă răspunsul de la server
            // socket.waitForReadyRead();
            // QString response = socket.readAll().trimmed();
            // qDebug() << "Răspuns de la server:" << response;
            while (true) {
                socket.waitForReadyRead();
                QString response = socket.readAll().trimmed();
                if (response.isEmpty()) {
                    break; // Ieși din buclă dacă nu mai sunt date de primit
                }
                qDebug() << "Răspuns parțial de la server:" << response;
                if(response == "Datele au fost inserate cu succes."){
                    this->close();
                    Admin *admin = new Admin();
                    //AdminWidget->addUsername(this->getUsername());
                    admin->start(this->getUsername());
                    admin->show();}
            }
        } else {
            qDebug() << "Conectarea la server a eșuat!";
        }

    });
}
