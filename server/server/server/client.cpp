#include "client.h"

Client::Client(qintptr socketDescriptor, QObject* parent) :
    QObject(parent)
{
    connect(this,SIGNAL(ReadFileDataToClient()),this,SLOT(ReadFileData()),Qt::QueuedConnection);
    connect(this,SIGNAL(SendFileDataToClient()),this,SLOT(SendFileData()),Qt::DirectConnection);
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
                if(nextBlockSize==0)//если файла нет возвращает 0 0
                {
                    break;
                }
                if(fileSocket.file==nullptr)
                {
                    if(m_client->bytesAvailable()<nextBlockSize)
                    {
                        break;
                    }
                    QString filename;
                    QString path;
                    in>>fileSocket.fileSize;
                    fileSocket.titleSize=nextBlockSize;
                    in >> filename;
                    in>>path;
                    fileSocket.file = new QFile(path+filename);
                    if(!fileSocket.file->open(QIODevice::Append))
                    {
                        qInfo()<<"все плохо с путем при чтении файла";
                    }
                    break;
                }
                else{
                    char ch[2048];
                    int read;
                     do{
                        read=in.readRawData(ch,sizeof(char)*2048);
                    fileSocket.file->write(ch,read);
                    fileSocket.alreadyRead+=read;
                    }while(read!=0);
                    if(fileSocket.alreadyRead==fileSocket.fileSize)
                    {
                        nextBlockSize=0;
                        fileSocket.alreadyRead=0;
                        fileSocket.Data.clear();
                        fileSocket.file->close();
                        delete fileSocket.file;
                        fileSocket.file=nullptr;
                        fileSocket.titleSize=0;
                        fileSocket.fileSize=0;
                        qInfo()<<"прочитал";
                    }
                    break;
                }
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
        fileParams.sendFile=new QFile(path);
        QByteArray send;
        QDataStream sendStream(&send, QIODevice::WriteOnly);
        send.clear();
        sendStream.setVersion(QDataStream::Qt_6_2);
        if(!fileParams.sendFile->open(QIODevice::ReadOnly))
        {
            sendStream<<qint64(0)<<qint64(0);
            m_client->write(send);
            fileParams.sendFile->close();
            delete fileParams.sendFile;
            return;
        }
        else{
            fileParams.fileInfo = new QFileInfo(path);
            QString name = fileParams.fileInfo->fileName();
            sendStream<<qint64(0)<<qint64(fileParams.sendFile->size())<<name;
            qInfo()<<fileParams.sendFile->size();
            sendStream.device()->seek(0);
            sendStream<<quint64(send.size()-sizeof(quint64)-sizeof(quint64));
            m_client->write(send);
            fileParams.read= new QDataStream(fileParams.sendFile);
            m_client->waitForBytesWritten();
            ReadFileData();
        }
}

void Client::SendFileData()
{
    fileParams.SendFileSize =m_client->write(fileParams.DataFile,fileParams.sizeFile);
    m_client->waitForBytesWritten();
    if(fileParams.SendFileSize==-1)
    {
        qInfo()<<"ошибка отправки файла";
        fileParams.sizeFile=0;//в функцию бы это вынести но лень
        fileParams.SendFileSize=0;
        delete fileParams.read;
        fileParams.read=nullptr;
        delete fileParams.fileInfo;
        fileParams.fileInfo=nullptr;
        fileParams.sendFile->close();
        delete fileParams.sendFile;
        fileParams.sendFile=nullptr;
        disconnected();
        return;
    }
    while(fileParams.SendFileSize!=fileParams.sizeFile)
    {
        fileParams.SendFileSize +=m_client->write(fileParams.DataFile+fileParams.SendFileSize,fileParams.sizeFile-fileParams.SendFileSize);
        m_client->waitForBytesWritten();
        if(fileParams.SendFileSize==-1)
        {
            qInfo()<<"ошибка отправки файла";
            fileParams.sizeFile=0;
            fileParams.SendFileSize=0;
            delete fileParams.read;
            fileParams.read=nullptr;
            delete fileParams.fileInfo;
            fileParams.fileInfo=nullptr;
            fileParams.sendFile->close();
            delete fileParams.sendFile;
            fileParams.sendFile=nullptr;
            disconnected();
            return;
        }
    }
    if(fileParams.read->atEnd()){
        fileParams.sizeFile=0;
        fileParams.SendFileSize=0;
        delete fileParams.read;
        fileParams.read=nullptr;
        delete fileParams.fileInfo;
        fileParams.fileInfo=nullptr;
        fileParams.sendFile->close();
        delete fileParams.sendFile;
        fileParams.sendFile=nullptr;
        qInfo()<<"отправил";
    }
    else
    {
        emit ReadFileDataToClient();
    }
}

void Client::ReadFileData()
{
    fileParams.sizeFile=fileParams.read->readRawData(fileParams.DataFile,sizeof(char)*2048);
    emit SendFileDataToClient();
}

void Client::disconnected()
{
    m_client->close();

    deleteLater();
}
