#include "Forms/Auth/auth.h"
#include <QApplication>
#include <QThreadPool>
#include "ClientManager/socketparser.h"
#include "ClientManager/clientmanager.h"
#include <QPalette>
#include <QStyle>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ClientState::GetInstance();
    QThread* thread= new QThread();
    ClientManager::GetInstance()->moveToThread(thread);
    SocketParser::GetInstance()->moveToThread(thread);
    thread->start();
    Auth auth;
    auth.open();
    return a.exec();
}
