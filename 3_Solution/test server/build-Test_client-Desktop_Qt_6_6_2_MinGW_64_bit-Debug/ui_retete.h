/********************************************************************************
** Form generated from reading UI file 'retete.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETETE_H
#define UI_RETETE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Retete
{
public:

    void setupUi(QWidget *Retete)
    {
        if (Retete->objectName().isEmpty())
            Retete->setObjectName("Retete");
        Retete->resize(400, 300);

        retranslateUi(Retete);

        QMetaObject::connectSlotsByName(Retete);
    } // setupUi

    void retranslateUi(QWidget *Retete)
    {
        Retete->setWindowTitle(QCoreApplication::translate("Retete", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Retete: public Ui_Retete {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETETE_H
