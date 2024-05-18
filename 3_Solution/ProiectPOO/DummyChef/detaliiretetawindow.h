// Clasa DetaliiRetetaWindow (DetaliiRetetaWindow.h)
#ifndef DETALII_RETETA_WINDOW_H
#define DETALII_RETETA_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "Reteta.h"

class DetaliiRetetaWindow : public QDialog {
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

    void creazaInterfata();
};

#endif // DETALII_RETETA_WINDOW_H
