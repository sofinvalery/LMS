#include "Forms/Main/mainwindow.h"
#include "Forms/Auth/auth.h"
#include <QApplication>
#include "ClientManager/socketparser.h"
#include "ClientState/clientstate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth auth;
    //штука гледа для лога
    //SocketParser::GetInstance();
    Authentication* authentication = new Authentication("admin","admin");
    authentication->SetInformationAfterAuthentication("Max","bbbbb",ADMIN,55,QList<QString>{"O725B"});
    QList<Course*> list= {new Course(5,"maths","aaaaa", QDate(1999,9,9),QDate(2000,1,1),20,100),
                            new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80),
                             new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80),
                             new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80),
                             new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80)};
    ClientState::GetInstance()->setAuth(authentication);
    ClientState::GetInstance()->setListCourses(list);


    auth.setModal(true);
    auth.exec();  //auth.open();
    if (auth.authstatus == 1){
        ClientState::GetInstance()->getMainwindow()->showFullScreen();
        ClientState::GetInstance()->getMainwindow()->ShowManePage();
    }
    if (auth.exit){
        return 0;
    }
    return a.exec();
}
