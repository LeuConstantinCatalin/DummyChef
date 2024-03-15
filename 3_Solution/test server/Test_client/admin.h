#ifndef ADMIN_H
#define ADMIN_H
#include"user.h"
#include <QWidget>

namespace Ui {
class Admin;
}

class Admin : public QWidget,public User
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);

    void start(const QString u);
    ~Admin();

private slots:


private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
