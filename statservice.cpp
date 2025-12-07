#include "statservice.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
StatService::StatService(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished,
            this, &StatService::onStatsReply);
}

void StatService::fetchStats() {
    QUrl url(STAT_API + "s");
    QNetworkRequest request(url);
    manager->get(request);
}

void StatService::onStatsReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    QList<Stat> list;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray arr = root["items"].toArray();

    for (const QJsonValue &v : arr) {
        list.append(Stat::fromJson(v.toObject()));
    }

    emit statsReady(list);
    reply->deleteLater();
}
