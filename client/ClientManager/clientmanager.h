#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QSslSocket>
#include<QJsonObject>
#include "../common/transferEnum/transferEnum.h"

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
    static ClientManager* s_Instance;

private slots:

    void slotReadyRead();
    void ServerOrClientError();
    void SendToServer(QJsonObject json);
    void sslErrorOccured( QList<QSslError> list);
    void tryReconnected();

public:
    static ClientManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new ClientManager()); }
    void Send(TransferEnum e, QJsonObject json);
signals:
    void Readed(QJsonObject);
};

#endif // CLIENTMANAGER_H
