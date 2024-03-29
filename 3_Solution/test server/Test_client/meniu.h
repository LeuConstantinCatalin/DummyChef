// meniu.h
#ifndef MENIU_H
#define MENIU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include<QDebug>

class Meniu : public QWidget
{
    Q_OBJECT

public:
    explicit Meniu(QWidget *parent = nullptr);
    ~Meniu();

    // Metode publice pentru a obține referințe către butoanele existente
    QPushButton* getButton1() const { return button1; }
    QPushButton* getButton2() const { return button2; }
    QPushButton* getButton3() const { return button3; }

signals:
    void logoutClicked(); // Semnal pentru a indica că butonul de logout a fost apăsat
    void reteteClicked();
    void listaDeIngredienteClicked();


private slots:
    void handleButton1Clicked();
    void handleButton2Clicked();
    void handleButton3Clicked();

private:
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
};

#endif // MENIU_H
