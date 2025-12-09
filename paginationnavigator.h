#ifndef PAGINATIONNAVIGATOR_H
#define PAGINATIONNAVIGATOR_H
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
class PaginationNavigator : public QWidget
{
    Q_OBJECT
public:
    PaginationNavigator(QWidget *parent = nullptr,
                        const int &page = 1,
                        const int &pageSize = 10,
                        const int &totalEntities = 0);

    void setPage(const int &page) {m_page = page; updateNavigation();}
    void setPageSize(const int &pageSize) {m_pageSize = pageSize; updateNavigation();}
    void setTotalEntities(const int &totalEntities) {m_totalEntities = totalEntities; updateNavigation();}

    int page() const {return m_page;}
    int pageSize() const {return m_pageSize;}
    int totalEntities() const {return m_totalEntities;}

    void updateNavigation();
private:
    void navigationClicked(int page);
    QHBoxLayout *navigator;

    QPushButton *backButton;
    QLabel *pageDisplay;
    QPushButton *nextButton;
    int m_page;
    int m_pageSize;
    int m_totalEntities;
signals:
    void pageChanged(int page);
};

#endif // PAGINATIONNAVIGATOR_H
