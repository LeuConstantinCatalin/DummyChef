#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include"user.h"
namespace Ui {
class Admin;
}

class Admin : public QWidget,public User
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);

    void start(const QString u);

    void onLogoutClicked();
    ~Admin();

private slots:


    //void on_pushButton_4_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
