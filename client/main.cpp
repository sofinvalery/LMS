#include "Forms/Main/mainwindow.h"
#include "Forms/Auth/auth.h"
#include <QApplication>
#include "ClientManager/socketparser.h"
#include "ClientManager/clientmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth auth;
    //штука гледа для лога



    auth.open();

    ClientManager::GetInstance();
    SocketParser::GetInstance();
    return a.exec();
}
