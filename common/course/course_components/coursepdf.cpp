#include "coursepdf.h"


CoursePdf::CoursePdf(int32_t id, int32_t order, QString title, QString url, QObject *parent)
: CourseComponent(id,order, parent)
{
    this->title=title;
    this->url=url;
}

//по нажатию тут передадим данные в новую форму or запрос к серверу и т.д
void CoursePdf::ClickIcon()
{

}

QString CoursePdf::getTitle() const
{
    return title;
}

QString CoursePdf::getUrl() const
{
    return url;
}

QString CoursePdf::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["order"]=order;
    json["title"]=title;
    json["url"]= url;
    QJsonDocument doc(json);
    QString jsonString = doc.toJson();
    return jsonString;
}

CoursePdf CoursePdf::Deserialize(QString jsonString)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = doc.object();
    return CoursePdf(jsonObj["id"].toInt(),jsonObj["order"].toInt(),
                     jsonObj["title"].toString(),jsonObj["url"].toString());
}
