#include "admin.h"
#include "ui_admin.h"

#include"login.h"

Admin::Admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    Meniu *meniu = new Meniu(this);
    layout->addWidget(meniu);

    // Conectează semnalul de logout din meniu la slot-ul din Admin
    connect(meniu, &Meniu::logoutClicked, this, &Admin::onLogoutClicked);
}

Admin::~Admin()
{
    delete ui;
}



void Admin::start(const QString u)
{
    this->username=u;
    ui->username->setText(u);
}

void Admin::onLogoutClicked()
{
    this->close();
    //ui->username->clear();
    LOGIN *l=new LOGIN();
    l->show();
}

