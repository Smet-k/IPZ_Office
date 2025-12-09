#ifndef STATSERVICE_H
#define STATSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include "stat.h"

#define STAT_API QStringLiteral("http://localhost:8080/api/stat")

class StatService : public QObject
{
    Q_OBJECT
public:
    explicit StatService(QObject *parent = nullptr);

    void fetchEmployeeStats(const int employee_id);
    void editStat(const Stat &stat, int authorizedEmployee);
signals:
    void statEdited(const int status);
    void onEmployeeStatsReply(const QList<Stat>& list);

private:

    QNetworkAccessManager *manager;
};


#endif // STATSERVICE_H
