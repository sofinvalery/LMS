#include "Forms/Main/mainwindow.h"
#include "Forms/Auth/auth.h"
#include <QApplication>
#include "ClientManager/socketparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth auth;
    MainWindow* mainwindow = nullptr;
    SocketParser::GetInstance();

    auth.setModal(true);
    auth.open();

    return a.exec();
}
