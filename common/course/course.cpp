#include "course.h"



Course::Course(int32_t id, QString title, QString avaUrl, QDate start, QDate end, QObject *parent): QObject{parent}
{
    this->id=id;
    this->title=title;
    this->avaTitleUrl=avaUrl;
    this->startTime=start;
    this->endTime=end;
}

Course Course::Deserialize(QString jsonString)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = doc.object();

    QDate start;
    start.fromString(jsonObj["startTime"].toString(),"dd/MM/YYYY");
    QDate end;
    end.fromString(jsonObj["endTime"].toString(),"dd/MM/YYYY");
    return Course(jsonObj["id"].toInt(),jsonObj["title"].toString(),jsonObj["avaTitleUrl"].toString(),start,end);
}

QString Course::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["title"]=title;
    json["avaTitleUrl"]=avaTitleUrl;
    json["startTime"]= startTime.toString();
    json["endTime"]= endTime.toString();
    QJsonDocument doc(json);
    QString jsonString = doc.toJson();
    return jsonString;
}
//сделать тут обработку события нажатия на иконку курса для главной страницы
void Course::ClickIcon()
{

}
