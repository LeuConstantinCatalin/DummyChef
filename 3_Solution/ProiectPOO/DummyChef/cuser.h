#ifndef CUSER_H
#define CUSER_H
#include"iuser.h"
#include "reteta.h"
#include "ingredient.h"
#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include <QSet>
#include <QListWidget>

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
    virtual void retete_clicked();
    virtual void listaDeCumparaturi_clicked();
    virtual void logOut_clicked();
    virtual void onRetetaButtonClicked();
    virtual void enter_clicked();
    virtual void statistici_clicked();

protected:

    QString username="~";
    QLabel* MenuTitle;
    QLabel* WelcomeMessage;
    QPushButton* Retete;
    QPushButton* ListaDeCumparaturi;
    QPushButton* LogOut;
    QPushButton* EnterReteta;
    QPushButton* Statistici;

    QList<QPushButton*> buttonsList;
    QListWidget *listaButoaneRetete;
    QListWidget *listaStatistici;

    QList<Reteta> listaRetete;
    QList<Ingredient> listaIngrediente;

    void populare_lista_retete(const QString& fileWithPaths);
};

#endif // CUSER_H
