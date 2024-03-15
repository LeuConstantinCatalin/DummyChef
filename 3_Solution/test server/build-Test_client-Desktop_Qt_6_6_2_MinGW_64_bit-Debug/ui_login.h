/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LOGIN
{
public:
    QPushButton *LoginButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *passwordInput;
    QPushButton *SignUpRedirect;
    QLabel *label_2;

    void setupUi(QWidget *LOGIN)
    {
        if (LOGIN->objectName().isEmpty())
            LOGIN->setObjectName("LOGIN");
        LOGIN->resize(400, 300);
        LoginButton = new QPushButton(LOGIN);
        LoginButton->setObjectName("LoginButton");
        LoginButton->setGeometry(QRect(150, 200, 80, 24));
        label = new QLabel(LOGIN);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 100, 61, 16));
        lineEdit = new QLineEdit(LOGIN);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(200, 100, 113, 24));
        passwordInput = new QLineEdit(LOGIN);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setGeometry(QRect(200, 150, 113, 24));
        SignUpRedirect = new QPushButton(LOGIN);
        SignUpRedirect->setObjectName("SignUpRedirect");
        SignUpRedirect->setGeometry(QRect(290, 20, 80, 24));
        label_2 = new QLabel(LOGIN);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 140, 49, 16));

        retranslateUi(LOGIN);

        QMetaObject::connectSlotsByName(LOGIN);
    } // setupUi

    void retranslateUi(QWidget *LOGIN)
    {
        LOGIN->setWindowTitle(QCoreApplication::translate("LOGIN", "Form", nullptr));
        LoginButton->setText(QCoreApplication::translate("LOGIN", "LOGIN", nullptr));
        label->setText(QCoreApplication::translate("LOGIN", "username", nullptr));
        SignUpRedirect->setText(QCoreApplication::translate("LOGIN", "SignUp", nullptr));
        label_2->setText(QCoreApplication::translate("LOGIN", "parola", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LOGIN: public Ui_LOGIN {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
