#include "statservice.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <stdio.h>
StatService::StatService(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{

}

void StatService::fetchEmployeeStats(const int employee_id){
    QUrl url(STAT_API + "s/" + QString::number(employee_id));
    QNetworkRequest request(url);

    QNetworkReply *reply;
    reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        if (reply->error() != QNetworkReply::NoError){
            reply->deleteLater();
            return;
        }

        QByteArray responseData = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject root = doc.object();
        int count = root["total_count"].toInt();

        if(count > 0){
            QList<Stat> list;
            QJsonArray arr = root["items"].toArray();

            for (const QJsonValue &v : arr) {
                list.append(Stat::fromJson(v.toObject()));
            }

            emit onEmployeeStatsReply(list);
            reply->deleteLater();
        }
    } );


}

void StatService::editStat(const Stat &stat, int authorizedEmployee){
    QUrl url(STAT_API);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject body;
    if(stat.id() > 0)
        body["id"] = stat.id();
    body["date"] = stat.date().toString(Qt::ISODate);
    body["time"] = stat.workTime().toString("HH:mm:ss");
    body["clock_amount"] = stat.clockCount();
    body["employee_id"]  = authorizedEmployee;


    QJsonDocument doc(body);
    QByteArray json = doc.toJson();
    QNetworkReply *reply;
    if(stat.id() > 0)
        reply = manager->put(request,json);
    else
        reply = manager->post(request,json);

    connect(reply, &QNetworkReply::finished, this, [this, reply,stat]() {
        if (reply->error() != QNetworkReply::NoError){
            emit statEdited(0);
            return;
        }
        emit statEdited(stat.id() > 0 ? 2 : 1); // use it for success messages

        reply->deleteLater();
    });
}
