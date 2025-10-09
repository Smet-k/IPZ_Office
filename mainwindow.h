#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include "homepage.h"
#include "statpage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void setClockIn(bool state);
private slots:
    void showHomePage();
    void showStatpage();
    void onLoginButtonClicked();
signals:
    void clockStateChanged(bool clockIn);
    void authorizationStateChanged(bool authorization);
private:
    bool clockIn = false;
    bool userAuthorized = false;

    QStackedWidget *stack;
    HomePage *homePage;
    StatPage *statPage;
    void initializeOverlays();
    QWidget* createSidemenu();
    void setPageInteractable(bool enabled);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MAINWINDOW_H
