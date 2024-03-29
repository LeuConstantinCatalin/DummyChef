#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>


namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    QString getUsername() const;
    void start();
    ~SignUp();

private slots:
    void on_SignUpButton_clicked();

private:
    Ui::SignUp *ui;
    //SignUp *signUpWidget;
    QString username;

signals:
   // void signUpClosed();
};

#endif // SIGNUP_H
