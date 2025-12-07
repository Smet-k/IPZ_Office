#ifndef NEWSSERVICE_H
#define NEWSSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include "newsletter.h"
#define NEWS_API QStringLiteral("http://localhost:8080/api/newsletter")
class NewsService : public QObject
{
    Q_OBJECT

public:
    explicit NewsService(QObject * parent = nullptr);

    void fetchNewsletters();

signals:
    void newslettersReady(const QList<Newsletter>& list);

private slots:
    void onNewsReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

#endif // NEWSSERVICE_H
