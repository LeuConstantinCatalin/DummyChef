#ifndef CUMPARATURIWINDOW_H
#define CUMPARATURIWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QList>
#include "ingredient.h"

class CumparaturiWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit CumparaturiWindow(QList<Ingredient> li, QWidget *parent = nullptr);

private slots:
    void adaugaProdus();
    void stergeProdus();
    void populeazaCumparaturi();

private:
    QList<Ingredient> guiListaIngrediente;

    QListWidget *listaProduse;
    QLineEdit *numeProdusEdit;
    QPushButton *adaugaButton;
    QPushButton *stergeButton;
    QPushButton* populeazaCumparaturiButton;
    QListWidget *detaliiListWidget;
    QListWidget *cumparaturi;

};

#endif // CUMPARATURIWINDOW_H
