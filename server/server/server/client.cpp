#include "client.h"

Client::Client(qintptr socketDescriptor, QObject* parent) :
    QObject(parent)
{
    qInfo() << "new connection";
    m_client = new QTcpSocket(this);

    // set the ID

    m_client->setSocketDescriptor(socketDescriptor);

    connect(m_client, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);


    connect(m_client,SIGNAL(disconnected()),
            this, SLOT(disconnected()), Qt::DirectConnection);
}

 void Client::readyRead()
{
    quint16 nextBlockSize=0;
    QDataStream in(m_client);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status()==QDataStream::Ok){
        for(;;){
            if(nextBlockSize==0){
                if(m_client->bytesAvailable()<2)
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

            SendToClient( jsonManager(json,auth));
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
    out<<quint16(0)<<json;
    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    m_client->write(Data);
}

void Client::disconnected()
{
    m_client->close();

    deleteLater();
}
