/********************************************************************************
** Form generated from reading UI file 'user2.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER2_H
#define UI_USER2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_user2
{
public:

    void setupUi(QWidget *user2)
    {
        if (user2->objectName().isEmpty())
            user2->setObjectName("user2");
        user2->resize(400, 300);

        retranslateUi(user2);

        QMetaObject::connectSlotsByName(user2);
    } // setupUi

    void retranslateUi(QWidget *user2)
    {
        user2->setWindowTitle(QCoreApplication::translate("user2", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user2: public Ui_user2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER2_H
