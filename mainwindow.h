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
private slots:
    void showHomePage();
    void showStatpage();
private:
    QWidget* createSidemenu();
    QStackedWidget *stack;
    HomePage *homePage;
    StatPage *statPage;
};

#endif // MAINWINDOW_H
