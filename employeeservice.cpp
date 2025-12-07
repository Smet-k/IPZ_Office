#include "employeeservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

EmployeeService::EmployeeService(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished,
            this, &EmployeeService::onEmployeeReply);
}

void EmployeeService::fetchEmployees() {
    QUrl url(EMPLOYEE_API + "s");
    QNetworkRequest request(url);
    manager->get(request);
}

void EmployeeService::onEmployeeReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    QList<Employee> list;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray arr = root["items"].toArray();

    for (const QJsonValue &v : arr) {
        list.append(Employee::fromJson(v.toObject()));
    }

    emit employeesReady(list);
    reply->deleteLater();
}
