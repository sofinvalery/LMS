#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QSslSocket>
#include<QJsonObject>
#include "../common/transferEnum/transferEnum.h"
#include <QFile>
#include <QFileInfo>

struct FileParams{
    QFile* sendFile=nullptr;
    QDataStream* read=nullptr;
    QFileInfo* fileInfo=nullptr;
    char DataFile[2048];
    int sizeFile=0;
    int SendFileSize=0;
};

class fileSocket: public QObject
{
    Q_OBJECT
public:
    explicit fileSocket(QObject *parent = nullptr){};
    bool isReady;
    QSslSocket *socket;
    QByteArray Data;
    qint64 titleSize=0;
    qint64 fileSize=0;
    qint64 alreadyRead=0;
    QFile* file=nullptr;
    FileParams fileParams;
    QString fileName;
signals:
    void newFile(QString,qint64);
    void downloadFinish(QString);
    void addRead(qint64);
};

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
    QList<fileSocket*> fileSockets;
    static ClientManager* s_Instance;
    QList<QString> downloadPath;

private slots:

    void slotReadyReadJson();
    void slotReadyReadFile();
    void ServerOrClientError();
    void SendToServerJson(QJsonObject json);
    fileSocket* GetFileSocket();
    void sslErrorOccured( QList<QSslError> list);
    void tryReconnected();
    void SendJson(TransferEnum e, QJsonObject json);
    void SendRequestFile(QString path);
    void SendFile(QString clientPath, QString serverPath);
    void SendFileData(fileSocket*);
    void ReadFileData(fileSocket*);
    void DeleteFileParams(fileSocket*);

public:
    static ClientManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new ClientManager()); }
    void SendJsonToServer(TransferEnum e, QJsonObject json);
    void SendRequestFileToServer(QString path);
    void SendFileToServer(QString clientPath, QString serverPath);

signals:
    void Readed(QJsonObject);
    void Json(TransferEnum e, QJsonObject json);
    void RequestFile(QString path);
    void File(QString clientPath, QString serverPath);
    void ReadFileDataToServer(fileSocket*);
    void SendFileDataToServer(fileSocket*);
    void ErrorConnect();
};

#endif // CLIENTMANAGER_H
