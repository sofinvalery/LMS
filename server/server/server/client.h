#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include<QTcpSocket>
#include<QJsonObject>
#include<QtConcurrent>
#include"../jsonManager/jsonmaneger.h"
#include<../../common/authentication/authentication.h>

class Client: public QObject
{
    Q_OBJECT

public:

    void SendToClient(QJsonObject);

    Client(qintptr socketDescriptor, QObject* parent = 0);

public slots:
    void readyRead();
    void disconnected();




private:
    Authentication* auth=nullptr;
    QTcpSocket* m_client;
};

#endif // CLIENT_H
