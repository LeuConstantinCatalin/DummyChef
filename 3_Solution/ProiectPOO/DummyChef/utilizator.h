#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <QWidget>
#include"cuser.h"



class Utilizator : public CUser
{
    Q_OBJECT
private:
    //static Utilizator* instance;
public:
    // static Utilizator* createUtilizator(QString userN);
    // static void deleteUtilizator();
    explicit Utilizator(QString userN,QWidget *parent = nullptr);
    ~Utilizator();
protected slots:
    //void listaDeCumparaturi_clicked()override{};
    //void logOut_clicked() override{qDebug()<<"Sunt in utilizator\n";};
// private:
//     Ui::Utilizator *ui;
};

#endif // UTILIZATOR_H
