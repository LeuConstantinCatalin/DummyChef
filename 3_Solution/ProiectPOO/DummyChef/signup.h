#ifndef SIGNUP_H
#define SIGNUP_H


#include "sig.h"


class SignUp : public Sig
{
    Q_OBJECT

private:
    static SignUp* instances;
    //explicit SignUp(QWidget *parent = nullptr);
    // SignUp(const SignUp&) = delete;
    // SignUp& operator=(const SignUp&) = delete;
    // virtual ~SignUp() = default;

public:
    explicit SignUp(QString mess, QWidget *parent = nullptr);
    SignUp(const SignUp&) = delete;
    SignUp& operator=(const SignUp&) = delete;
    virtual ~SignUp() = default;
    // static SignUp& createSignUp();
    // static void deleteSignUp();


    void actionButtonClicked()override;
    void otherButtonClicked()override;



};
#endif // SIGNUP_H
