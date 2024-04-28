#include "notification.h"
#include "ui_notification.h"
#include "StyleManager/stylemanager.h"

Notification::Notification(QWidget *parent, QString notification, QString colour)
    : QWidget(parent)
    , ui(new Ui::Notification)
{
    ui->setupUi(this);
    //startEnterAnimation();
    this->move(StyleManager::GetInstance()->getScreenWidth() - 290, 100); //StyleManager::GetInstance()->getScreenWidth() - 290
    StyleManager::GetInstance()->setLabelStyle(ui->notificationLabel, notification, true, colour, true, 16);

    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: 2px solid lightgrey;"
        "}");
    QTimer* timer = new QTimer(this);
    timer->setInterval(5000);
    timer->start();
    connect(timer, &QTimer::timeout, this, &Notification::startExitAnimation);
}

void Notification::startExitAnimation()
{
    QPropertyAnimation* moveLeftAnimation = new QPropertyAnimation(this, "geometry");
    moveLeftAnimation->setStartValue(geometry());
    moveLeftAnimation->setEndValue(QRect(x() - 30, y(), width(), height()));
    moveLeftAnimation->setDuration(300);

    QPropertyAnimation* moveOutAnimation = new QPropertyAnimation(this, "geometry");
    moveOutAnimation->setStartValue(geometry());
    moveOutAnimation->setEndValue(QRect(StyleManager::GetInstance()->getScreenWidth(), y(), width(), height()));
    moveOutAnimation->setDuration(300);

    connect(moveLeftAnimation, &QPropertyAnimation::finished, [moveOutAnimation]() {
        moveOutAnimation->start();
    });
    connect(moveOutAnimation, &QPropertyAnimation::finished, this, &QWidget::close);
    moveLeftAnimation->start();
}

void Notification::startEnterAnimation()
{
    // this->move(StyleManager::GetInstance()->getScreenWidth(), 100); //StyleManager::GetInstance()->getScreenWidth() - 290
    // QPropertyAnimation* moveLeftAnimation = new QPropertyAnimation(this, "geometry");
    // moveLeftAnimation->setStartValue(geometry());
    // moveLeftAnimation->setEndValue(QRect(x() - 320, y(), width(), height()));
    // moveLeftAnimation->setDuration(300);

    // QPropertyAnimation* moveRightAnimation = new QPropertyAnimation(this, "geometry");
    // moveRightAnimation->setStartValue(geometry());
    // moveRightAnimation->setEndValue(QRect(x() + 30, y(), width(), height()));
    // moveRightAnimation->setDuration(300);

    // connect(moveLeftAnimation, &QPropertyAnimation::finished, [moveRightAnimation]() {
    //     moveRightAnimation->start();
    // });
    // moveLeftAnimation->start();
}

Notification::~Notification()
{
    delete ui;
}
