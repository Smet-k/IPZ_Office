#include "editemployeepage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

EditEmployeePage::EditEmployeePage() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    employeeNameField = new QLineEdit();
    employeeNameField->setPlaceholderText("Employee Name");
    employeeSurnameField = new QLineEdit();
    employeeSurnameField->setPlaceholderText("Employee Surname");
    employeePositionField = new QLineEdit();
    employeePositionField->setPlaceholderText("Employee Position");
    employeeEmploymentDateField = new QDateEdit();

    QVBoxLayout *nameLayout = new QVBoxLayout();
    QVBoxLayout *surnameLayout = new QVBoxLayout();

    nameLayout->addWidget(new QLabel("Name:"));
    nameLayout->addWidget(employeeNameField);

    surnameLayout->addWidget(new QLabel("Surname:"));
    surnameLayout->addWidget(employeeSurnameField);

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

    mainLayout->addStretch();

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *deleteBtn = new QPushButton("Delete");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    QPushButton *submitBtn = new QPushButton("Submit");

    buttonsLayout->addWidget(deleteBtn);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addWidget(submitBtn);

    mainLayout->addLayout(buttonsLayout);
}

void EditEmployeePage::updatePage(){
    employeeNameField->setText(m_employee.name());
    employeeSurnameField->setText(m_employee.surname());
    employeePositionField->setText(m_employee.name());
    employeeEmploymentDateField->setDate(m_employee.employmentDate());
}

void EditEmployeePage::clearPage(){
    employeeNameField->clear();
    employeeSurnameField->clear();
    employeePositionField->clear();
    employeeEmploymentDateField->setDate(employeeEmploymentDateField->minimumDate());

    m_employee = Employee();
}
