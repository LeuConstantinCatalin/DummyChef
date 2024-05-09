#include "sig.h"
#include "ui_sig.h"
//#include "userfactory.h"
Sig::Sig(QString mess,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sig)
{

    //connect(other, &QPushButton::clicked, this, &Sig::otherButtonClicked);
    //creere ui
    ui->setupUi(this);
    action = new QPushButton("Action", this);
    other= new QPushButton("Other",this);
    usernameText = new QLabel("Username",this);
    passwordText = new QLabel("Password",this);
    usernameInput = new QLineEdit("",this);
    passwordInput = new QLineEdit("",this);
    message = new QLineEdit(mess,this);

    // Setarea dimensiunilor și a poziției butonului
    action->setGeometry(150, 250, 100, 30);
    other->setGeometry(290,10,100,30);
    usernameText->setGeometry(100,70,100,30);
    passwordText->setGeometry(100,110,100,30);
    usernameInput->setGeometry(240,70,100,30);
    passwordInput->setGeometry(240,110,100,30);
    message->setGeometry(25,10,250,30);

    //aliniera textului la centru
    usernameText->setAlignment(Qt::AlignCenter);
    passwordText->setAlignment(Qt::AlignCenter);
    usernameInput->setAlignment(Qt::AlignCenter);
    passwordInput->setAlignment(Qt::AlignCenter);
    message->setAlignment(Qt::AlignCenter);

    message->setReadOnly(true);

    connect(other, &QPushButton::clicked, this, &Sig::other_clicked);
    connect(action, &QPushButton::clicked, this, &Sig::action_clicked);


    comboBox = new QComboBox(this);
    comboBox->addItem("utilizator");
    //comboBox->addItem("admin");
    comboBox->addItem("bucatar");
    comboBox->setGeometry(240, 150, 100, 30);
    connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, &Sig::comboBoxActivated);
}
// void Sig::on_other_clicked()
// {
//     otherButtonClicked();
// }

void Sig::comboBoxActivated()
{
    type=comboBox->currentText();
    qDebug()<<type;
    // Implementează acțiunea pentru selectarea unei opțiuni din combobox aici
}

void Sig::other_clicked()
{
    otherButtonClicked();
}

void Sig::action_clicked()
{
    actionButtonClicked();
}
Sig::~Sig()
{
    delete ui;
    //UserFactory::deleteUser();
}
