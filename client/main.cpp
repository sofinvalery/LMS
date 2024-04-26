#include "Forms/Auth/auth.h"
#include <QApplication>
#include <QThreadPool>
#include "ClientManager/socketparser.h"
#include "ClientManager/clientmanager.h"
#include <QPalette>
#include <QStyle>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientState::GetInstance();
    QThread* thread= new QThread();
    ClientManager::GetInstance()->moveToThread(thread);
    SocketParser::GetInstance()->moveToThread(thread);
    thread->start();
    qInfo()<< QDir::currentPath();
    Auth auth;
    //штука гледа для лога
    a.setStyle("Fusion");
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(245, 245, 245));
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, QColor(255, 255, 255));
    palette.setColor(QPalette::AlternateBase, QColor(245, 245, 245));
    palette.setColor(QPalette::ToolTipBase, Qt::black);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, QColor(245, 245, 245));
    palette.setColor(QPalette::ButtonText, Qt::black);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, QColor(0, 0, 255));
    palette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    palette.setColor(QPalette::HighlightedText, Qt::white);
    a.setPalette(palette);
    auth.open();
    return a.exec();
}
