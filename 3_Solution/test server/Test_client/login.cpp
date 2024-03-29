#include "login.h"

#include "ui_login.h"

LOGIN::LOGIN(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LOGIN)
{

    ui->setupUi(this);

    // QVBoxLayout *layout = new QVBoxLayout(this);
    // Meniu *meniu = new Meniu(this);
    // layout->addWidget(meniu);
    //signUpWidget = new SignUp();
    //admin=new Admin();

}

LOGIN::~LOGIN()
{
    //delete admin;
   // delete signUpWidget;
    delete ui;
}



QString LOGIN::getUsername() const
{
    return username;
}

void LOGIN::start()
{

        QString username=this->getUsername();
        // qDebug() <<username;
        QTcpSocket socket;
        socket.connectToHost("127.0.0.1", 12345); // Adresa IP și portul serverului

        if (socket.waitForConnected()) {
            qDebug() << "Conectat cu succes la server!";
            QString numeDeCautat = username; // Numele pe care vrem să-l căutăm

            // Trimite cererea către server
            QString cerere = "CautaNume|" + numeDeCautat;
            //QString cerere = "InsereazaDate|" + numeDeCautat;
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
                if(response != "Nu s-a gasit nicio potrivire."){
                    this->close();
                    // Admin *AdminWidget = new Admin();
                    //AdminWidget->addUsername(this->getUsername());
                    Admin *admin= new Admin();
                    admin->start(this->getUsername());
                    admin->show();}


            }
        } else {
            qDebug() << "Conectarea la server a eșuat!";
        }


}



void LOGIN::on_LoginButton_clicked()
{
    this->username = ui->lineEdit->text();
    this->start();
    //emit loginClosed(); // Emite semnalul atunci când butonul este apăsat și obținerea username-ului este completă
}


void LOGIN::on_SignUpRedirect_clicked()
{
    // Închide fereastra de login
    this->close();
    // Deschide pagina de înregistrare folosind show()
    SignUp *signUpWidget = new SignUp();
    //signUpWidget->show();
    signUpWidget->show();
}



