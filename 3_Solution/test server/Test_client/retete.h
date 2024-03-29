#ifndef RETETE_H
#define RETETE_H

#include <QWidget>

namespace Ui {
class Retete;
}

class Retete : public QWidget
{
    Q_OBJECT

public:
    explicit Retete(QWidget *parent = nullptr);
    ~Retete();

private:
    Ui::Retete *ui;
};

#endif // RETETE_H
