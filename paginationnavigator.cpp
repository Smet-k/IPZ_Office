#include "paginationnavigator.h"
#include <QPushButton>
#include <QLabel>
#include <QString>

void PaginationNavigator::updateNavigation(){
    pageDisplay->setText(QString::number(m_page));

    if(m_totalEntities < m_pageSize){
        backButton->setEnabled(false);

        nextButton->setEnabled(false);
    }
    else if (m_page == 1){
        backButton->setEnabled(false);

        nextButton->setEnabled(true);
    }
    else if (m_totalEntities < m_page * m_pageSize){
        backButton->setEnabled(true);

        nextButton->setEnabled(false);
    }
    if (m_totalEntities < m_pageSize){
        nextButton->setEnabled(false);
    }
}

PaginationNavigator::PaginationNavigator(QWidget *parent, const int &page, const int &pageSize, const int &totalEntities) :
    QWidget(parent),
    m_page(page),
    m_pageSize(pageSize),
    m_totalEntities(totalEntities) {
    navigator = new QHBoxLayout(this);

    backButton = new QPushButton("<");
    pageDisplay = new QLabel(QString::number(m_page));
    nextButton = new QPushButton(">");

    navigator->addWidget(backButton);
    navigator->addWidget(pageDisplay);
    navigator->addWidget(nextButton);

    connect(backButton, &QPushButton::clicked, this, [this]{
        navigationClicked(m_page-1);
    });

    connect(nextButton, &QPushButton::clicked, this, [this]{
        navigationClicked(m_page+1);
    });
}

void PaginationNavigator::navigationClicked(int page){
    if (page == 0 || (page - 1) > m_totalEntities / m_pageSize) return;
    backButton->setEnabled(false);
    nextButton->setEnabled(false);

    m_page = page;

    emit pageChanged(page);

    updateNavigation();
}


