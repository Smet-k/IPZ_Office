#include "newsservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
NewsService::NewsService(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished,
            this, &NewsService::onNewsReply);
}

void NewsService::fetchNewsletters() {
    QUrl url(NEWS_API + "s");
    QNetworkRequest request(url);
    manager->get(request);
}

void NewsService::onNewsReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    QList<Newsletter> list;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray arr = root["items"].toArray();

    for (const QJsonValue &v : arr) {
        list.append(Newsletter::fromJson(v.toObject()));
    }

    emit newslettersReady(list);
    reply->deleteLater();
}
