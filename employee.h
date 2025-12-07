#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class Employee{
public:
    Employee(const QString &name = "",
        const QString &surname = "",
        const QString &position = "Employee",
        const QDate &employmentDate = QDate::currentDate())
        : m_name(name), m_surname(surname), m_position(position), m_employmentDate(employmentDate) {}

    static Employee fromJson(const QJsonObject &obj) {
        return Employee(
            obj["name"].toString(),
            obj["surname"].toString(),
            obj["position_id"].toString(), //TMP, need to make combined request
            QDate::fromString(obj["employment_date"].toString(), Qt::ISODate)
            );
    }


    QString name() const {return m_name; }
    QString surname() const {return m_surname; }
    QString position() const {return m_position; }
    QDate employmentDate() const {return m_employmentDate; }

    void setName(const QString &name) {m_name = name; }
    void setSurname(const QString &surname) {m_surname = surname; }
    void setPosition(const QString &position) {m_position = position; }
    void setEmploymentDate(const QDate &employmentDate) {m_employmentDate = employmentDate; }

private:
    QString m_name;
    QString m_surname;
    QString m_position;
    QDate m_employmentDate;
};

#endif // EMPLOYEE_H
