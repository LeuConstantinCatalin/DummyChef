#ifndef CEDITVIEW_H
#define CEDITVIEW_H

#include <QWidget>
#include<QVBoxLayout>
#include "editView.h"

namespace Ui {
class editView;
}

class CeditView : public QWidget,public editView
{
    Q_OBJECT

public:
    explicit CeditView(QString action,int n,QWidget *parent = nullptr);
    ~CeditView();
    //int n=0;
    virtual void createView(QString action)override;
    void show() override{ QWidget::show();};

signals:
    void userDeleted();
protected:
    int nr;
    Ui::editView *ui;
    virtual void addMiniBox(const QString& message, QVBoxLayout* contentLayout, QWidget* contentWidget);
};

#endif // CEDITVIEW_H
