#ifndef MANAGEPAGE_H
#define MANAGEPAGE_H

#include <QWidget>
#include <QStackedWidget>
#include "clickablewidget.h"
#include "newsletter.h"
#include "employee.h"
#include "newsservice.h"
#include "employeeservice.h"

class ManagePage : public QWidget
{
    Q_OBJECT
public:
    ManagePage();

private slots:
    void showEmployeeSection();
    void showNewsSection();
private:
    ClickableWidget* createNewsRow(Newsletter news);
    ClickableWidget* createEmployeeRow(Employee employee);
    void updateList();

    NewsService *newsService;
    EmployeeService *employeeService;

    QStackedWidget *stack;
    QWidget *employeeSection;
    QWidget *newsSection;
signals:
    void goToEmployeeEdit(Employee employee);
    void goToEmployeeAdd();
    void goToNewsEdit(Newsletter news);
    void goToNewsAdd();
};

#endif // MANAGEPAGE_H
