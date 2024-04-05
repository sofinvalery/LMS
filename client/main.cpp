#include "Forms/Main/mainwindow.h"
#include "Forms/Auth/auth.h"
#include <QApplication>
#include "ClientManager/socketparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth auth;
    MainWindow mainwindow = nullptr;
    //штука гледа для лога
    //SocketParser::GetInstance();

    auth.setModal(true);
    auth.exec();  //auth.open();
    if (auth.authstatus == 1){

        mainwindow.showFullScreen();
    }
    if (auth.exit){
        return 0;
    }
    return a.exec();
}
