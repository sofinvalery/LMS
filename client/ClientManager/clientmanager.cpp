#include "clientmanager.h"



ClientManager* ClientManager::s_Instance = nullptr;


ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead, this,&ClientManager::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected, this,&ClientManager::ServerOrClientError);
    port=1234;
    hostName="127.0.0.1";
    socket->connectToHost(hostName,port);
}

void ClientManager::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status()==QDataStream::Ok){

        for(;;){
            if(nextBlockSize==0){
                if(socket->bytesAvailable()<2)
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
    out<<quint16(0)<<json;
    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    socket->write(Data);
}

void ClientManager::Send(TransferEnum e, QJsonObject json)
{
    QJsonObject sendJson;
    sendJson["Action"]=e;
    sendJson["Data"]=json;
    SendToServer(sendJson);
}
