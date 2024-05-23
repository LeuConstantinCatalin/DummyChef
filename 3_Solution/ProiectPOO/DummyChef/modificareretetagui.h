#ifndef MODIFICARE_RETETA_GUI_H
#define MODIFICARE_RETETA_GUI_H

#include <QMainWindow>
#include "reteta.h" // Asigură-te că ai inclus fișierul care definește clasa Reteta

class QLineEdit;
class QTextEdit;
class QPushButton;

class ModificareRetetaGUI : public QMainWindow
{
    Q_OBJECT

public:
    ModificareRetetaGUI(Reteta& r, QWidget *parent = nullptr);
    ~ModificareRetetaGUI();

private slots:
    void aplicareModificari();

private:
    Reteta& reteta;
    QLineEdit* numeLineEdit;
    QList<QLineEdit*> listaIngredienteLineEdit;
    QLineEdit* modPreparareTextEdit;
    QPushButton* modificaButton;

    void setupUI();
};

#endif // MODIFICARE_RETETA_GUI_H

