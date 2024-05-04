#include "notification.h"
#include "ui_notification.h"
#include "StyleManager/stylemanager.h"

Notification::Notification(QWidget *parent, QString notification, QString colour)
    : QDialog(parent)
    , ui(new Ui::Notification)
{
    ui->setupUi(this);
    startEnterAnimation();
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    StyleManager::GetInstance()->setLabelStyle(ui->notificationLabel, notification, true, colour, true, 14);

    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: 2px solid lightgrey;"
        "}");
    timer->setInterval(4600);
    timer->start();
    connect(timer, &QTimer::timeout, this, &Notification::startExitAnimation);
}

void Notification::startExitAnimation()
{
    QPropertyAnimation* moveLeftAnimation = new QPropertyAnimation(this, "geometry");
    moveLeftAnimation->setStartValue(geometry());
    moveLeftAnimation->setEndValue(QRect(x() - 30, y(), width(), height()));
    moveLeftAnimation->setDuration(200);

    QPropertyAnimation* moveOutAnimation = new QPropertyAnimation(this, "geometry");
    moveOutAnimation->setStartValue(geometry());
    moveOutAnimation->setEndValue(QRect(StyleManager::GetInstance()->getScreenWidth(), y(), width(), height()));
    moveOutAnimation->setDuration(200);

    connect(moveLeftAnimation, &QPropertyAnimation::finished, [moveOutAnimation]() {
        moveOutAnimation->start();
    });
    connect(moveOutAnimation, &QPropertyAnimation::finished, this, [this]() {this->close(); this->deleteLater();});
    moveLeftAnimation->start();
}

void Notification::startEnterAnimation()
{
    this->move(StyleManager::GetInstance()->getScreenWidth(), 100);
    QPropertyAnimation* moveLeftAnimation = new QPropertyAnimation(this, "geometry");
    moveLeftAnimation->setStartValue(geometry());
    moveLeftAnimation->setEndValue(QRect(x() - 320, y(), width(), height()));
    moveLeftAnimation->setDuration(200);
    moveLeftAnimation->start();
}

Notification::~Notification()
{
    delete ui;
}
