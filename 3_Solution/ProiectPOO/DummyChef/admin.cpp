#include "admin.h"
//#include "ui_bucatar.h"

Admin::Admin(QString userN,QWidget *parent)
    : Bucatar(userN,parent)

{
    ModificareUseri=new QPushButton("ModificareUseri",this);
    ModificareUseri->setGeometry(20,180,130,30);
    connect(ModificareUseri, &QPushButton::clicked, this, &Admin::modificareUseri_clicked);
}

Admin::~Admin()
{
    //delete ui;
}
