#include "Forms/Main/mainwindow.h"
#include "Forms/Auth/auth.h"
#include <QApplication>
#include "ClientManager/socketparser.h"
#include "ClientState/clientstate.h"
#include "../common/authentication/group.h"
#include "../common/authentication/authentication.h"


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
    QList<Group*> groups = {
                             new Group(1,"О725Б",false,QList<Authentication*> {new Authentication("asdasd","asdsad",1,"Попов ГЕоргий","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"Эдуард","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"Поп","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"ГЕоргий","sadsad",STUDENT,QList<QString>{"О725Б"})}),
        new Group(1,"А725Б",false,QList<Authentication*> {new Authentication("asdasd","asdsad",1,"Попов ГЕоргий","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                                             new Authentication("asdasd","asdsad",1,"Эдуард","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                                             new Authentication("asdasd","asdsad",1,"Поп","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                                             new Authentication("asdasd","asdsad",1,"ГЕоргий","sadsad",STUDENT,QList<QString>{"О725Б"})}),
        new Group(1,"У725Б",false,QList<Authentication*> {new Authentication("asdasd","asdsad",1,"Попов ГЕоргий","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                                             new Authentication("asdasd","asdsad",1,"Эдуард","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                                             new Authentication("asdasd","asdsad",1,"Поп","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                                             new Authentication("asdasd","asdsad",1,"ГЕоргий","sadsad",STUDENT,QList<QString>{"О725Б"})}),
        };
    ClientState::GetInstance()->setGroups(groups);
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
