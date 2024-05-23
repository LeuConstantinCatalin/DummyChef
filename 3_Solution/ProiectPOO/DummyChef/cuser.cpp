#include "cuser.h"
#include "ui_cuser.h"
#include "detaliiretetawindow.h"
//#include "login.h"
#include"signfactory.h"
#include"userfactory.h"
#include"serverconector.h"
#include "cumparaturiwindow.h"
#include <QDebug>
#include <QFile>
#include <QStringList>

CUser::CUser(QString userN,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CUser)
{
    username=userN;
    //creere ui
    ui->setupUi(this);
    resize(600, 400);
    MenuTitle= new QLabel("Menu",this);
    Retete=new QPushButton("Retete",this);
    ListaDeCumparaturi=new QPushButton("Lista de cumparaturi",this);
    QString wm="Welcome "+ username;
    WelcomeMessage= new QLabel(wm,this);
    LogOut = new QPushButton("LogOut",this);
    EnterReteta = new QPushButton("Enter", this);
    Statistici = new QPushButton("StatisticiUtilizatori", this);

    // Setarea dimensiunilor și a poziției butonului
    MenuTitle->setGeometry(30, 30, 100, 30);
    Retete->setGeometry(30,80,100,30);
    EnterReteta->setGeometry(140,80,100,30);
    ListaDeCumparaturi->setGeometry(10,130,140,30);
    listaButoaneRetete = new QListWidget(this);
    listaButoaneRetete->setGeometry(260, 80, 100, 200);
    Statistici->setGeometry(370,80,100,30);
    listaStatistici = new QListWidget(this);
    listaStatistici->setGeometry(370, 120, 100, 160);

    WelcomeMessage->setGeometry(100,30,200,30);

    LogOut->setGeometry(265,30,100,30);

    MenuTitle->setAlignment(Qt::AlignCenter);

    WelcomeMessage->setAlignment(Qt::AlignCenter);

    connect(Retete, &QPushButton::clicked, this, &CUser::retete_clicked);
    connect(LogOut, &QPushButton::clicked, this, &CUser::logOut_clicked);
    connect(ListaDeCumparaturi, &QPushButton::clicked, this, &CUser::listaDeCumparaturi_clicked);
    connect(EnterReteta, &QPushButton::clicked, this, &CUser::enter_clicked);
    connect(Statistici,&QPushButton::clicked, this, &CUser::statistici_clicked);
}

void CUser::statistici_clicked()
{
    QString cerere = "Activity";
    ServerConector::send_message(cerere);
    QString primire;
    primire = ServerConector::receive_message();
    listaStatistici->addItem(primire);
}

void CUser::enter_clicked()
{
    if (listaButoaneRetete->selectedItems().size() == 1) {
        int index = listaButoaneRetete->currentRow();
        Reteta reteta = listaRetete.at(index);

        // Creează și afișează fereastra cu detaliile rețetei
        DetaliiRetetaWindow *detaliiRetetaWindow = new DetaliiRetetaWindow(this);
        detaliiRetetaWindow->afiseazaDetaliiReteta(reteta);
        detaliiRetetaWindow->show(); // Afișează fereastra modală
    }
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

    //if(!listaRetete.isEmpty())
    //{
    //     return;
    //}
    QString cerereRetete = "ToateRetetele";
    ServerConector::send_message(cerereRetete);
    QString raspuns;
    raspuns = ServerConector::receive_message();
    qDebug() << raspuns;

    QStringList lines = raspuns.split('_');
    if (lines.size() > 1) {
        int numRecipes = lines.takeFirst().toInt();
        for (int i = 0; i < numRecipes; ++i) {
            QString textData = lines[i];
            Reteta r(textData);
            listaRetete.append(r);
        }
    }
}



void CUser::retete_clicked() {
    // Șterge butoanele anterioare
    listaButoaneRetete->clear();
    listaRetete.clear();

    for (QPushButton *button : buttonsList) {
        button->deleteLater();
    }
    buttonsList.clear(); // Șterge butoanele din lista
    listaRetete.clear();
    // Obține lista de rețete din clasa CUser
    populare_lista_retete("retete.txt");

    for (int i = 0; i < listaRetete.size(); ++i) {

        listaButoaneRetete->addItem(listaRetete[i].getNume());
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
    detaliiRetetaWindow->show();
}

void CUser::listaDeCumparaturi_clicked(){

    QString cerereIngrediente = "ToateIngredientele";
    ServerConector::send_message(cerereIngrediente);
    QString raspuns;
    raspuns = ServerConector::receive_message();
    qDebug() << raspuns;

    QStringList lines = raspuns.split('\n'); // Split the string into lines
    listaIngrediente.clear();
    foreach(QString line, lines) {
        QStringList parts = line.split(' '); // Split each line into parts: name, quantity, unitOfMeasure
        if (parts.size() == 3) { // Ensure we have all three parts
            QString name = parts[0];
            double quantity = parts[1].toDouble(); // Convert quantity from string to double
            QString unitOfMeasure = parts[2];

            // Now you can create an Ingredient object with these values
            Ingredient ingredient(0, name, quantity, unitOfMeasure);
            listaIngrediente.push_back(ingredient);
        }
    }

    // Creăm o instanță a ferestrei de cumpărături
    CumparaturiWindow *cumparaturiWindow = new CumparaturiWindow(listaIngrediente, this);

    // Afișăm fereastra de cumpărături
    cumparaturiWindow->show();
}


CUser::~CUser()
{
    delete ui;
}



