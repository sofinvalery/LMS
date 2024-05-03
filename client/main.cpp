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

    // a.setStyle("Fusion");
    // QPalette palette;
    // palette.setColor(QPalette::Window, QColor(245, 245, 245));
    // palette.setColor(QPalette::WindowText, Qt::black);
    // palette.setColor(QPalette::Base, QColor(255, 255, 255));
    // palette.setColor(QPalette::AlternateBase, QColor(245, 245, 245));
    // palette.setColor(QPalette::ToolTipBase, Qt::black);
    // palette.setColor(QPalette::ToolTipText, Qt::white);
    // palette.setColor(QPalette::Text, Qt::black);
    // palette.setColor(QPalette::Button, QColor(245, 245, 245));
    // palette.setColor(QPalette::ButtonText, Qt::black);
    // palette.setColor(QPalette::BrightText, Qt::red);
    // palette.setColor(QPalette::Link, QColor(0, 0, 255));
    // palette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    // palette.setColor(QPalette::HighlightedText, Qt::white);
    // a.setPalette(palette);

    Auth auth;
<<<<<<< HEAD
    auth.open();

=======
    //штука гледа для лога
    //SocketParser::GetInstance();
    Authentication* authentication = new Authentication("admin","admin");
    authentication->SetInformationAfterAuthentication("Max","bbbbb",ADMIN,55,QList<QString>{"O725B"});
    QList<Course*> list= {new Course(5,"maths",":/img/resources/kap.jpg", QDate(1999,9,9),QDate(2000,1,1),20,100),
                            new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80),
                             new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80),
                             new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80),
                             new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80)};
    QList<CourseComponent*> sad = {new CoursePdf(21313, 1, "testpdf", ""), new CoursePdf(21313, 1, "testpdf", ""), new CoursePdf(21313, 1, "testpdf", ""), new CoursePdf(21313, 1, "testpdf", ""),
                                    new CourseTest(12123, 3, "testtest", 10, "", 100, 9, "сдал", QDate(2004,4,4)), new CourseTask(1213123, 4, "adsasda", 10, 15, "pdf", "qwe", QDate(2004,4,4), 9, ""),
                                    new CourseTutorials(123123, 5, "tutorial")};
    ClientState::GetInstance()->setAuth(authentication);
    ClientState::GetInstance()->setListCourses(list);
    ClientState::GetInstance()->getListCourses()[0]->setListComponents(sad);
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
    QList<QString> gtoupsname{"О721", "О212", "О2133", "О214", "О215", "О216", "О217", "О218", "О219", "О220",
                              "О221", "О222", "О223", "О224", "О225", "О226", "О227", "О228", "О229", "О230",
                              "О231", "О232", "О233", "О234", "О235", "О236", "О237", "О238", "О239", "О240",
                              "О241", "О242", "О243", "О244", "О245", "О246", "О247", "О248", "О249", "О250",
                              "О251", "О252", "О253", "О254", "О255", "О256", "О257", "О258", "О259", "О260"};
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
>>>>>>> 22bb22f (coursepage img)
    return a.exec();
}
