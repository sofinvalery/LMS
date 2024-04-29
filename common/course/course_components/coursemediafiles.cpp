#include "coursemediafiles.h"

CourseMediaFiles::CourseMediaFiles(int32_t id, int32_t order, QString title, QString url,TypeFile typeFile, QObject *parent)
    : CourseComponent(id,order, parent)
{
    this->title=title;
    this->url=url;
    this->typeFile=typeFile;
}

TypeFile CourseMediaFiles::getTypeFile() const
{
    return typeFile;
}


//по нажатию тут передадим данные в новую форму or запрос к серверу и т.д
void CourseMediaFiles::ClickIcon()
{

}

QWidget *CourseMediaFiles::QWidgetShow()
{
    return new QTextEdit();
}

QString CourseMediaFiles::getTitle() const
{
    return title;
}

QString CourseMediaFiles::getUrl() const
{
    return url;
}

QJsonObject CourseMediaFiles::Serialize()
{
    QJsonObject main;
    QJsonObject json;
    json["id"]=id;
    json["order"]=order;
    json["title"]=title;
    json["url"]= url;
    json["typeFile"]=typeFile;
    main["CourseMediaFiles"]=json;
    return main;
}

CourseMediaFiles* CourseMediaFiles::Deserialize(QJsonObject jsonObj)
{
    QJsonObject json=jsonObj["CourseMediaFiles"].toObject();
    return new CourseMediaFiles(json["id"].toInt(),json["order"].toInt(),
                                json["title"].toString(),json["url"].toString(),(TypeFile)json["typeFile"].toInt());
}
