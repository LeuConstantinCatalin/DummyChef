#ifndef USER_H
#define USER_H
#include <QString>//

//#include <QWidget>

class User
{
protected:
    QString username;
public:
    User();
    void addUsername(const QString u);
    virtual void start(const QString u)=0;
    virtual void onLogoutClicked()=0;

};

#endif // USER_H
