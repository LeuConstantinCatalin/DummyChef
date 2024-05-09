#ifndef SIGNFACTORY_H
#define SIGNFACTORY_H
#include "isign.h"
#include<QString>
class SignFactory
{
public:
    SignFactory();

private:
    static ISign* instance;
public:
    static ISign& createSign(QString mess, QString type);
    static void deleteSign();
};

#endif // SIGNFACTORY_H
