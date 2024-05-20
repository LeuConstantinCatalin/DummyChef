#ifndef EDITVIEWFACTORY_H
#define EDITVIEWFACTORY_H
#include "editview.h"
class editViewFactory
{
private:
    static editView* instance;
public:
 //   editViewFactory();
    static editView& createEditView(QString type,int numar);
    static void deleteEditView();
};

#endif // EDITVIEWFACTORY_H


