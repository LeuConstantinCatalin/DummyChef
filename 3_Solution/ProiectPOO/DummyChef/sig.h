#ifndef SIG_H
#define SIG_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include<QString>

#include "isign.h"
namespace Ui {
class Sig;
}

class Sig : public QWidget, public ISign
{
    Q_OBJECT

public:
    explicit Sig(QString message,QWidget *parent = nullptr);
    ~Sig();
    void actionButtonClicked() override=0;
    void otherButtonClicked() override=0;
    void show() override{ QWidget::show();};
private:
    Ui::Sig *ui;

// protected slots:
//     void on_other_clicked();
protected:
    QString type="utilizator";
    QPushButton* action;
    QPushButton* other;
    QLabel* usernameText;
    QLabel* passwordText;
    QLineEdit* usernameInput;
    QLineEdit* passwordInput;
    QLineEdit* message;


private slots:
    void other_clicked();
    void action_clicked();

};

#endif // SIG_H
