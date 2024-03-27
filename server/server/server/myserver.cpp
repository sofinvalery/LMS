#include "myserver.h"

Server::Server(size_t threads, QObject * parent) :
    QTcpServer(parent),
    m_threadCount(threads),
    m_rrcounter(0)
{
    initThreads();
}

void Server::startServer()
{
    int port = 1234;

    if(!this->listen(QHostAddress::Any,port))
    {
        qInfo() << "Could not start server";
    }
    else
    {
        qInfo() << "Listening to port " << port << "...";
    }
}



Server::~Server()
{
    for(QThread* thread: m_threads)
    {
        thread->quit();
        thread->wait();
    }
}

void Server::initThreads()
{
    for (size_t i = 0; i < m_threadCount; ++i)
    {
        QThread* thread = new QThread(this);

        Worker* worker = new Worker();
        worker->moveToThread(thread);
        connect(thread, &QThread::finished,
                worker, &QObject::deleteLater);

        m_threads.push_back(thread);
        m_workers.push_back(worker);

        thread->start();
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    Worker* worker = m_workers[m_rrcounter % m_threadCount];
    ++m_rrcounter;

    QMetaObject::invokeMethod(worker, "addClient",
                              Qt::QueuedConnection,
                              Q_ARG(qintptr, socketDescriptor));
}
void Worker::addClient(qintptr socketDescriptor)
{
    new Client(socketDescriptor, this);
}
