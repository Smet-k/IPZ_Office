#include "editemployeepage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "position.h"
#include "employeeroles.h"
EditEmployeePage::EditEmployeePage() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    service = new EmployeeService(this);
    posService = new PositionService(this);

    employeeNameField = new QLineEdit();
    employeeNameField->setPlaceholderText("Employee Name");
    employeeSurnameField = new QLineEdit();
    employeeSurnameField->setPlaceholderText("Employee Surname");
    employeePositionField = new QComboBox();
    employeePositionField->setPlaceholderText("Employee Position");
    employeeRoleField = new QComboBox();
    employeeRoleField->setPlaceholderText("Employee Role");
    employeePasswordField = new QLineEdit();
    employeePasswordField->setPlaceholderText("Employee Password");
    employeeLoginField = new QLineEdit();
    employeeLoginField->setPlaceholderText("Employee Login");

    employeeEmploymentDateField = new QDateEdit();
    employeeEmploymentDateField->setDisplayFormat("dd-MM-yyyy");

    // SETTING UP COMBO BOXES
    connect(posService, &PositionService::positionsReady, this, [=](const QList<Position> list){
        employeePositionField->clear();

        for (const Position &pos : list){
            employeePositionField->addItem(
                pos.title(),
                pos.id()
            );
        }
    });

    posService->fetchPositions();

    employeeRoleField->addItem(EmployeeRoles::toString(EmployeeRoles::Employee),     EmployeeRoles::Employee);
    employeeRoleField->addItem(EmployeeRoles::toString(EmployeeRoles::Admin),    EmployeeRoles::Admin);
    employeeRoleField->addItem(EmployeeRoles::toString(EmployeeRoles::SysAdmin), EmployeeRoles::SysAdmin);

    // END
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

    QVBoxLayout *roleLayout = new QVBoxLayout();
    QVBoxLayout *positionLayout = new QVBoxLayout();
    QVBoxLayout *employmentDateLayout = new QVBoxLayout();

    roleLayout->addWidget(new QLabel("Role:"));
    roleLayout->addWidget(employeeRoleField);

    positionLayout->addWidget(new QLabel("Position:"));
    positionLayout->addWidget(employeePositionField);

    employmentDateLayout->addWidget(new QLabel("Employment Date:"));
    employmentDateLayout->addWidget(employeeEmploymentDateField);

    mainLayout->addLayout(positionLayout);
    mainLayout->addLayout(roleLayout);
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
        Employee formData = Employee(m_employee.id(), employeeLoginField->text(), employeeNameField->text(), employeeSurnameField->text(), "", employeePositionField->currentData().toInt(),
                                     employeeEmploymentDateField->date(), employeePasswordField->text(), employeeRoleField->currentData().toInt());
        service->editEmployee(formData);
    });

    connect(service, &EmployeeService::employeeEdited, this, [=](const int status){
        if(status > 0){
            emit formClosed();
        }
        // else process messages
    });

    connect(cancelBtn, &QPushButton::clicked, this, [this](){
        emit formClosed();
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
    int index = employeePositionField->findData(m_employee.positionId());
    employeePositionField->setCurrentIndex(index);
    employeeEmploymentDateField->setDate(m_employee.employmentDate());
    employeePasswordField->setText(m_employee.password());
    employeeLoginField->setText(m_employee.login());
}

void EditEmployeePage::clearPage(){
    employeeNameField->clear();
    employeeSurnameField->clear();
    employeePositionField->setCurrentIndex(0);
    employeeEmploymentDateField->setDate(employeeEmploymentDateField->minimumDate());
    employeePasswordField->clear();
    employeeLoginField->clear();
    m_employee = Employee();
    m_employee.setId(0);
}
