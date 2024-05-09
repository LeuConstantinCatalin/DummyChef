/********************************************************************************
** Form generated from reading UI file 'sig.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIG_H
#define UI_SIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sig
{
public:

    void setupUi(QWidget *Sig)
    {
        if (Sig->objectName().isEmpty())
            Sig->setObjectName("Sig");
        Sig->resize(400, 300);

        retranslateUi(Sig);

        QMetaObject::connectSlotsByName(Sig);
    } // setupUi

    void retranslateUi(QWidget *Sig)
    {
        Sig->setWindowTitle(QCoreApplication::translate("Sig", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sig: public Ui_Sig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIG_H
