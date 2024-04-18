#include "client.h"

Client::Client(qintptr socketDescriptor, QObject* parent) :
    QObject(parent)
{
    connect(this,SIGNAL(FileData()),this,SLOT(SendFileData()), Qt::QueuedConnection);
    auth=new Authentication*();
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
     qInfo()<<"readyRead";
    QDataStream in(m_client);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status()==QDataStream::Ok){
        for(;;){
            if(nextBlockSize==0){
                if(m_client->bytesAvailable()<(sizeof(quint64)+sizeof(quint32)))
                {
                    break;
                }
                in>>nextBlockSize;
                in>>typeMessage;
            }
            if(typeMessage==JSONMESSAGE){
            if(m_client->bytesAvailable()<nextBlockSize)
            {
                break;
            }
            QJsonObject json;

            in>>json;
            nextBlockSize=0;
            ServerTask *mytask = new ServerTask(json,auth);
            mytask->setAutoDelete(true);
            connect(mytask, SIGNAL(Result(QJsonObject)), this, SLOT(SendToClient(QJsonObject)), Qt::QueuedConnection);
            QThreadPool::globalInstance()->start(mytask);
            break;
            }
            else if(typeMessage==REQUESTFILEMESSAGE){
                if(m_client->bytesAvailable()<nextBlockSize)
                {
                    break;
                }
                QString path;
                in>>path;
                SendFile(path);
                nextBlockSize=0;
                break;
            }
            else if(typeMessage==SENDFILEMESSAGE){

                break;
            }
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
    qInfo()<<quint64(Data.size()-sizeof(quint64));
    m_client->write(Data);
}


void Client::sslErrorOccured(const QList<QSslError> list)
{
    for (const QSslError &error : list) {
        qInfo() << "SSL error:" << error.errorString();
    }
}

void Client::SendFile(QString path)
{
    QFile sendFile = QFile(path);
    if (sendFile.open(QIODevice::ReadOnly))
    {
        QFileInfo fileInfo(path);
        QString name = fileInfo.fileName();
        QDataStream read(&sendFile);
        read.setVersion(QDataStream::Qt_6_2);
        QByteArray send;
        send.clear();
        QDataStream sendStream(&send, QIODevice::WriteOnly);
        sendStream.setVersion(QDataStream::Qt_6_2);
        sendStream<<qint64(0)<<qint64(sendFile.size())<<name;
        qInfo()<<sendFile.size();
        sendStream.device()->seek(0);
        sendStream<<quint64(send.size()-sizeof(quint64)-sizeof(quint64));
        m_client->write(send);
        m_client->waitForBytesWritten();
        while(!read.atEnd())
        {
            sizeFile = read.readRawData(DataFile,sizeof(char)*1024);
            alreadySendFile =m_client->write(DataFile,sizeFile);
            m_client->waitForBytesWritten();
            if(alreadySendFile==-1)
            {
                qInfo()<<"ошибка отправки файла";
                disconnected();
            }
            while(alreadySendFile!=sizeFile)
            {
              alreadySendFile +=m_client->write(DataFile+alreadySendFile,sizeFile-alreadySendFile);
              m_client->waitForBytesWritten();
              if(alreadySendFile==-1)
              {
                    qInfo()<<"ошибка отправки файла";
                    disconnected();
              }
            }
        }
        alreadySendFile=0;
    }
}

void Client::SendFileData()
{
    alreadySendFile +=m_client->write(DataFile+alreadySendFile,sizeFile-alreadySendFile);
    m_client->waitForBytesWritten();
}

void Client::disconnected()
{
    m_client->close();

    deleteLater();
}
