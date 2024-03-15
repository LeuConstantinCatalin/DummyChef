#include "utilizator.h"
#include "ui_utilizator.h"

Utilizator::Utilizator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Utilizator)
{
    ui->setupUi(this);
}

Utilizator::~Utilizator()
{
    delete ui;
}
