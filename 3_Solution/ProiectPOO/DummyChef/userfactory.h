#ifndef USERFACTORY_H
#define USERFACTORY_H
#include"iuser.h"
#include<QString>

class UserFactory
{
private:
    static IUser*instance;
public:
    UserFactory();
    static IUser& createUser(QString type,QString username);
    static void deleteUser();

};

#endif // USERFACTORY_H
