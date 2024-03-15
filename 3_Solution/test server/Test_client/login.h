#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "signup.h"
#include "admin.h"


namespace Ui {
class LOGIN;
}

class LOGIN : public QWidget
{
    Q_OBJECT

public:
    explicit LOGIN(QWidget *parent = nullptr);
    QString getUsername() const;
    void start();
    ~LOGIN();


private:
    Ui::LOGIN *ui;
    //SignUp *signUpWidget;
    //Admin *admin;
    QString username;

signals:
    void loginClosed();

private slots:
    void on_LoginButton_clicked();
    void on_SignUpRedirect_clicked();
};

#endif // LOGIN_H
