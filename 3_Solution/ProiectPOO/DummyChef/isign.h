// isign.h
#ifndef ISIGN_H
#define ISIGN_H
#include"QString"

class ISign
{
public:
    virtual ~ISign(){};
    virtual void actionButtonClicked() = 0;
    virtual void otherButtonClicked() = 0;
    virtual void show() =0;
};
#endif // ISIGN_H


