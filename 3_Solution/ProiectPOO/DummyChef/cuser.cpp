#include "cuser.h"
#include "ui_cuser.h"
#include "detaliiretetawindow.h"
//#include "login.h"
#include"signfactory.h"
#include"userfactory.h"
#include"serverconector.h"
#include<QFile>

CUser::CUser(QString userN,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CUser)
{
    username=userN;
    //creere ui
    ui->setupUi(this);

    MenuTitle= new QLabel("Menu",this);
    Retete=new QPushButton("Retete",this);
    ListaDeCumparaturi=new QPushButton("Lista de cumparaturi",this);
    QString wm="Welcome "+ username;
    WelcomeMessage= new QLabel(wm,this);
    LogOut = new QPushButton("LogOut",this);


    // Setarea dimensiunilor și a poziției butonului
    MenuTitle->setGeometry(30, 30, 100, 30);
    Retete->setGeometry(30,80,100,30);
    ListaDeCumparaturi->setGeometry(10,130,140,30);


    WelcomeMessage->setGeometry(100,30,200,30);

    LogOut->setGeometry(265,30,100,30);




    MenuTitle->setAlignment(Qt::AlignCenter);

    WelcomeMessage->setAlignment(Qt::AlignCenter);

    connect(Retete, &QPushButton::clicked, this, &CUser::retete_clicked);
    connect(LogOut, &QPushButton::clicked, this, &CUser::logOut_clicked);
    connect(ListaDeCumparaturi, &QPushButton::clicked, this, &CUser::listaDeCumparaturi_clicked);
}

void CUser::logOut_clicked()
{
    this->close();
    ServerConector::deleteServerConector();
    //ServerConector::send_message("ion");
   // const QString  r= ServerConector::receive_message();
   // qDebug()<<r<<"\n";
    //Login::deleteLogin();
    //UserFactory::deleteUser();
    SignFactory::deleteSign();
    UserFactory::deleteUser();
    //Login::createLogin().show();
    SignFactory::createSign(" ","LOGIN").show();
    //Login::deleteLogin();

}

void CUser::populare_lista_retete(const QString& fileWithPaths) {

    // Deschide fișierul care conține pathurile către fișierele cu rețete
    QFile file(fileWithPaths);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Eroare la deschiderea fișierului" << fileWithPaths << ":" << file.errorString();
        return;
    }

    // Citeste fiecare linie din fișierul cu pathuri
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString filePath = in.readLine().trimmed(); // Citeste și elimina eventualele spații albe

        // Citește conținutul fișierului cu rețeta și crează un obiect Reteta
        Reteta reteta(filePath);
        listaRetete.push_back(reteta);
    }

    // Închide fișierul cu pathurile către fișierele cu rețete
    file.close();

}



void CUser::retete_clicked() {
    // Șterge butoanele anterioare
    for (QPushButton *button : buttonsList) {
        button->deleteLater();
    }
    buttonsList.clear(); // Șterge butoanele din lista
    listaRetete.clear();
    // Obține lista de rețete din clasa CUser
    populare_lista_retete("E:\\POO\\DummyChef-main\\DummyChef-main\\3_Solution\\retete.txt.txt");

    // Obține dimensiunile widget-ului principal
    int windowWidth = this->width();
    int windowHeight = this->height();

    // Setează poziția de start pe axa y pentru primul buton
    int startY = 80;

    // Calculează pozițiile butoanelor
    int xOffset = 100; // 100 de pixeli mai la dreapta
    for (int i = 0; i < listaRetete.size(); ++i) {
        // Creează un buton pentru fiecare rețetă din lista de rețete
        QPushButton *button = new QPushButton(listaRetete.at(i).getNume(), this);
        button->setFixedSize(100, 30);
        buttonsList.append(button);
        connect(button, &QPushButton::clicked, this, &CUser::onRetetaButtonClicked);
        // Setează poziția butonului
        button->move((windowWidth - 100) / 2 + xOffset, startY + i * (30 + 10)); // 10 este spațiul suplimentar între butoane

        // Afișează butonul
        button->show();
    }
}

void CUser::onRetetaButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    // Obține rețeta corespunzătoare butonului apăsat
    int index = buttonsList.indexOf(button);
    if (index == -1 || index >= listaRetete.size()) return;
    Reteta reteta = listaRetete.at(index);

    // Creează și afișează fereastra cu detaliile rețetei
    DetaliiRetetaWindow *detaliiRetetaWindow = new DetaliiRetetaWindow(this);
    detaliiRetetaWindow->afiseazaDetaliiReteta(reteta);
    detaliiRetetaWindow->exec(); // Afișează fereastra modală
}

CUser::~CUser()
{
    delete ui;
}


