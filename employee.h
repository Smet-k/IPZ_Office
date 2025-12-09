#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class Employee{
public:
    Employee(const QString &name = "",
             const QString &login = "",
             const QString &surname = "",
             const QString &position = "Employee",
             const int &positionId = 0,
             const QDate &employmentDate = QDate::currentDate(),
             const QString &password = "",
             const int &role = 1)
        : m_login(login), m_name(name), m_surname(surname), m_position(position), m_positionId(positionId), m_employmentDate(employmentDate), m_password(password), m_role(role) {}

    Employee(const int &id,
             const QString &login = "",
             const QString &name = "",
             const QString &surname = "",
             const QString &position = "Employee",
             const int &positionId = 0,
             const QDate &employmentDate = QDate::currentDate(),
             const QString &password = "",
             const int &role = 1)
        : m_id(id), m_login(login), m_name(name), m_surname(surname), m_position(position), m_positionId(positionId), m_employmentDate(employmentDate), m_password(password), m_role(role) {}

    static Employee fromJson(const QJsonObject &obj) {
        return Employee(
            obj["id"].toInt(),
            obj["login"].toString(),
            obj["name"].toString(),
            obj["surname"].toString(),
            obj["position"].toString(),
            obj["position_id"].toInt(),
            QDate::fromString(obj["employment_date"].toString(), Qt::ISODate),
            obj["password"].toString(),
            obj["role_id"].toInt()
            );
    }


    int id() const {return m_id; }
    QString login() const {return m_login; }
    QString name() const {return m_name; }
    QString surname() const {return m_surname; }
    int positionId() const {return m_positionId; }
    QString position() const {return m_position; }
    QDate employmentDate() const {return m_employmentDate; }
    QString password() const {return m_password; }
    int role() const {return m_role; }

    void setId(const int &id) {m_id = id; }
    void setLogin(const QString &login) {m_login = login; }
    void setName(const QString &name) {m_name = name; }
    void setSurname(const QString &surname) {m_surname = surname; }
    void setPosition(const QString &position) {m_position = position; }
    void setPositionId(const int &id) {m_positionId = id;}
    void setEmploymentDate(const QDate &employmentDate) {m_employmentDate = employmentDate; }
    void setPassword(const QString &password) {m_password = password;}
private:
    int m_id;
    QString m_login;
    QString m_name;
    QString m_surname;
    int m_positionId;
    QString m_position;
    QDate m_employmentDate;
    QString m_password;
    int m_role;
};

#endif // EMPLOYEE_H
