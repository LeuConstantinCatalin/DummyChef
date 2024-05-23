// Clasa DetaliiRetetaWindow (DetaliiRetetaWindow.h)
#ifndef DETALII_RETETA_WINDOW_H
#define DETALII_RETETA_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include "Reteta.h"

class DetaliiRetetaWindow : public QMainWindow {
    Q_OBJECT

public:
    DetaliiRetetaWindow(QWidget *parent = nullptr);
    void afiseazaDetaliiReteta(const Reteta& reteta);

private:
    QLabel *numeLabel;
    QLabel *ingredienteLabel;
    QLabel *modPreparareLabel;
    QLabel *pozaLabel;
    QVBoxLayout *layout;
    QListWidget* detaliiListWidget;
    QListWidget* ingredienteListWidget;

    void creazaInterfata();
};

#endif // DETALII_RETETA_WINDOW_H
