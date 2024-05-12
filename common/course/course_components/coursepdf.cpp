#include "coursepdf.h"
#include "../../../client/Forms/CoursePageComponents/CourseDownload/coursedownload.h"


CoursePdf::CoursePdf(int32_t id, int32_t order, QString title, QString url, QObject *parent)
: CourseComponent(id,order, parent)
{
    this->title=title;
    this->url=url;
}

QString CoursePdf::getTitle() const
{
    return title;
}

QString CoursePdf::getUrl() const
{
    return url;
}

QJsonObject CoursePdf::Serialize()
{
    QJsonObject main;
    QJsonObject json;
    json["id"]=id;
    json["order"]=order;
    json["title"]=title;
    json["url"]= url;
    main["CoursePdf"]=json;
    return main;
}

CoursePdf* CoursePdf::Deserialize(QJsonObject jsonObj)
{
    QJsonObject json=jsonObj["CoursePdf"].toObject();
    return new CoursePdf(json["id"].toInt(),json["order"].toInt(),
                     json["title"].toString(),json["url"].toString());
}

void CoursePdf::setTitle(const QString &newTitle)
{
    title = newTitle;
}

void CoursePdf::setUrl(const QString &newUrl)
{
    url = newUrl;
}
