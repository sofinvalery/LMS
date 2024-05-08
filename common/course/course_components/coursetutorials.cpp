#include "coursetutorials.h"

CourseTutorials::CourseTutorials(int32_t id, int32_t order, QString content, QObject *parent)
    :CourseComponent(id,order,parent)
{
    this->content=content;
}

QJsonObject CourseTutorials::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["order"]=order;
    json["content"]=content;
    QJsonObject main;
    main["CourseTutorials"]=json;
    return main;
}

CourseTutorials* CourseTutorials::Deserialize(QJsonObject json)
{
    QJsonObject jsonObj=json["CourseTutorials"].toObject();
    return new CourseTutorials(jsonObj["id"].toInt(),jsonObj["order"].toInt(),
                     jsonObj["content"].toString());
}

QString CourseTutorials::getContent() const
{
    return content;
}

void CourseTutorials::setContent(const QString &newContent)
{
    content = newContent;
}


