#ifndef STAT_H
#define STAT_H
#include <QDate>
#include <QTime>

class Stat{
public:
    Stat(const QDate &date = QDate::currentDate(),
         const QTime &workTime = QTime::currentTime(),
         const int clockCount = 0)
        : m_date(date), m_workTime(workTime), m_clockCount(clockCount) {}

    QDate date() const {return m_date; }
    QTime workTime() const {return m_workTime; }
    int clockCount() const {return m_clockCount;}

    void setDate(const QDate &date){ m_date = date;}
    void setWorkTime(const QTime &workTime) {m_workTime = workTime;}
    void setClockCount(const int &clockCount) {m_clockCount = clockCount;}
private:
    QDate m_date;
    QTime m_workTime;
    int m_clockCount;
};

#endif // STAT_H
