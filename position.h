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

    static Position fromJson(const QJsonObject &obj) {
        return Position(
            obj["title"].toString(),
            obj["salary"].toInt()
            );
    }


    QString title() const {return m_title; }
    int salary() const {return m_salary; }

    void setTitle(const QString &title) {m_title = title; }
    void setSurname(const int &salary) {m_salary = salary; }


private:
    QString m_title;
    int m_salary;
};

#endif // POSITION_H
