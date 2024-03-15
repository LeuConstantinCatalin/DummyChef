#ifndef BUCATAR_H
#define BUCATAR_H

#include <QWidget>

namespace Ui {
class Bucatar;
}

class Bucatar : public QWidget
{
    Q_OBJECT

public:
    explicit Bucatar(QWidget *parent = nullptr);
    ~Bucatar();

private:
    Ui::Bucatar *ui;
};

#endif // BUCATAR_H
