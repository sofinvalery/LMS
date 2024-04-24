#include "socketparser.h"



SocketParser* SocketParser::s_Instance = nullptr;

SocketParser::SocketParser(QObject *parent)
    : QObject{parent}
{
    connect(ClientManager::GetInstance(),SIGNAL(Readed(QJsonObject)),this,SLOT(socketparse(QJsonObject)));
}

void SocketParser::socketparse(QJsonObject json)
{
    QJsonObject data=json["Data"].toObject();
    TransferEnum e = (TransferEnum)json["Action"].toInt();
    switch(e){
    case LOGINING: logining(data);
        break;
    case GETMAINPAGE: getMainPage(data);
        break;
    case GETINFOFORADDINGPOTOK: getAddPotok(data);
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
    ClientState::GetInstance()->setListCourses(list);
    emit logined();
}

void SocketParser::getMainPage(QJsonObject json)
{
    QJsonArray components=json.value("CourseList").toArray();
    QList<Course*> list;
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


