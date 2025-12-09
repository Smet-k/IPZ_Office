#include "loginmodal.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "employeeservice.h"
#include <stdio.h>
LoginModal::LoginModal(QWidget *parent)
    :QDialog(parent){
    this->setFixedSize(200, 175);
    setWindowTitle("Login");
    setModal(true);

    service = new EmployeeService(this);

    QVBoxLayout *loginLayout = new QVBoxLayout(this);
    loginLayout->setSpacing(15);
    loginField = new QLineEdit();
    passwordField = new QLineEdit();
    passwordField->setEchoMode(QLineEdit::Password);

    QPushButton *confirmBtn = new QPushButton("Login");
    QPushButton *cancelBtn = new QPushButton("Cancel");

    QVBoxLayout *fields = new QVBoxLayout();
    fields->setSpacing(4);
    fields->addWidget(new QLabel("Login:"));
    fields->addWidget(loginField);
    fields->addWidget(new QLabel("Password:"));
    fields->addWidget(passwordField);

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(cancelBtn);
    buttons->addWidget(confirmBtn);

    loginLayout->addLayout(fields);
    loginLayout->addLayout(buttons);

    connect(service, &EmployeeService::employeeAuthorized, this, [=](const Employee &employee){
        emit authorizationSuccessful(employee);
        accept();
    });

    connect(confirmBtn, &QPushButton::clicked, this, [this]{
        service->authEmployee(loginField->text(), passwordField->text());
    });
    connect(cancelBtn, &QPushButton::clicked, this, &LoginModal::reject);
}



QString LoginModal::login() const { return loginField->text(); }
QString LoginModal::password() const { return passwordField->text(); }
