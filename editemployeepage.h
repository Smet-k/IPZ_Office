#ifndef EDITEMPLOYEEPAGE_H
#define EDITEMPLOYEEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>

#include "employee.h"
#include "employeeservice.h"
#include "positionservice.h"
#include <QPushButton>
class EditEmployeePage : public QWidget
{
    Q_OBJECT
public:
    EditEmployeePage();


    void setEmployee (const Employee employee) {m_employee = employee; deleteBtn->setVisible(true); }
    void updatePage();
    void clearPage();
private:
    void submitForm(Employee formData);

    EmployeeService *service;
    PositionService *posService;

    Employee m_employee;
    QPushButton *deleteBtn;
    QLineEdit *employeeLoginField;
    QLineEdit *employeeNameField;
    QLineEdit *employeeSurnameField;
    QComboBox *employeePositionField;
    QComboBox *employeeRoleField;
    QDateEdit *employeeEmploymentDateField;
    QLineEdit *employeePasswordField;
signals:
    void formClosed();
};

#endif // EDITEMPLOYEEPAGE_H
