#ifndef EDITNEWSPAGE_H
#define EDITNEWSPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>

#include "newsletter.h"
class EditNewsPage : public QWidget
{
    Q_OBJECT
public:
    EditNewsPage();

    void setNews(const Newsletter news) {m_news = news; }
    void updatePage();
    void clearPage();
private:
    Newsletter m_news;

    QLineEdit *newsTitleField;
    QLineEdit *newsBodyField;
    QDateEdit *newsDateField;
};

#endif // EDITNEWSPAGE_H
