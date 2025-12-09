#include "newsservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
NewsService::NewsService(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{}

void NewsService::fetchNewsletters(int page, int pagesize) {
    QUrl url(QString("%1s?page=%2&page_size=%3")
                 .arg(QString(NEWS_API))
                 .arg(QString::number(page))
                 .arg(QString::number(pagesize)));

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);


    connect(reply, &QNetworkReply::finished, this, [this, reply](){
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
        const int totalCount = root["total_count"].toInt();

        for (const QJsonValue &v : arr) {
            list.append(Newsletter::fromJson(v.toObject()));
        }

        emit newslettersReady(list, totalCount);
        reply->deleteLater();
    });
}

void NewsService::deleteNews(const int id) {
    QUrl url(QString("%1/%2")
                 .arg(QString(NEWS_API))
                 .arg(QString::number(id)));

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->deleteResource(request);


    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Request error:" << reply->errorString();
            reply->deleteLater();
            emit newsDeleted(0);
            return;
        }

        emit newsDeleted(1);
    });
}

void NewsService::editNews(const Newsletter &news){
    QUrl url(NEWS_API);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject body;
    if(news.id() > 0)
        body["id"] = news.id();
    body["title"] = news.title();
    body["body"] = news.body();
    body["date"] = news.date().toString(Qt::ISODate);


    QJsonDocument doc(body);
    QByteArray json = doc.toJson();
    QNetworkReply *reply;
    if(news.id() > 0)
        reply = manager->put(request,json);
    else
        reply = manager->post(request,json);

    connect(reply, &QNetworkReply::finished, this, [this, reply,news]() {
        if (reply->error() != QNetworkReply::NoError){
            emit newsEdited(0);
            return;
        }
        emit newsEdited(news.id() > 0 ? 2 : 1);

        reply->deleteLater();
    });
}
