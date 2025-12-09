#ifndef POSITIONSERVICE_H
#define POSITIONSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include "position.h"
#define POSITION_API QStringLiteral("http://localhost:8080/api/position")
class PositionService : public QObject
{
    Q_OBJECT
public:
    explicit PositionService(QObject *parent = nullptr);

    void fetchPositions();
signals:
    void positionsReady(const QList<Position>& list);

private:
    QNetworkAccessManager *manager;
};

#endif // POSITIONSERVICE_H
