#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QTimer>
namespace Ui {
class Notification;
}

class Notification : public QDialog
{
    Q_OBJECT

public:
    explicit Notification(QWidget *parent = nullptr, QString notification = "Vam ban", QString colour = "red");
    ~Notification();
private:
    Ui::Notification *ui;
    void startExitAnimation();
    void startEnterAnimation();
    QTimer* timer = new QTimer(this);
};

#endif // NOTIFICATION_H
