#include "loginmodal.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
LoginModal::LoginModal(QWidget *parent)
    :QDialog(parent){
    this->setFixedSize(200, 175);
    setWindowTitle("Login");
    setModal(true);

    QVBoxLayout *loginLayout = new QVBoxLayout(this);
    loginLayout->setSpacing(15);
    usernameField = new QLineEdit();
    passwordField = new QLineEdit();
    passwordField->setEchoMode(QLineEdit::Password);

    QPushButton *confirmBtn = new QPushButton("Login");
    QPushButton *cancelBtn = new QPushButton("Cancel");

    QVBoxLayout *fields = new QVBoxLayout();
    fields->setSpacing(4);
    fields->addWidget(new QLabel("Username:"));
    fields->addWidget(usernameField);
    fields->addWidget(new QLabel("Password:"));
    fields->addWidget(passwordField);

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(cancelBtn);
    buttons->addWidget(confirmBtn);

    loginLayout->addLayout(fields);
    loginLayout->addLayout(buttons);

    connect(confirmBtn, &QPushButton::clicked, this, &LoginModal::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &LoginModal::reject);
}

QString LoginModal::username() const { return usernameField->text(); }
QString LoginModal::password() const { return passwordField->text(); }
