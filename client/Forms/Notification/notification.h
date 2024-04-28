#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QTimer>
namespace Ui {
class Notification;
}

class Notification : public QWidget
{
    Q_OBJECT

public:
    explicit Notification(QWidget *parent = nullptr, QString notification = "Vam ban", QString colour = "red");
    ~Notification();
private:
    Ui::Notification *ui;
    void startExitAnimation();
    void startEnterAnimation();
};

#endif // NOTIFICATION_H
