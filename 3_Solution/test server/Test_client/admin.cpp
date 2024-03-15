#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);

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
