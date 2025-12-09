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

    void fetchNewsletters(int page=1, int pagesize=10);
    void editNews(const Newsletter &employee);
    void deleteNews(const int id);
signals:
    void newslettersReady(const QList<Newsletter>& list, const int totalCount);
    void newsEdited(const int status);
    void newsDeleted(const int status);
private:
    QNetworkAccessManager *manager;
};

#endif // NEWSSERVICE_H
