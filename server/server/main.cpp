#include <QCoreApplication>
#include "server/myserver.h"
#include "QDir"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInfo()<<QDir::currentPath();
    // Make a server and starts it
    Server* server=new Server();
    server->startServer();
    return a.exec();
}
