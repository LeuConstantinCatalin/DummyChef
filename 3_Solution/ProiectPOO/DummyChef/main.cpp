#include <QApplication>


#include"signfactory.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   SignFactory::createSign(" ","LOGIN").show();


    return a.exec();
}

