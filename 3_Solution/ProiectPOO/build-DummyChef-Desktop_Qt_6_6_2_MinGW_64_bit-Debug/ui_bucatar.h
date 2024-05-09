/********************************************************************************
** Form generated from reading UI file 'bucatar.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUCATAR_H
#define UI_BUCATAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Bucatar
{
public:

    void setupUi(QWidget *Bucatar)
    {
        if (Bucatar->objectName().isEmpty())
            Bucatar->setObjectName("Bucatar");
        Bucatar->resize(400, 300);

        retranslateUi(Bucatar);

        QMetaObject::connectSlotsByName(Bucatar);
    } // setupUi

    void retranslateUi(QWidget *Bucatar)
    {
        Bucatar->setWindowTitle(QCoreApplication::translate("Bucatar", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Bucatar: public Ui_Bucatar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUCATAR_H
