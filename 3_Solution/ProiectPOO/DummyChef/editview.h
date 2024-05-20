#ifndef EDITVIEW_H
#define EDITVIEW_H
#include <QString>


class editView
{
public:
    //editView();
    virtual void createView(QString action)=0;
    virtual void show() =0;
    virtual ~editView(){}

};

#endif // EDITVIEW_H
