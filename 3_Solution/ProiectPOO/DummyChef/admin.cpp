#include "admin.h"
#include "editviewfactory.h"
#include "serverconector.h"
#include "userfactory.h"
#include <QThread>
//#include "ui_bucatar.h"

Admin::Admin(QString userN,QWidget *parent)
    : Bucatar(userN,parent)

{
    AddBucatari=new QPushButton("AddBucatari",this);
    AddBucatari->setGeometry(20,180,130,30);
    connect(AddBucatari, &QPushButton::clicked, this, &Admin::AddBucatari_clicked);

    EditUsers=new QPushButton("EditUsers",this);
    EditUsers->setGeometry(20,230,130,30);
    connect(EditUsers, &QPushButton::clicked, this, &Admin::EditUsers_clicked);
}

void Admin::AddBucatari_clicked()
{
    this->close();
    editViewFactory::createEditView("addBucatari",0).show();
}

void Admin::EditUsers_clicked()
{
    this->close();
    editViewFactory::createEditView("editUsers",0).show();
}

Admin::~Admin()
{
    //delete ui;
}
