#include "editemployeepage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

EditEmployeePage::EditEmployeePage() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    service = new EmployeeService(this);

    employeeNameField = new QLineEdit();
    employeeNameField->setPlaceholderText("Employee Name");
    employeeSurnameField = new QLineEdit();
    employeeSurnameField->setPlaceholderText("Employee Surname");
    employeePositionField = new QLineEdit();
    employeePositionField->setPlaceholderText("Employee Position");
    employeePasswordField = new QLineEdit();
    employeePasswordField->setPlaceholderText("Employee Password");
    employeeLoginField = new QLineEdit();
    employeeLoginField->setPlaceholderText("Employee Login");

    employeeEmploymentDateField = new QDateEdit();
    employeeEmploymentDateField->setDisplayFormat("dd-MM-yyyy");

    QVBoxLayout *loginLayout = new QVBoxLayout();
    QVBoxLayout *nameLayout = new QVBoxLayout();
    QVBoxLayout *surnameLayout = new QVBoxLayout();


    loginLayout->addWidget(new QLabel("Login:"));
    loginLayout->addWidget(employeeLoginField);

    nameLayout->addWidget(new QLabel("Name:"));
    nameLayout->addWidget(employeeNameField);

    surnameLayout->addWidget(new QLabel("Surname:"));
    surnameLayout->addWidget(employeeSurnameField);

    mainLayout->addLayout(loginLayout);
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(surnameLayout);

    QVBoxLayout *positionLayout = new QVBoxLayout();
    QVBoxLayout *employmentDateLayout = new QVBoxLayout();

    positionLayout->addWidget(new QLabel("Position:"));
    positionLayout->addWidget(employeePositionField);

    employmentDateLayout->addWidget(new QLabel("Employment Date:"));
    employmentDateLayout->addWidget(employeeEmploymentDateField);

    mainLayout->addLayout(positionLayout);
    mainLayout->addLayout(employmentDateLayout);

    QVBoxLayout *passwordLayout = new QVBoxLayout();

    passwordLayout->addWidget(new QLabel("Password:"));
    passwordLayout->addWidget(employeePasswordField);

    mainLayout->addLayout(passwordLayout);

    mainLayout->addStretch();

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *deleteBtn = new QPushButton("Delete");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    QPushButton *submitBtn = new QPushButton("Submit");

    connect(submitBtn, &QPushButton::clicked, this, [this]() {
        Employee formData = Employee(m_employee.id(), employeeLoginField->text(), employeeNameField->text(), employeeSurnameField->text(), employeePositionField->text(),
                                     employeeEmploymentDateField->date(), employeePasswordField->text());
        service->editEmployee(formData);
    });


    buttonsLayout->addWidget(deleteBtn);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addWidget(submitBtn);

    mainLayout->addLayout(buttonsLayout);
}

void EditEmployeePage::updatePage(){
    employeeNameField->setText(m_employee.name());
    employeeSurnameField->setText(m_employee.surname());
    employeePositionField->setText(m_employee.position());
    employeeEmploymentDateField->setDate(m_employee.employmentDate());
    employeePasswordField->setText(m_employee.password());
    employeeLoginField->setText(m_employee.login());
}

void EditEmployeePage::clearPage(){
    employeeNameField->clear();
    employeeSurnameField->clear();
    employeePositionField->clear();
    employeeEmploymentDateField->setDate(employeeEmploymentDateField->minimumDate());
    employeePasswordField->clear();
    employeeLoginField->clear();
    m_employee = Employee();
    m_employee.setId(0);
}
