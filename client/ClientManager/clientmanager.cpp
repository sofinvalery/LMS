#include "clientmanager.h"
#include <QSslConfiguration>
#include <QStandardPaths>
#include <QDir>
#include <ClientState/clientstate.h>

ClientManager* ClientManager::s_Instance = nullptr;


ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    connect(this,SIGNAL(SendFileDataToServer(fileSocket*)),this,SLOT(SendFileData(fileSocket*)),Qt::DirectConnection);
    connect(this,SIGNAL(ReadFileDataToServer(fileSocket*)),this,SLOT(ReadFileData(fileSocket*)),Qt::QueuedConnection);
    qRegisterMetaType<TransferEnum>("TransferEnum");
    connect(this,SIGNAL(Json(TransferEnum,QJsonObject)),this,SLOT(SendJson(TransferEnum,QJsonObject)), Qt::QueuedConnection);
    connect(this,SIGNAL(RequestFile(QString)),this,SLOT(SendRequestFile(QString)), Qt::QueuedConnection);
    connect(this,SIGNAL(File(QString,QString)),this,SLOT(SendFile(QString,QString)), Qt::QueuedConnection);
    connect(this,SIGNAL(ErrorConnect()),this,SLOT(ServerOrClientError()), Qt::QueuedConnection);
    socket = new QSslSocket(this);
    const QString serverKeyPath(":/sll/ClientManager/certificate/client.key");
    socket->setPrivateKey(serverKeyPath,QSsl::Rsa);
    connect(socket,&QTcpSocket::readyRead, this,&ClientManager::slotReadyReadJson);
    connect(socket,&QTcpSocket::disconnected, this,&ClientManager::ServerOrClientError);
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrorOccured(QList<QSslError> )));
    port=1234;
    //hostName="127.0.0.1";
    hostName="188.242.157.174";
    socket->connectToHostEncrypted(hostName,port);
    if (!socket->waitForEncrypted(10000)) {
        qInfo() << socket->errorString();
        emit ErrorConnect();
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
                if(temp->titleSize==0)//если файла нет возвращает 0 0
                {
                    temp->isReady=true;
                    break;
                }
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
                for(int j=path.size()-1; j>=0; j--)
                    if(path[j]=='/')
                    {
                        temp->fileName=path.mid(j+1);
                        break;
                    }

                temp->file = new QFile(path);
                temp->file->open(QIODevice::Append);
                emit temp->newFile(temp->fileName,temp->fileSize);
                ClientState::GetInstance()->ShowNotifacate("Загрузка файла:\n"+temp->fileName,"black");

                break;
            }
            else{
                char ch[2048];
                int read;
                do{
                    read=in.readRawData(ch,sizeof(char)*2048);
                    temp->file->write(ch,read);
                    temp->alreadyRead+=read;
                    emit temp->addRead(read);
                }
                while(read!=0);
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
                    emit temp->downloadFinish(temp->fileName);
                    ClientState::GetInstance()->ShowNotifacate("Загружен файл:\n"+temp->fileName,"black");
                }
                break;
            }
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
    socket->waitForDisconnected();
    connect(ClientState::GetInstance()->getRec(),SIGNAL(re()),this,SLOT(tryReconnected()));
    connect(socket,SIGNAL(encrypted()),ClientState::GetInstance()->getRec(),SLOT(reconnectGood()));
    connect(socket,SIGNAL(errorOccurred(QAbstractSocket::SocketError)),ClientState::GetInstance()->getRec(),SLOT(reconnectEr(QAbstractSocket::SocketError)));
    ClientState::GetInstance()->ShowReconnect();
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
        if(temp->file!=nullptr)
        {
            QString name=temp->file->fileName();
            int i = name.size()-1;
            while(i>=0 && name[i--]!='.');
            if(i<0)
            {
                temp->file->rename(name+"_неподтвержденный");
            }
            else{
                temp->file->rename(name.insert(i+1,"_неподтвержденный"));
            }
            temp->file->close();
            delete temp->file;
            temp->file=nullptr;
            temp->alreadyRead=0;
            temp->titleSize=0;
            temp->fileSize=0;
            temp->Data.clear();
        }
        temp->socket->connectToHostEncrypted(hostName,port);
        //можно продолжить загрузку попытаться типо передать скок считали там сдвинуть но лень
        temp->isReady=true;
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
    if(fileSockets.size()<4)
    {
        fileSocket* temp = new fileSocket();
        temp->socket = new QSslSocket(this);
        const QString serverKeyPath(":/sll/ClientManager/certificate/client.key");
        temp->socket->setPrivateKey(serverKeyPath,QSsl::Rsa);

        connect(temp,SIGNAL(newFile(QString,qint64)),ClientState::GetInstance()->getMainwindow()->getDialogLoader(),SLOT(createWidget(QString,qint64)));
        connect(temp,SIGNAL(downloadFinish(QString)),ClientState::GetInstance()->getMainwindow()->getDialogLoader(),SLOT(deleteWidget(QString)));

        connect(temp->socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrorOccured(QList<QSslError> )));
        connect(temp->socket,&QTcpSocket::readyRead, this,&ClientManager::slotReadyReadFile);
        temp->socket->connectToHostEncrypted(hostName,port);
        temp->socket->waitForEncrypted(10000);
        fileSockets.append(temp);
        return temp;
    }
    else return nullptr;
}

