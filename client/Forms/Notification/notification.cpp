#include "notification.h"
#include "ui_notification.h"
#include "StyleManager/stylemanager.h"

Notification::Notification(QWidget *parent, QString notification, QString colour)
    : QWidget(parent)
    , ui(new Ui::Notification)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setLabelStyle(ui->notificationLabel, notification, true, colour, true, 16);

    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: 2px solid lightgrey;"
        "}");
    QPropertyAnimation* animation = new QPropertyAnimation(ui->progressBar, "value");
    animation->setStartValue(100);
    animation->setEndValue(0);
    animation->setDuration(5000);
    animation->start();
    connect(animation, &QPropertyAnimation::finished, this, &Notification::closeNotification);

    this->move(StyleManager::GetInstance()->getScreenWidth() - 290, 100);
}

void Notification::closeNotification()
{
    this->close();
}

Notification::~Notification()
{
    delete ui;
}
