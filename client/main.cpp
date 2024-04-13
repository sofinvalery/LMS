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
    Group* group = new Group(1,"О725Б",false,QList<Authentication*> {new Authentication("asdasd","asdsad",1,"Попов ГЕоргий","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"Эдуард","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"Поп","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"ГЕоргий","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"Jon","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"Kate","sadsad",STUDENT,QList<QString>{"О725Б"}),
                                new Authentication("asdasd","asdsad",1,"Psich","sadsad",STUDENT,QList<QString>{"О725Б"})});
    ClientState::GetInstance()->setGroup(group);
    QList<QString> potoksName{"О1","О2","О3","А3","А1","Ж6","Б0","КА","КВ","ВК"};
    ClientState::GetInstance()->setPotoksName(potoksName);
    QList<QString> gtoupsname{"О721","О212","О2133","А2133","А1123","Ж6123","Б1230","К12А","КВ12","ВК12"};
    ClientState::GetInstance()->setGroupsName(gtoupsname);
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
