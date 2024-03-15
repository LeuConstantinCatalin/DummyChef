#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <QWidget>

namespace Ui {
class Utilizator;
}

class Utilizator : public QWidget
{
    Q_OBJECT

public:
    explicit Utilizator(QWidget *parent = nullptr);
    ~Utilizator();

private:
    Ui::Utilizator *ui;
};

#endif // UTILIZATOR_H
