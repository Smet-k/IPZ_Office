#ifndef STAT_H
#define STAT_H
#include <QDate>
#include <QTime>
#include <QJsonObject>
class Stat{
public:
    Stat(const int &id = 0,
         const QDate &date = QDate::currentDate(),
         const QTime &workTime = QTime::currentTime(),
         const int &clockCount = 0,
         const int &employeeId = 0)
        : m_id(id), m_date(date), m_workTime(workTime), m_clockCount(clockCount), m_employeeId(employeeId) {}

    static Stat fromJson(const QJsonObject &obj) {
        return Stat(
            obj["id"].toInt(),
            QDate::fromString(obj["date"].toString(), Qt::ISODate),
            QTime::fromString(obj["time"].toString()),
            obj["clock_amount"].toInt(),
            obj["employee_id"].toInt()
            );
    }

    int id() const {return m_id; };
    QDate date() const {return m_date; }
    QTime workTime() const {return m_workTime; }
    int clockCount() const {return m_clockCount;}
    int employeeId() const {return m_employeeId;}

    void setId(const int &id) { m_id = id;}
    void setDate(const QDate &date){ m_date = date;}
    void setWorkTime(const QTime &workTime) {m_workTime = workTime;}
    void setClockCount(const int &clockCount) {m_clockCount = clockCount;}
    void setEmployeeId(const int &employeeId) {m_employeeId = employeeId;}
private:
    int m_id;
    QDate m_date;
    QTime m_workTime;
    int m_clockCount;
    int m_employeeId;
};

#endif // STAT_H
