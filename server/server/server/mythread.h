#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include<QJsonObject>
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = 0);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();
    void SendToClient(QJsonObject);
private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    quint16 nextBlockSize=0;
    QByteArray Data;
};

#endif // MYTHREAD_H
