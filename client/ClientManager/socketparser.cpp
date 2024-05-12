#include "socketparser.h"



SocketParser* SocketParser::s_Instance = nullptr;

SocketParser::SocketParser(QObject *parent)
    : QObject{parent}
{
    connect(ClientManager::GetInstance(),SIGNAL(Readed(QJsonObject)),this,SLOT(socketparse(QJsonObject)));
}

void SocketParser::socketparse(QJsonObject json)
{
    if(json.find("Data")==json.end())
        return;
    QJsonObject data=json["Data"].toObject();
    TransferEnum e = (TransferEnum)json["Action"].toInt();
    switch(e){
    case LOGINING: logining(data);
        break;
    case GETMAINPAGE: getMainPage(data);
        break;
    case GETINFOFORADDINGPOTOK: getAddPotok(data);
        break;
    case GETINFOFORADDINGGROUP: getAddGroup(data);
        break;
    case GETINFOFORAADDINGCOURSE: getAddCourse(data);
        break;
    case GETINFOFOREDITGROUP: getEditGroup(data);
        break;
    case GETGROUP: getGroup(data);
        break;
    case GETCOURSECOMPONENTS: getCourseComponents(data);
        break;
    case GETALLCOURSECOMPONENTS: getScore(data);
        break;
    case GETGROUPSBYCOURSEID: showTeacherScore(data);
        break;
    case GETSUBMITS: getSubmit(data);
        break;
    }
}

void SocketParser::logining(QJsonObject json)
{
    ClientState::GetInstance()->setAuth(Authentication::Deserialize(json.value("Authentication").toObject()));
    QJsonArray components=json.value("CourseList").toArray();
    QList<Course*> list;
    for(qsizetype i=0;i<components.size();i++)
        list.append(Course::Deserialize(components[i].toObject()));
    if(components.size()>0)
    ClientState::GetInstance()->setListCourses(list);
    emit logined();
}

void SocketParser::getMainPage(QJsonObject json)
{
    QJsonArray components=json.value("CourseList").toArray();
    QList<Course*> list;
    qInfo()<<components.size();
    for(qsizetype i=0;i<components.size();i++)
        list.append(Course::Deserialize(components[i].toObject()));
    ClientState::GetInstance()->setListCourses(list);
    emit getMainPage();
}

void SocketParser::getAddPotok(QJsonObject json)
{
    QJsonArray groupsComponents=json.value("studentGroupName").toArray();
    QList<QString> studentGroupName;
    for(qsizetype i=0;i<groupsComponents.size();i++)
        studentGroupName.append(groupsComponents[i].toString());
    ClientState::GetInstance()->setGroupsName(studentGroupName);

    QJsonArray potoksComponents=json.value("potoksName").toArray();
    QList<QString> potoksName;
    for(qsizetype i=0;i<potoksComponents.size();i++)
        potoksName.append(potoksComponents[i].toString());
    ClientState::GetInstance()->setPotoksName(potoksName);

    emit getAddPotok();
}

void SocketParser::getAddGroup(QJsonObject json)
{
    QJsonArray groupsComponents=json.value("GroupName").toArray();
    QList<QString> GroupName;
    for(qsizetype i=0;i<groupsComponents.size();i++)
        GroupName.append(groupsComponents[i].toString());
    ClientState::GetInstance()->setGroupsName(GroupName);

    emit getAddGroup();
}

void SocketParser::getAddCourse(QJsonObject json)
{
    QJsonArray groupsComponents=json.value("TeacherGroupNames").toArray();
    QList<QString> TeacherGroupNames;
    for(qsizetype i=0;i<groupsComponents.size();i++)
        TeacherGroupNames.append(groupsComponents[i].toString());
    ClientState::GetInstance()->setGroupsName(TeacherGroupNames);

    QJsonArray potoksComponents=json.value("PotokNames").toArray();
    QList<QString> PotokNames;
    for(qsizetype i=0;i<potoksComponents.size();i++)
        PotokNames.append(potoksComponents[i].toString());
    ClientState::GetInstance()->setPotoksName(PotokNames);


    emit getAddCourse();
}

void SocketParser::getEditGroup(QJsonObject json)
{
    QJsonArray groupsComponents=json.value("GroupName").toArray();
    QList<QString> GroupName;
    for(qsizetype i=0;i<groupsComponents.size();i++)
        GroupName.append(groupsComponents[i].toString());
    ClientState::GetInstance()->setGroupsName(GroupName);

    emit getEditGroup();
}

void SocketParser::getGroup(QJsonObject json)
{
    Group* gr = Group::Deserialize(json);
    ClientState::GetInstance()->setGroup(gr);

    emit getShowEditGroup();
}

void SocketParser::getCourseComponents(QJsonObject json)
{
    int id = json["CourseId"].toInt();
    QList<CourseComponent*> ls = Course::DeserializeListComponentsCourse(json);
    for(auto temp : ClientState::GetInstance()->getListCourses())
        if(temp->GetCourseId()==id)
        {
            temp->setListComponents(ls);
            emit getCourseComponents(temp);
            break;
        }
}

void SocketParser::getScore(QJsonObject json)
{
    QJsonArray groupsComponents=json.value("ComponentsList").toArray();
    for(auto component:groupsComponents){
        int id = component.toObject()["CourseId"].toInt();
        QList<CourseComponent*> ls = Course::DeserializeListComponentsCourse(component.toObject());
        for(auto temp : ClientState::GetInstance()->getListCourses())
            if(temp->GetCourseId()==id)
            {
                temp->setListComponents(ls);
                break;
            }
    }

    emit getScore();
}

void SocketParser::showTeacherScore(QJsonObject json)
{
    QJsonArray groupsComponents=json.value("Groups").toArray();
    QList<QString> groupsName;
    for(auto component:groupsComponents){
        groupsName.append(component.toString());
    }
    ClientState::GetInstance()->setGroupsName(groupsName);

    emit showTeacherScore();
}

void SocketParser::getSubmit(QJsonObject json)
{
    Group* gr = Group::Deserialize(json["Group"].toObject());
    QList<Submit*> submits;
    QJsonArray components=json.value("Submits").toArray();
    for(auto temp:components){
        Submit* submit =new Submit();
        submit->student= Authentication::Deserialize(temp.toObject()["Authentication"].toObject());
        if(temp.toObject()["CourseSubmit"].toObject().contains("CourseTask"))
            submit->work= CourseTask::Deserialize(temp.toObject()["CourseSubmit"].toObject());
        else if(temp.toObject()["CourseSubmit"].toObject().contains("CourseTest"))
            submit->work=CourseTest::Deserialize(temp.toObject()["CourseSubmit"].toObject());
        else{
            qDebug()<<"ошибка в парсинге сокета getSubmit скорее всего на стороне сервера";
            return;
        }
        submits.append(submit);
    }
    emit getSubmit(submits,gr);
}


