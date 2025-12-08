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

void EmployeeService::editEmployee(const Employee &employee){
    QUrl url(EMPLOYEE_API);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject body;
    if(employee.id() > 0)
        body["id"] = employee.id();
    body["login"] = employee.login();
    body["name"] = employee.name();
    body["surname"] = employee.surname();
    body["employment_date"]  = employee.employmentDate().toString("yyyy-MM-dd");
    body["position_id"] = 1; // tmp
    body["role_id"] = 1; // tmp
    body["password"] = employee.password();

    QJsonDocument doc(body);
    QByteArray json = doc.toJson();
    QNetworkReply *reply;
    if(employee.id() > 0)
        reply = manager->put(request,json);
    else
        reply = manager->post(request,json);

    connect(reply, &QNetworkReply::finished, this, [this, reply,employee]() {
        if (reply->error() != QNetworkReply::NoError){
            emit employeeEdited(0);
            return;
        }
        emit employeeEdited(employee.id() > 0 ? 2 : 1); // use it for success messages

        reply->deleteLater();
    });
}
