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
}


