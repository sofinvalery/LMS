#include "course.h"



Course::Course(int32_t id, QString title, QString avaUrl, QDate start, QDate end,int32_t sumpoints, QObject *parent): QObject{parent}
{
    this->id=id;
    this->title=title;
    this->avaTitleUrl=avaUrl;
    this->startTime=start;
    this->endTime=end;
    this->sumpoints=sumpoints;
}

int32_t Course::getSumpoints() const
{
    return sumpoints;
}

QList<CourseComponent *> Course::getListComponents() const
{
    return listComponents;
}

QJsonObject Course::SerializeListComponents()
{
    QJsonObject json;
    QJsonArray components;
    for (auto & user : listComponents)
        components.append(user->Serialize());
    json["listComponents"]=components;
    json["CourseId"]=id;
    //QJsonDocument doc(json);
    //QString jsonString = doc.toJson();
    return json;
}
//тут надо прям потестить будет хорошо
void Course::DeserializeListComponents(QJsonObject jsonObj)
{
    listComponents.clear();
    QJsonArray questions=jsonObj["listComponents"].toArray();
    for(int i=0;i<questions.size();i++)
    {
        QString s=questions[i].toObject().keys()[0];
        if(s=="CoursePdf")
            listComponents.append(CoursePdf::Deserialize(questions[i].toObject()));
        if(s=="CourseTask")
            listComponents.append(CourseTask::Deserialize(questions[i].toObject()));
        if(s=="CourseTest")
            listComponents.append(CourseTest::Deserialize(questions[i].toObject()));
        if(s=="CourseTutorials")
            listComponents.append(CourseTutorials::Deserialize(questions[i].toObject()));
        if(s=="CourseVideos")
            listComponents.append(CourseVideos::Deserialize(questions[i].toObject()));
    }
}

Course Course::Deserialize(QJsonObject jsonObj)
{
    QDate start;
    start.fromString(jsonObj["startTime"].toString(),"dd/MM/YYYY");
    QDate end;
    end.fromString(jsonObj["endTime"].toString(),"dd/MM/YYYY");
    return Course(jsonObj["id"].toInt(),jsonObj["title"].toString(),jsonObj["avaTitleUrl"].toString(),start,end,jsonObj["sumpoints"].toInt());
}

QJsonObject Course::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["title"]=title;
    json["avaTitleUrl"]=avaTitleUrl;
    json["startTime"]= startTime.toString();
    json["endTime"]= endTime.toString();
    json["sumpoints"]=sumpoints;
    return json;
}
//сделать тут обработку события нажатия на иконку курса для главной страницы
void Course::ClickIcon()
{

}

QWidget *Course::QWidgetShow()
{
    return new QTextEdit();
}
