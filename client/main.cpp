#include "Forms/Main/mainwindow.h"
#include "Forms/Auth/auth.h"
#include "Forms/MyWidget/mywidget.h"
#include <QApplication>
#include "ClientManager/socketparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth b;
    MainWindow* w = nullptr;
    SocketParser::GetInstance();

    b.setModal(true);
    b.exec();
    if (b.authstatus == 1){
        w = new MainWindow;
        //QWidget* m_widget = new MyWidget(w);
        w->showFullScreen();
        //m_widget->show();
    }
    if (b.exit && b.authstatus != 1){

        return 0;
    }
    return a.exec();
}
