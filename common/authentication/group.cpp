#include "group.h"

Group::Group(int32_t id, QString classname, bool isTeacherGroup,  QList<Authentication*> participants,
QObject *parent)

    : QObject{parent}
{
    this->id=id;
    this->classname=classname;
    this->isTeacherGroup=isTeacherGroup;
    this->participants=participants;
}

int32_t Group::getId() const
{
    return id;
}

QString Group::getClassname() const
{
    return classname;
}

bool Group::getIsTeacherGroup() const
{
    return isTeacherGroup;
}

QList<Authentication *> Group::getParticipants() const
{
    return participants;
}

QJsonObject Group::Serialize()
{
    QJsonObject json;
    QJsonArray list;
    for (auto & user : participants)
        list.append(user->Serialize());
    json["participants"]=list;
    json["id"]=id;
    json["classname"]=classname;
    json["isTeacherGroup"]=isTeacherGroup;
    return json;
}

Group *Group::Deserialize(QJsonObject jsonObj)
{
    QList<Authentication*> participants;
    QJsonArray questions=jsonObj["participants"].toArray();
    for(int i=0;i<questions.size();i++)
        participants.append(Authentication::Deserialize(questions[i].toObject()));
    return new Group(jsonObj["id"].toInt(),jsonObj["classname"].toString(),
                 jsonObj["isTeacherGroup"].toBool(),participants);
}
