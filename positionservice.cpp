#include "positionservice.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
PositionService::PositionService(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{

}

void PositionService::fetchPositions() {
    QUrl url(POSITION_API + "s");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]{
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
    });
}

