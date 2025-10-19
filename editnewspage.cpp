#include "editnewspage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

EditNewsPage::EditNewsPage() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    newsTitleField = new QLineEdit();
    newsTitleField->setPlaceholderText("News Title");
    newsBodyField = new QLineEdit();
    newsBodyField->setPlaceholderText("News Body");
    newsBodyField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    newsBodyField->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    newsDateField = new QDateEdit();

    QHBoxLayout *headerLayout = new QHBoxLayout();
    QVBoxLayout *titleLayout = new QVBoxLayout();
    QVBoxLayout *dateLayout = new QVBoxLayout();

    dateLayout->addWidget(new QLabel("Date:"));
    dateLayout->addWidget(newsDateField);

    titleLayout->addWidget(new QLabel("Title:"));
    titleLayout->addWidget(newsTitleField);

    headerLayout->addLayout(titleLayout);
    headerLayout->addLayout(dateLayout);

    mainLayout->addLayout(headerLayout, 1);

    QVBoxLayout *bodyLayout = new QVBoxLayout();
    bodyLayout->setSpacing(0);
    bodyLayout->addWidget(new QLabel("Body:"), 1);
    bodyLayout->addWidget(newsBodyField, 10);

    mainLayout->addLayout(bodyLayout , 8);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *deleteBtn = new QPushButton("Delete");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    QPushButton *submitBtn = new QPushButton("Submit");

    buttonsLayout->addWidget(deleteBtn);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addWidget(submitBtn);

    mainLayout->addLayout(buttonsLayout, 1);
}

void EditNewsPage::updatePage(){
    newsTitleField->setText(m_news.title());
    newsBodyField->setText(m_news.body());
    newsDateField->setDate(m_news.date());
}

void EditNewsPage::clearPage(){
    newsTitleField->clear();
    newsBodyField->clear();
    newsDateField->setDate(newsDateField->minimumDate());

    m_news = Newsletter();
}