void ClientManager::SendRequestFile(QString path)
{
    fileSocket* temp=GetFileSocket();
    if (temp==nullptr)
    {
        ClientState::GetInstance()->ShowNotifacate("Достигнут лимит\nЗагружаемых файлов","red");
        return;
    }
    temp->isReady=false;
    temp->Data.clear();
    QDataStream out(&(temp->Data),QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<quint64(0)<<quint32(REQUESTFILEMESSAGE)<<path;
    out.device()->seek(0);
    out<<quint64(temp->Data.size()-sizeof(quint64)-sizeof(quint32));
    temp->socket->write(temp->Data);
}

void ClientManager::SendFile(QString clientPath, QString serverPath)
{
    fileSocket* temp=GetFileSocket();
    temp->isReady=false;
    temp->fileParams.sendFile=new QFile(clientPath);
    QByteArray send;
    QDataStream sendStream(&send, QIODevice::WriteOnly);
    send.clear();
    sendStream.setVersion(QDataStream::Qt_6_2);
    if(!temp->fileParams.sendFile->open(QIODevice::ReadOnly))
    {
        sendStream<<qint64(0)<<quint32(SENDFILEMESSAGE);
        temp->socket->write(send);
        temp->fileParams.sendFile->close();
        delete temp->fileParams.sendFile;
        return;
    }
    else{
        temp->fileParams.fileInfo = new QFileInfo(clientPath);
        QString name = temp->fileParams.fileInfo->fileName();
        sendStream<<qint64(0)<<quint32(SENDFILEMESSAGE)<<qint64(temp->fileParams.sendFile->size())<<name<<serverPath;
        qInfo()<<temp->fileParams.sendFile->size();
        sendStream.device()->seek(0);
        sendStream<<quint64(send.size()-sizeof(quint64)-sizeof(quint32));
        temp->socket->write(send);
        temp->fileParams.read= new QDataStream(temp->fileParams.sendFile);
        temp->socket->waitForBytesWritten();
        emit temp->newFile(temp->fileParams.fileInfo->fileName(),temp->fileParams.sendFile->size());
        ReadFileData(temp);
    }
}

void ClientManager::SendFileData(fileSocket *temp)
{
    temp->socket->waitForBytesWritten();
    temp->fileParams.SendFileSize =temp->socket->write(temp->fileParams.DataFile,temp->fileParams.sizeFile);
    emit temp->addRead(temp->fileParams.SendFileSize);
    if(temp->fileParams.SendFileSize==-1)
    {
        qInfo()<<"ошибка отправки файла";
        DeleteFileParams(temp);
        int i=0;
        for(; i<fileSockets.size();i++)
        {
            if(fileSockets[i]==temp)
                break;
        }
        QList<fileSocket*>::iterator pos=fileSockets.begin()+i;
        fileSockets.erase(pos);
        temp->socket->close();
        temp->socket->deleteLater();
        delete temp;
        return;
    }
    while(temp->fileParams.SendFileSize!=temp->fileParams.sizeFile)
    {
        temp->socket->waitForBytesWritten();
        temp->fileParams.SendFileSize +=temp->socket->write(temp->fileParams.DataFile+temp->fileParams.SendFileSize,temp->fileParams.sizeFile-temp->fileParams.SendFileSize);
        if(temp->fileParams.SendFileSize==-1)
        {
            qInfo()<<"ошибка отправки файла";
            DeleteFileParams(temp);
            int i=0;
            for(; i<fileSockets.size();i++)
            {
                if(fileSockets[i]==temp)
                    break;
            }
            auto pos=fileSockets.begin()+i;
            fileSockets.erase(pos);
            temp->socket->close();
            temp->socket->deleteLater();
            delete temp;
            return;
        }
    }
    if(temp->fileParams.read->atEnd()){
        emit temp->downloadFinish(temp->fileParams.fileInfo->fileName());
        ClientState::GetInstance()->ShowNotifacate("Выгружен файл:\n"+temp->fileParams.fileInfo->fileName(),"black");
        DeleteFileParams(temp);
    }
    else
    {
        emit ReadFileDataToServer(temp);
    }
}

void ClientManager::ReadFileData(fileSocket* temp)
{
    temp->fileParams.sizeFile=temp->fileParams.read->readRawData(temp->fileParams.DataFile,sizeof(char)*2048);
    emit SendFileDataToServer(temp);
}

void ClientManager::DeleteFileParams(fileSocket * temp)
{
    temp->fileParams.sizeFile=0;
    temp->fileParams.SendFileSize=0;
    delete temp->fileParams.read;
    temp->fileParams.read=nullptr;
    delete temp->fileParams.fileInfo;
    temp->fileParams.fileInfo=nullptr;
    temp->fileParams.sendFile->close();
    delete temp->fileParams.sendFile;
    temp->fileParams.sendFile=nullptr;
}

void ClientManager::SendJsonToServer(TransferEnum e, QJsonObject json)
{
    emit Json(e,json);
}

void ClientManager::SendRequestFileToServer(QString path)
{
    emit RequestFile(path);
}

void ClientManager::SendFileToServer(QString clientPath, QString serverPath)
{
    emit File(clientPath,serverPath);
}

void ClientManager::SendJson(TransferEnum e, QJsonObject json)
{
        QJsonObject sendJson;
        sendJson["Action"]=e;
        sendJson["Data"]=json;
        SendToServerJson(sendJson);
}
