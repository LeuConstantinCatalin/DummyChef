#include "retete.h"
#include "ui_retete.h"

Retete::Retete(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Retete)
{
    ui->setupUi(this);
}

Retete::~Retete()
{
    delete ui;
}
