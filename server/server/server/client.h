#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include<QSslSocket>
#include<QJsonObject>
#include<QtConcurrent>
#include "servertask.h"
#include "../../common/authentication/authentication.h"

class Client: public QObject
{
    Q_OBJECT

public:

    Client(qintptr socketDescriptor, QObject* parent = 0);

private slots:
    void readyRead();
    void disconnected();
    void SendToClient(QJsonObject);
    void sslErrorOccured(QList<QSslError> list);

private:
    Authentication* auth=nullptr;
    QSslSocket* m_client;
};

#endif // CLIENT_H
