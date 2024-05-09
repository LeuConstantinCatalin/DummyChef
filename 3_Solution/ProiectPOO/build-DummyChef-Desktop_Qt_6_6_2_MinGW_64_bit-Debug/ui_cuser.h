/********************************************************************************
** Form generated from reading UI file 'cuser.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSER_H
#define UI_CUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CUser
{
public:

    void setupUi(QWidget *CUser)
    {
        if (CUser->objectName().isEmpty())
            CUser->setObjectName("CUser");
        CUser->resize(400, 300);

        retranslateUi(CUser);

        QMetaObject::connectSlotsByName(CUser);
    } // setupUi

    void retranslateUi(QWidget *CUser)
    {
        CUser->setWindowTitle(QCoreApplication::translate("CUser", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CUser: public Ui_CUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSER_H
