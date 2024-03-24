#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include<QJsonObject>
#include "../common/transferEnum/transferEnum.h"

class ClientManager : public QObject
{
    Q_OBJECT
private:
    explicit ClientManager(QObject *parent = nullptr);

    QTcpSocket *socket;
    QByteArray Data;
    quint16 nextBlockSize=0;
    QString hostName;
    quint16 port;
    static ClientManager* s_Instance;

private slots:

    void slotReadyRead();
    void ServerOrClientError();
    void SendToServer(QJsonObject json);

public:
    static ClientManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new ClientManager()); }
    void Send(TransferEnum e, QJsonObject json);
signals:
    //если нужен будет другой тип возвращаемого значения поменяем
    void Readed(QJsonObject);
    //для подключения:
   // connect(ClientManager::GetInstance(),SIGNAL(Readed(QJsonObject)),this,SLOT(P(QJsonObject)));
    //otkl
    //QObject::disconnect(const QObject *receiver, const char *method = nullptr)
};

#endif // CLIENTMANAGER_H
