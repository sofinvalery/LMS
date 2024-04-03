#include "client.h"

Client::Client(qintptr socketDescriptor, QObject* parent) :
    QObject(parent)
{
    qInfo() << "new connection";
    m_client = new QSslSocket(this);
    if (m_client->setSocketDescriptor(socketDescriptor)) {
        const QString serverCertPath(":/sll/server/certificate/server.crt");
        const QString serverKeyPath(":/sll/server/certificate/server.key");
        m_client->setLocalCertificate(serverCertPath);
        m_client->setPrivateKey(serverKeyPath,QSsl::Rsa);
        connect(m_client, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
        connect(m_client,SIGNAL(disconnected()),
                this, SLOT(disconnected()), Qt::DirectConnection);
        connect(m_client, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(sslErrorOccured(QList<QSslError>)));
        m_client->startServerEncryption();
    } else {
        delete m_client;
    }
}

 void Client::readyRead()
{
    quint64 nextBlockSize=0;
    QDataStream in(m_client);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status()==QDataStream::Ok){
        for(;;){
            if(nextBlockSize==0){
                if(m_client->bytesAvailable()<sizeof(quint64))
                {
                    break;
                }
                in>>nextBlockSize;
            }
            if(m_client->bytesAvailable()<nextBlockSize)
            {
                break;
            }
            QJsonObject json;

            in>>json;
            ServerTask *mytask = new ServerTask(json,auth);
            mytask->setAutoDelete(true);
            connect(mytask, SIGNAL(Result(QJsonObject)), this, SLOT(SendToClient(QJsonObject)), Qt::QueuedConnection);
            QThreadPool::globalInstance()->start(mytask);
            break;
        }
    }
    else{
        qDebug()<<"Все пошло по одному месту";
    }
}

void Client::SendToClient(QJsonObject json){

    QByteArray Data;
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<quint64(0)<<json;
    out.device()->seek(0);
    out<<quint64(Data.size()-sizeof(quint64));
    m_client->write(Data);
}


void Client::sslErrorOccured(const QList<QSslError> list)
{
    for (const QSslError &error : list) {
        qInfo() << "SSL error:" << error.errorString();
    }
}

void Client::disconnected()
{
    m_client->close();

    deleteLater();
}
