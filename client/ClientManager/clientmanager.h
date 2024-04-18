#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QSslSocket>
#include<QJsonObject>
#include "../common/transferEnum/transferEnum.h"
#include <QFile>

struct fileSocket{
    bool isReady;
    QSslSocket *socket;
    QByteArray Data;
    qint64 titleSize=0;
    qint64 fileSize=0;
    qint64 alreadyRead=0;
    QFile* file=nullptr;
};

class ClientManager : public QObject
{
    Q_OBJECT
private:
    explicit ClientManager(QObject *parent = nullptr);

    QSslSocket *socket;
    QByteArray Data;
    quint64 nextBlockSize=0;
    QString hostName;
    quint16 port;
    QList<fileSocket*> fileSockets;
    static ClientManager* s_Instance;
    QList<QString> downloadPath;

private slots:

    void slotReadyReadJson();
    void slotReadyReadFile();
    void ServerOrClientError();
    void SendToServerJson(QJsonObject json);
    fileSocket* GetFileSocket();
    void sslErrorOccured( QList<QSslError> list);
    void tryReconnected();

public:
    static ClientManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new ClientManager()); }
    void SendJson(TransferEnum e, QJsonObject json);
    void SendRequestFile(QString path);
    void SendFile(QString path);
signals:
    void Readed(QJsonObject);
};

#endif // CLIENTMANAGER_H
