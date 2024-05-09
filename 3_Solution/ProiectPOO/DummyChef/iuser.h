#ifndef IUSER_H
#define IUSER_H

#include<QLabel>


class IUser
{
public:
    virtual void show()=0;
    virtual ~IUser(){};
};

#endif // IUSER_H

// class FactoryUser
// {
//     //public static
// }
