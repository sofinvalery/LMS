#include <QCoreApplication>
#include "server\myserver.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Make a server and starts it
    MyServer server;
    server.startServer();

    return a.exec();
}
