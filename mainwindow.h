#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include "homepage.h"
#include "statpage.h"
#include "newsletterpage.h"
#include "newsletter.h"
#include "managepage.h"
#include "employee.h"
#include "editemployeepage.h"
#include "editnewspage.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void setClockIn(bool state);
private slots:
    void showHomePage();
    void showStatpage();
    void showManagePage();
    void showEditEmployeePage(Employee employee);
    void showAddEmployeePage();
    void showEditNewsPage(Newsletter news);
    void showAddNewsPage();
    void showNewsPage(Newsletter news);
    void onLoginButtonClicked();
signals:
    void clockStateChanged(bool clockIn);
    void authorizationStateChanged(bool authorization);
private:
    bool clockIn = false;
    bool userAuthorized = false;

    EditEmployeePage *editEmployeePage;
    EditNewsPage *editNewsPage;
    ManagePage *managePage;
    NewsletterPage *newsPage;
    QStackedWidget *stack;
    HomePage *homePage;
    StatPage *statPage;
    void initializeOverlays();
    QWidget* createSidemenu();
    void setPageInteractable(bool enabled);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MAINWINDOW_H
