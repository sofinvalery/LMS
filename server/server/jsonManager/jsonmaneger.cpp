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
    auth = Authentication::Deserialize(json);
    QList<Course*> list = DatabaseManager::getInstance()->Login(auth);
    QJsonObject sendjson;
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
