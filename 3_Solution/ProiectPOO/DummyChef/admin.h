#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include"bucatar.h"

// namespace Ui {
// class Bucatar;
// }

class Admin : public Bucatar
{
    Q_OBJECT

public:

    explicit Admin(QString userN,QWidget *parent = nullptr);
    //~Utilizator();
    //explicit Bucatar(QWidget *parent = nullptr);
    ~Admin();

private:
    //Ui::Bucatar *ui;
};

#endif // ADMIN_H
