/********************************************************************************
** Form generated from reading UI file 'utilizator.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UTILIZATOR_H
#define UI_UTILIZATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Utilizator
{
public:

    void setupUi(QWidget *Utilizator)
    {
        if (Utilizator->objectName().isEmpty())
            Utilizator->setObjectName("Utilizator");
        Utilizator->resize(400, 300);

        retranslateUi(Utilizator);

        QMetaObject::connectSlotsByName(Utilizator);
    } // setupUi

    void retranslateUi(QWidget *Utilizator)
    {
        Utilizator->setWindowTitle(QCoreApplication::translate("Utilizator", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Utilizator: public Ui_Utilizator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UTILIZATOR_H
