#include <QCoreApplication>
#include "server/myserver.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Make a server and starts it
    Server* server=new Server();
    server->startServer();

    return a.exec();
}
