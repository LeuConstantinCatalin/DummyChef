#ifndef ADDBUCATARI2_H
#define ADDBUCATARI2_H

#include "ceditview.h"

#include <QWidget>

namespace Ui {
class addBucatari2;
}

class addBucatari2 : public CeditView
{
    Q_OBJECT

public:
    explicit addBucatari2(QString action,int nr,QWidget *parent = nullptr);
   // void createView(QString action)override;
    ~addBucatari2();

private:
    Ui::addBucatari2 *ui;
    void addMiniBox(const QString& message, QVBoxLayout* contentLayout, QWidget* contentWidget)override;
    //void createView(QString action,int nr)override;
};

#endif // ADDBUCATARI2_H
