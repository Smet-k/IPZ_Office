#include "logoutmodal.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
LogoutModal::LogoutModal(QWidget *parent)
    : QDialog(parent) {
    this->setFixedSize(225, 100);
    setWindowTitle("Logout");
    setModal(true);

    QVBoxLayout *logoutLayout = new QVBoxLayout(this);
    logoutLayout->setSpacing(15);

    QFont font = QFont("Noto Sans", 14);
    logoutLayout->addWidget(new QLabel("Are you sure you want to Logout?"));

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *confirmBtn = new QPushButton("Proceed");
    QPushButton *cancelBtn = new QPushButton("Cancel");

    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addWidget(confirmBtn);

    connect(confirmBtn, &QPushButton::clicked, this, &LogoutModal::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &LogoutModal::reject);

    logoutLayout->addLayout(buttonsLayout);
}
