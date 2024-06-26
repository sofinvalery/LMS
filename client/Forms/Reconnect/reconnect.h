#ifndef RECONNECT_H
#define RECONNECT_H

#include <QDialog>
#include <QSslSocket>
#include "../../../common/transferEnum/transferEnum.h"
#include "ClientManager/clientmanager.h"
#include <QMovie>

namespace Ui {
class Reconnect;
}

class Reconnect : public QDialog
{
    Q_OBJECT

public:
    explicit Reconnect(QWidget *parent = nullptr);
    ~Reconnect();

private slots:
    void on_exitButton_clicked();
    void on_reconnectButton_clicked();
    void reconnectGood();
    void reconnectEr(QAbstractSocket::SocketError socketError);
private:
    QMovie *movie = new QMovie(":/gif/resources/reconnect.gif");
    Ui::Reconnect *ui;
signals:
    void re();
};

#endif // RECONNECT_H
