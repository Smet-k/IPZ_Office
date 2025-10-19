#ifndef EDITEMPLOYEEPAGE_H
#define EDITEMPLOYEEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>

#include "employee.h"
class EditEmployeePage : public QWidget
{
    Q_OBJECT
public:
    EditEmployeePage();

    void setEmployee (const Employee employee) {m_employee = employee; }
    void updatePage();
    void clearPage();
private:
    Employee m_employee;

    QLineEdit *employeeNameField;
    QLineEdit *employeeSurnameField;
    QLineEdit *employeePositionField;
    QDateEdit *employeeEmploymentDateField;
};

#endif // EDITEMPLOYEEPAGE_H
