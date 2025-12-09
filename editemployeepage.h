#ifndef EDITEMPLOYEEPAGE_H
#define EDITEMPLOYEEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>

#include "employee.h"
#include "employeeservice.h"
#include "positionservice.h"
class EditEmployeePage : public QWidget
{
    Q_OBJECT
public:
    EditEmployeePage();


    void setEmployee (const Employee employee) {m_employee = employee; }
    void updatePage();
    void clearPage();
private:
    void submitForm(Employee formData);

    EmployeeService *service;
    PositionService *posService;

    Employee m_employee;

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
