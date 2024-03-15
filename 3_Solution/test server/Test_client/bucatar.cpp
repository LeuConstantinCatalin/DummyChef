#include "bucatar.h"
#include "ui_bucatar.h"

Bucatar::Bucatar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bucatar)
{
    ui->setupUi(this);
}

Bucatar::~Bucatar()
{
    delete ui;
}
