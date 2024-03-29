/********************************************************************************
** Form generated from reading UI file 'meniu.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENIU_H
#define UI_MENIU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Meniu
{
public:

    void setupUi(QWidget *Meniu)
    {
        if (Meniu->objectName().isEmpty())
            Meniu->setObjectName("Meniu");
        Meniu->resize(400, 300);

        retranslateUi(Meniu);

        QMetaObject::connectSlotsByName(Meniu);
    } // setupUi

    void retranslateUi(QWidget *Meniu)
    {
        Meniu->setWindowTitle(QCoreApplication::translate("Meniu", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Meniu: public Ui_Meniu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENIU_H
