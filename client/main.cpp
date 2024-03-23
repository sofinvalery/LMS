#include "Forms/Main/mainwindow.h"
#include "Forms/Auth/auth.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth b;
    MainWindow w;
    b.setModal(true);
    b.exec();
    if (b.authstatus == 1){

        w.showFullScreen();
    }
    if (b.exit){
        w.close();
        qApp->quit();
    }
    return a.exec();
}
