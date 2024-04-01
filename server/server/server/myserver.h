#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include "client.h"
#include<QThread>


class Worker: public QObject
{
    Q_OBJECT

public:

    Q_INVOKABLE void addClient(qintptr socketDescriptor);
};




class Server: public QTcpServer
{
    Q_OBJECT

public:
    void startServer();
    Server(size_t threads = QThread::idealThreadCount()/2, QObject * parent = nullptr);
    ~Server();

protected:

    virtual void incomingConnection(qintptr socketDescriptor);

private:

    void initThreads();

private:

    size_t m_threadCount;

    QVector<QThread*> m_threads;
    QVector<Worker*> m_workers;
    size_t m_rrcounter;
};

#endif // MYSERVER_H
