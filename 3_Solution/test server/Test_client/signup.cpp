#include "signup.h"
#include "ui_signup.h"

#include "admin.h"



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
void SignUp::start()
{

    QString username=this->getUsername();
    // qDebug() <<username;
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 12345); // Adresa IP și portul serverului

    if (socket.waitForConnected()) {
        qDebug() << "Conectat cu succes la server!";
        QString numeDeCautat = username; // Numele pe care vrem să-l căutăm

        // Trimite cererea către server
        QString cerere = "InsereazaDate|" + numeDeCautat;
        socket.write(cerere.toUtf8());
        socket.waitForBytesWritten();

        // Așteaptă răspunsul de la server
        while (true) {
            socket.waitForReadyRead();
            QString response = socket.readAll().trimmed();
           // g=response;
            if (response.isEmpty()) {
                break; // Ieși din buclă dacă nu mai sunt date de primit
            }
            qDebug() << "Răspuns parțial de la server:" << response;
            if(response != "Eroare la inserarea datelor."){
                this->close();
                Admin *admin = new Admin();
                admin->start(this->getUsername());
                admin->show();
            }
            else
            {
                this->ui->retraySignUp->setText("Username indisponibil");
                this->close();
                this->show();}
        }

    } else {
        qDebug() << "Conectarea la server a eșuat!";
    }



}

void SignUp::on_SignUpButton_clicked()
{
    this->username = ui->username->text();
    this->start();
}

