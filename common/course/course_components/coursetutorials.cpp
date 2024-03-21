#include "coursetutorials.h"

//по нажатию тут передадим данные в новую форму запрос к серверу и т.д
void CourseTutorials::ClickIcon()
{

}

CourseTutorials::CourseTutorials(int32_t id, int32_t order, QString content, QObject *parent)
    :CourseComponent(id,order,parent)
{
    this->content=content;
}

QString CourseTutorials::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["order"]=order;
    json["content"]=content;
    QJsonDocument doc(json);
    QString jsonString = doc.toJson();
    return jsonString;
}

CourseTutorials CourseTutorials::Deserialize(QString jsonString)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = doc.object();
    return CourseTutorials(jsonObj["id"].toInt(),jsonObj["order"].toInt(),
                     jsonObj["content"].toString());
}

QString CourseTutorials::getContent() const
{
    return content;
}


