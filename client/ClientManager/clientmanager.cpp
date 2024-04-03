#include "clientmanager.h"
#include <QSslConfiguration>


ClientManager* ClientManager::s_Instance = nullptr;


ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    socket = new QSslSocket(this);
    const QString serverKeyPath(":/sll/ClientManager/certificate/client.key");
    socket->setPrivateKey(serverKeyPath,QSsl::Rsa);
    connect(socket,&QTcpSocket::readyRead, this,&ClientManager::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected, this,&ClientManager::ServerOrClientError);
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrorOccured(QList<QSslError> )));
    port=1234;
    hostName="127.0.0.1";
    socket->connectToHostEncrypted(hostName,port);
    if (!socket->waitForEncrypted(1000000)) {
        qInfo() << socket->errorString();
        throw ("ошибка подключения");
    }
    qInfo() << "connection to server";

}

void ClientManager::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status()==QDataStream::Ok){

        for(;;){
            if(nextBlockSize==0){
                if(socket->bytesAvailable()<sizeof(quint64))
                {
                    break;
                }
                in>>nextBlockSize;
            }
            if(socket->bytesAvailable()<nextBlockSize)
            {
                break;
            }
            QJsonObject json;
            in >> json;
            nextBlockSize=0;
            emit Readed(json);


            break;
        }

    }
    else
    {
        ServerOrClientError();
    }





}
//вывести как нибудь что все пошло не туда...
void ClientManager::ServerOrClientError()
{
   QT_THROW("Проверь интернет кабель...");
}

void ClientManager::SendToServer(QJsonObject json)
{
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<quint64(0)<<json;
    out.device()->seek(0);
    out<<quint64(Data.size()-sizeof(quint64));
    socket->write(Data);
}

void ClientManager::sslErrorOccured( QList<QSslError> list )
{
        for (const QSslError &error : list) {
            qInfo() << "SSL error:" << error.errorString();
        }
        socket->ignoreSslErrors(list);
}

void ClientManager::Send(TransferEnum e, QJsonObject json)
{
    QJsonObject sendJson;
    sendJson["Action"]=e;
    sendJson["Data"]=json;
    SendToServer(sendJson);
}
