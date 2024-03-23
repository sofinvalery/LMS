#include "coursevideos.h"



CourseVideos::CourseVideos(int32_t id, int32_t order, QString title, QString url, QObject *parent)
    : CourseComponent(id,order, parent)
{
    this->title=title;
    this->url=url;
}

//по нажатию тут передадим данные в новую форму or запрос к серверу и т.д
void CourseVideos::ClickIcon()
{

}

QWidget *CourseVideos::QWidgetShow()
{
    return new QTextEdit();
}


QString CourseVideos::getTitle() const
{
    return title;
}

QString CourseVideos::getUrl() const
{
    return url;
}

QJsonObject CourseVideos::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["order"]=order;
    json["title"]=title;
    json["url"]= url;
    QJsonObject main;
    main["CourseVideos"]=json;
    return main;
}

CourseVideos* CourseVideos::Deserialize(QJsonObject json)
{
    QJsonObject jsonObj=json["CourseVideos"].toObject();
    return new CourseVideos(jsonObj["id"].toInt(),jsonObj["order"].toInt(),
                     jsonObj["title"].toString(),jsonObj["url"].toString());
}
