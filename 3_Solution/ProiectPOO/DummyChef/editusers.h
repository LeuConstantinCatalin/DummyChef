#ifndef EDITUSERS_H
#define EDITUSERS_H

#include "ceditview.h"

#include <QWidget>

namespace Ui {
class editUsers;
}

class editUsers : public CeditView
{
    Q_OBJECT

public:
    explicit editUsers(QString action,int nr,QWidget *parent = nullptr);
    ~editUsers();

private:
    Ui::editUsers *ui;
    void addMiniBox(const QString& message, QVBoxLayout* contentLayout, QWidget* contentWidget)override;
};

#endif // EDITUSERS_H
