#ifndef EDITNEWSPAGE_H
#define EDITNEWSPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>

#include "newsletter.h"
#include "newsservice.h"
class EditNewsPage : public QWidget
{
    Q_OBJECT
public:
    EditNewsPage();

    void setNews(const Newsletter news) {m_news = news; deleteBtn->setVisible(true);}
    void updatePage();
    void clearPage();
private:
    Newsletter m_news;
    void submitForm(Newsletter formData);

    NewsService *service;

    QPushButton *deleteBtn;
    QLineEdit *newsTitleField;
    QLineEdit *newsBodyField;
    QDateEdit *newsDateField;
signals:
    void formClosed();
};

#endif // EDITNEWSPAGE_H
