/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QLineEdit *username;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *SignUpButton;

    void setupUi(QWidget *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(400, 300);
        username = new QLineEdit(SignUp);
        username->setObjectName("username");
        username->setGeometry(QRect(190, 70, 113, 24));
        lineEdit_2 = new QLineEdit(SignUp);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(190, 140, 113, 24));
        label = new QLabel(SignUp);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 70, 49, 16));
        label_2 = new QLabel(SignUp);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 150, 49, 16));
        SignUpButton = new QPushButton(SignUp);
        SignUpButton->setObjectName("SignUpButton");
        SignUpButton->setGeometry(QRect(140, 230, 80, 24));

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QWidget *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "Form", nullptr));
        label->setText(QCoreApplication::translate("SignUp", "username", nullptr));
        label_2->setText(QCoreApplication::translate("SignUp", "password", nullptr));
        SignUpButton->setText(QCoreApplication::translate("SignUp", "SignUp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
