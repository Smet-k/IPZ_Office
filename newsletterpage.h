#ifndef NEWSLETTERPAGE_H
#define NEWSLETTERPAGE_H

#include <QWidget>
#include <QLabel>
#include "newsletter.h"

class NewsletterPage : public QWidget
{
    Q_OBJECT
public:
    NewsletterPage();
    void updatePage();

    void setNews(Newsletter news) {m_news = news; }

    Newsletter news() const {return m_news; }
private:
    QLabel* title;
    QLabel* date;
    QLabel* body;
    Newsletter m_news;
};

#endif // NEWSLETTERPAGE_H
