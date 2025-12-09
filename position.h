#ifndef POSITION_H
#define POSITION_H

#include <QString>
#include <QDate>
#include <QJsonObject>
class Position{
public:
    Position(const QString &title = "",
             const int &salary = 0)
        : m_title(title), m_salary(salary) {}

    Position(const int &id = 0,
             const QString &title = "",
             const int &salary = 0)
        : m_id(id), m_title(title), m_salary(salary) {}

    static Position fromJson(const QJsonObject &obj) {
        return Position(
            obj["id"].toInt(),
            obj["title"].toString(),
            obj["salary"].toInt()
            );
    }


    int id() const {return m_id; }
    QString title() const {return m_title; }
    int salary() const {return m_salary; }

    void setId(const int &id) {m_id = id;}
    void setTitle(const QString &title) {m_title = title; }
    void setSurname(const int &salary) {m_salary = salary; }


private:
    int m_id;
    QString m_title;
    int m_salary;
};

#endif // POSITION_H
