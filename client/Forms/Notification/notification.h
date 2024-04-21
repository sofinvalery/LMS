#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class Notification;
}

class Notification : public QWidget
{
    Q_OBJECT

public:
    explicit Notification(QWidget *parent = nullptr, QString notification = "Vam ban", QString colour = "red");
    ~Notification();
private slots:
    void closeNotification();
private:
    Ui::Notification *ui;
};

#endif // NOTIFICATION_H
