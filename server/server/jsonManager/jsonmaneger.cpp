#include "jsonmaneger.h"

typedef QJsonObject (*Action)(QJsonObject,Authentication *auth);

static Action Actions[] ={
    [LOGINING] = logining,
    [GETMAINPAGE] = getMainPage,
    [GETCOURSECOMPONENTS] = getCourseComponents,
    [GETTESTQUESTION] = getTestQuestions,
    [SETNEWGROUPSTUDENTS] = setNewGroupStudents,
    [SETNEWTEST] = setNewTest,
    [SETNEWCOURSE] = setNewCourse
};

QJsonObject jsonManager(QJsonObject json,Authentication *auth)
{
    QJsonObject data=json["Data"].toObject();
    TransferEnum e = (TransferEnum)json["Action"].toInt();
    if( (auth==nullptr&& e!=LOGINING) || (auth!=nullptr && !auth->IsAuthenticated() && e!=LOGINING))
        throw std::exception();
    return Actions[e](data,auth);
}

QJsonObject logining(QJsonObject json,Authentication *auth)
{
    QJsonObject sendjson;
    auth = Authentication::Deserialize(json);
    //QList<Course*> list = DatabaseManager::getInstance()->Login(auth);
    QList<Course*> list= {new Course(5,"maths","aaaaa", QDate(1999,9,9),QDate(2000,1,1),20,100),
                            new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80)};
   // auth->SetInformationAfterAuthentication("Max","bbbbb",ADMIN,55,QList<QString>{"O725B"});
    QJsonArray components;
    for (auto & user : list)
        components.append(user->Serialize());
    sendjson["Action"]=LOGINING;
    QJsonObject temp;
    temp["Authentication"]=auth->Serialize();
    temp["CourseList"]=components;
    sendjson["Data"]=temp;
    return sendjson;
}

QJsonObject getMainPage(QJsonObject json,Authentication *auth)
{
    auth = Authentication::Deserialize(json);
    QList<Course*> list = DatabaseManager::getInstance()->Login(auth);
    QJsonObject sendjson;
    QJsonArray components;
    for (auto & user : list)
        components.append(user->Serialize());
    sendjson["Action"]=GETMAINPAGE;
    sendjson["Data"]=components;
}

QJsonObject getCourseComponents(QJsonObject json,Authentication *auth)
{

}

QJsonObject getTestQuestions(QJsonObject json,Authentication *auth)
{

}

QJsonObject setNewGroupStudents(QJsonObject json,Authentication *auth)
{

}

QJsonObject setNewTest(QJsonObject json,Authentication *auth)
{

}

QJsonObject setNewCourse(QJsonObject json,Authentication *auth)
{

}
