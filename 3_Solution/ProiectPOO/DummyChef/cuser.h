#ifndef CUSER_H
#define CUSER_H
#include"iuser.h"
#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>

namespace Ui {
class CUser;
}

class CUser : public QWidget, public IUser
{
    Q_OBJECT

public:
    explicit CUser(QString userN="!",QWidget *parent = nullptr);
    ~CUser();
    void show() override { QWidget::show();}

private:
    Ui::CUser *ui;

private slots:
    virtual void retete_clicked(){};
    virtual void listaDeCumparaturi_clicked(){};
    virtual void logOut_clicked();

protected:

    QString username="~";
    QLabel* MenuTitle;
    QLabel* WelcomeMessage;
    QPushButton* Retete;
    QPushButton* ListaDeCumparaturi;
    QPushButton* LogOut;
};

#endif // CUSER_H
