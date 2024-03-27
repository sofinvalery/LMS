#include "Forms/Main/mainwindow.h"
#include "Forms/Auth/auth.h"
#include "Forms/MyWidget/mywidget.h"
#include <QApplication>
#include "ClientManager/socketparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth auth;
    MainWindow* mainwindow = nullptr;
    SocketParser::GetInstance();

    auth.setModal(true);
    auth.exec();
    if (auth.authstatus == 1){
        mainwindow = new MainWindow;
        //QWidget* m_widget = new MyWidget(w);
        mainwindow->showFullScreen();
        //m_widget->show();
    }
    if (auth.exit && auth.authstatus != 1){

        return 0;
    }
    return a.exec();
}
