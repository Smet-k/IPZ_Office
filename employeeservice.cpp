#include "employeeservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

EmployeeService::EmployeeService(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{}

void EmployeeService::fetchEmployees(int page, int pagesize) {
    QUrl url(QString("%1s_view?page=%2&page_size=%3")
                 .arg(QString(EMPLOYEE_API))
                 .arg(QString::number(page))
                 .arg(QString::number(pagesize)));
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
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
        int totalCount = root["total_count"].toInt();
        for (const QJsonValue &v : arr) {
            list.append(Employee::fromJson(v.toObject()));
        }

        emit employeesReady(list, totalCount);
        reply->deleteLater();
    });
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
    body["position_id"] = employee.positionId();
    body["role_id"] = employee.role();
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

void EmployeeService::authEmployee(const QString login, const QString password){
    QUrl url(EMPLOYEE_API + "/auth");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject body;

    body["login"] = login;
    body["password"] = password;

    QJsonDocument doc(body);
    QByteArray json = doc.toJson();
    QNetworkReply *reply = manager->post(request,json);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError){;
            return;
        }
        QByteArray data = reply->readAll();


        QJsonDocument doc = QJsonDocument::fromJson(data);
        Employee emp = Employee::fromJson(doc.object());

        emit employeeAuthorized(emp);
        reply->deleteLater();
    });
}
