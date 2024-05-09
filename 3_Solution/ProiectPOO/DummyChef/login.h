// // login.h
#ifndef LOGIN_H
#define LOGIN_H

 #include "sig.h"
// #include <QDialog>
#include <QComboBox>
class Login : public Sig
 {
    Q_OBJECT

 private:

    QComboBox *comboBox;

    //static Login* instancel;
    //explicit Login(QWidget *parent = nullptr);
    // Login(const Login&) = delete;
    // Login& operator=(const Login&) = delete;
    // virtual ~Login() = default;
 public:
    explicit Login(QString message,QWidget *parent = nullptr);
     Login(const Login&) = delete;
     Login& operator=(const Login&) = delete;
     virtual ~Login() = default;

    // static Login& createLogin();
    // static void deleteLogin();

    void actionButtonClicked()override;
    void otherButtonClicked()override;
private slots:
    void comboBoxActivated();

 };

 #endif // LOGIN_H

