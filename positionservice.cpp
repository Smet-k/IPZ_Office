#include "positionservice.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
PositionService::PositionService(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished,
            this, &PositionService::onPositionsReply);
}

void PositionService::fetchPositions() {
    QUrl url(POSITION_API + "s");
    QNetworkRequest request(url);
    manager->get(request);
}

void PositionService::onPositionsReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    QList<Position> list;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray arr = root["items"].toArray();

    for (const QJsonValue &v : arr) {
        list.append(Position::fromJson(v.toObject()));
    }

    emit positionsReady(list);
    reply->deleteLater();
}
