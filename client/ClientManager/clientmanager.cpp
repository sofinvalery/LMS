#include "clientmanager.h"
#include <QSslConfiguration>
#include "Forms/Reconnect/reconnect.h"
#include <QStandardPaths>
#include <QDir>

ClientManager* ClientManager::s_Instance = nullptr;


ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    socket = new QSslSocket(this);
    const QString serverKeyPath(":/sll/ClientManager/certificate/client.key");
    socket->setPrivateKey(serverKeyPath,QSsl::Rsa);
    connect(socket,&QTcpSocket::readyRead, this,&ClientManager::slotReadyReadJson);
    connect(socket,&QTcpSocket::disconnected, this,&ClientManager::ServerOrClientError);
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrorOccured(QList<QSslError> )));
    port=1234;
    hostName="127.0.0.1";
    socket->connectToHostEncrypted(hostName,port);
    if (!socket->waitForEncrypted(10000)) {
        qInfo() << socket->errorString();
        ServerOrClientError();
    }
    qInfo() << "connection to server";
    downloadPath=QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
}

void ClientManager::slotReadyReadJson()
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



    qInfo()<<socket->bytesAvailable();

}

void ClientManager::slotReadyReadFile()
{
    fileSocket* temp=nullptr;
    for(fileSocket* t : fileSockets)
    {
        if(t->socket==qobject_cast<QSslSocket *>(sender()))
        {
            temp=t;
            break;
        }
    }
    if (temp==nullptr)
        throw("чет напутал");
    QDataStream in(temp->socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status()==QDataStream::Ok){

        for(;;){
            if(temp->titleSize==0){
                if(temp->socket->bytesAvailable()<(sizeof(qint64)+sizeof(qint64)))
                {
                    break;
                }
                in>>temp->titleSize;
                in>>temp->fileSize;
            }
            if(temp->file==nullptr)
            {
                if(temp->socket->bytesAvailable()<temp->titleSize)
                {
                    break;
                }
                QString filename;
                in >> filename;
                QString path;
                if(downloadPath.size()>0&&downloadPath[0]!="")
                    path=downloadPath[0]+"/"+filename;
                else{
                    path=QDir::homePath()+"/"+filename;
                }
                int i=1;
                do
                {
                    QFileInfo check_file(path);
                    if (!check_file.exists()) {
                        break;
                    } else {
                        if(downloadPath.size()>0&&downloadPath[0]!="")
                            path=downloadPath[0]+"/"+filename;
                        else{
                            path=QDir::homePath()+"/"+filename;
                        }
                        for(int j=path.size()-1; j>=0; j--)
                            if(path[j]=='.')
                            {
                                path.insert(j,"("+QString::number(i++)+")");
                                break;
                            }
                    }
                }
                while(true);
                temp->file = new QFile(path);
                temp->file->open(QIODevice::Append);



                break;
            }
            else{
                char ch[1024];
                int read=in.readRawData(ch,sizeof(char)*1024);
                temp->file->write(ch,read);
                temp->alreadyRead+=read;
                if(temp->alreadyRead==temp->fileSize)
                {
                    temp->alreadyRead=0;
                    temp->isReady=true;
                    temp->Data.clear();
                    temp->file->close();
                    delete temp->file;
                    temp->file=nullptr;
                    temp->titleSize=0;
                    temp->fileSize=0;
                    qInfo()<<"прочитал";
                }
                break;
            }
        }

    }
    else
    {
        ServerOrClientError();
    }



    qInfo()<<temp->socket->bytesAvailable();
}
//вывести как нибудь что все пошло не туда...
void ClientManager::ServerOrClientError()
{
    socket->waitForDisconnected();
    Reconnect* rec = new Reconnect;
    connect(rec,SIGNAL(re()),this,SLOT(tryReconnected()));
    connect(socket,SIGNAL(encrypted()),rec,SLOT(reconnectGood()));
    connect(socket,SIGNAL(errorOccurred(QAbstractSocket::SocketError)),rec,SLOT(reconnectEr(QAbstractSocket::SocketError)));
    rec->setModal(true);
    rec->raise();
    rec->show();
}

void ClientManager::SendToServerJson(QJsonObject json)
{
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<quint64(0)<<quint32(JSONMESSAGE)<<json;
    out.device()->seek(0);
    out<<quint64(Data.size()-sizeof(quint64)-sizeof(quint32));
    socket->write(Data);
}

void ClientManager::sslErrorOccured( QList<QSslError> list )
{
        for (const QSslError &error : list) {
            qInfo() << "SSL error:" << error.errorString();
        }
        qobject_cast<QSslSocket *>(sender())->ignoreSslErrors(list);
}

void ClientManager::tryReconnected()
{
    qInfo()<<"Asd";

    QMetaObject::invokeMethod(this, [this]{ socket->connectToHostEncrypted(hostName,port); }, Qt::QueuedConnection);
    for(fileSocket* temp : fileSockets)
    {
        temp->socket->connectToHostEncrypted(hostName,port);
    }
}

fileSocket* ClientManager::GetFileSocket()
{
    for(fileSocket* temp : fileSockets)
    {
        if(temp->isReady)
        {
            return temp;
        }
    }
    fileSocket* temp = new fileSocket();
    temp->socket = new QSslSocket(this);
    const QString serverKeyPath(":/sll/ClientManager/certificate/client.key");
    temp->socket->setPrivateKey(serverKeyPath,QSsl::Rsa);
    connect(temp->socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrorOccured(QList<QSslError> )));
    connect(temp->socket,&QTcpSocket::readyRead, this,&ClientManager::slotReadyReadFile);
    temp->socket->connectToHostEncrypted(hostName,port);
    temp->socket->waitForEncrypted(10000);
    fileSockets.append(temp);
    return temp;
}

void ClientManager::SendRequestFile(QString path)
{
    fileSocket* temp=GetFileSocket();
    temp->isReady=false;
    temp->Data.clear();
    QDataStream out(&(temp->Data),QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<quint64(0)<<quint32(REQUESTFILEMESSAGE)<<path;
    out.device()->seek(0);
    out<<quint64(temp->Data.size()-sizeof(quint64)-sizeof(quint32));
    temp->socket->write(temp->Data);
}

void ClientManager::SendFile(QString path)
{

}

void ClientManager::SendJson(TransferEnum e, QJsonObject json)
{
        QJsonObject sendJson;
        sendJson["Action"]=e;
        sendJson["Data"]=json;
        SendToServerJson(sendJson);
}
