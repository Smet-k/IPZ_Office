#ifndef LOGINMODAL_H
#define LOGINMODAL_H

#include <QDialog>
#include <QLineEdit>
class LoginModal : public QDialog
{
    Q_OBJECT
public:
    LoginModal(QWidget *parent = nullptr);
    QString username() const;
    QString password() const;
private:
    QLineEdit *usernameField;
    QLineEdit *passwordField;
};

#endif // LOGINMODAL_H
