#include "editviewfactory.h"
#include<QDebug>
#include"addbucatari2.h"
#include"editusers.h"
//editViewFactory::editViewFactory() {}

editView* editViewFactory::instance=nullptr;
editView& editViewFactory::createEditView(QString type, int numar)
{
    if(instance==nullptr)
    {
        if(type=="addBucatari"){
            instance=new addBucatari2("addBucatari",numar);
            qDebug()<<"am creat un nou editBucatari\n";
        }
        else
        {
            if(type=="editUsers"){
                instance=new editUsers("editUsers",numar);
                qDebug()<<"am creat un nou editUsers\n";
            }
        }

    }

    return* instance;
}


void editViewFactory::deleteEditView()
{
    if(instance!=nullptr)
    {
        delete instance;
        instance=nullptr;
        qDebug()<<"am distrus un editView\n";
    }
}
