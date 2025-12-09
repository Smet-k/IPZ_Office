#ifndef NEWSLETTER_H
#define NEWSLETTER_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class Newsletter {
public:
    Newsletter(const int &id = 0,
               const QString &title = "",
               const QString &body = "",
               const QDate &date = QDate::currentDate())
        : m_id(id) ,m_title(title), m_body(body), m_date(date) {}

    static Newsletter fromJson(const QJsonObject &obj) {
        return Newsletter(
            obj["id"].toInt(),
            obj["title"].toString(),
            obj["body"].toString(),
            QDate::fromString(obj["date"].toString(), Qt::ISODate)
            );
    }

    QString title() const {return m_title; }
    QString body() const {return m_body; }
    QDate date() const {return m_date; }
    int id() const {return m_id;}

    void setTitle(const QString &title) { m_title = title; }
    void setBody(const QString &body) { m_body = body; }
    void setDate(const QDate &date) { m_date = date; }
    void setId(const int &id) {m_id = id;}
private:
    int m_id;
    QString m_title;
    QString m_body;
    QDate m_date;
};

#endif // NEWSLETTER_H
