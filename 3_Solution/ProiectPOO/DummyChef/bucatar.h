#ifndef BUCATAR_H
#define BUCATAR_H

#include <QWidget>
#include"utilizator.h"
#include "modificareretetagui.h"

// namespace Ui {
// class Bucatar;
// }

class Bucatar : public Utilizator
{
    Q_OBJECT

public:

    explicit Bucatar(QString userN,QWidget *parent = nullptr);
    //~Utilizator();
    //explicit Bucatar(QWidget *parent = nullptr);
    ~Bucatar();
protected slots:
    void alterRetete_clicked();
private:
    QPushButton* AlterRetete;

    //Ui::Bucatar *ui;
};

#endif // BUCATAR_H
