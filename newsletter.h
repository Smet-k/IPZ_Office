#ifndef NEWSLETTER_H
#define NEWSLETTER_H

#include <QString>
#include <QDate>

class Newsletter {
public:
    Newsletter(const QString &title = "",
               const QString &body = "",
               const QDate &date = QDate::currentDate())
        : m_title(title), m_body(body), m_date(date) {}

    QString title() const {return m_title; }
    QString body() const {return m_body; }
    QDate date() const {return m_date; }

    void setTitle(const QString &title) { m_title = title; }
    void setBody(const QString &body) { m_body = body; }
    void setDate(const QDate &date) { m_date = date; }
private:
    QString m_title;
    QString m_body;
    QDate m_date;
};

#endif // NEWSLETTER_H
