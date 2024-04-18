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
    void SendFile(QString path);
    void SendFileData();

private:
    quint64 nextBlockSize=0;
    quint32 typeMessage=0;
    Authentication** auth;
    QSslSocket* m_client;
    int sizeFile=0;
    int alreadySendFile=0;
    char DataFile[1024];
signals:
    void FileData();
};

#endif // CLIENT_H
