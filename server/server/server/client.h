#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include<QSslSocket>
#include<QJsonObject>
#include<QtConcurrent>
#include "servertask.h"
#include "../../common/authentication/authentication.h"


struct FileParams{
    QFile* sendFile=nullptr;
    QDataStream* read=nullptr;
    QFileInfo* fileInfo=nullptr;
    char DataFile[2048];
    int sizeFile=0;
    int SendFileSize=0;
};

struct FileSocket{
    QByteArray Data;
    qint64 titleSize=0;
    qint64 fileSize=0;
    qint64 alreadyRead=0;
    QFile* file=nullptr;
    FileParams fileParams;
};

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
    void ReadFileData();

private:
    quint64 nextBlockSize=0;
    quint32 typeMessage=0;
    Authentication** auth;
    QSslSocket* m_client;
    FileParams fileParams;
    FileSocket fileSocket;
signals:
    void ReadFileDataToClient();
    void SendFileDataToClient();
};

#endif // CLIENT_H
