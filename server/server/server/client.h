#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include<QTcpSocket>
#include<QJsonObject>
#include<QtConcurrent>
#include "servertask.h"
#include "../../common/authentication/authentication.h"

class Client: public QObject
{
    Q_OBJECT

public:

    Client(qintptr socketDescriptor, QObject* parent = 0);

public slots:
    void readyRead();
    void disconnected();
    void SendToClient(QJsonObject);



private:
    Authentication* auth=nullptr;
    QTcpSocket* m_client;
};

#endif // CLIENT_H
