#include "course.h"


Course::Course(int32_t id, QString title, QString avaUrl, QDate start, QDate end,
               int32_t sumpoints,int32_t maxSumpoints, QObject *parent): QObject{parent}
{
    this->id=id;
    this->title=title;
    this->avaTitleUrl=avaUrl;
    this->startTime=start;
    this->endTime=end;
    this->sumpoints=sumpoints;
    this->maxSumpoints=maxSumpoints;
}

Course::~Course()
{
    for(CourseComponent* temp:listComponents)
    {
        delete temp;
    }
}

void Course::setListComponents(const QList<CourseComponent *> &newListComponents)
{
    listComponents = newListComponents;
}

int32_t Course::getMaxSumpoints() const
{
    return maxSumpoints;
}

QString Course::moveImageNewCourseToStandartName(int32_t id)
{
    QString path="";
    if(avaTitleUrl!=":/img/resources/kap.jpg")
    {
        path="./data/Courses/"+QString::number(id)+".jpg";
        QFile file (avaTitleUrl);
        file.rename(path);
    }
    return path;
}

int32_t Course::getSumpoints() const
{
    return sumpoints;
}

QList<CourseComponent *>& Course::getListComponents()
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
    for(auto temp:listComponents)
        delete temp;
    listComponents.clear();
    QJsonArray questions=jsonObj["listComponents"].toArray();
    for(int i=0;i<questions.size();i++)
    {
        QString s=questions[i].toObject().keys()[0];
        if(s=="CourseMediaFiles")
            listComponents.append(CourseMediaFiles::Deserialize(questions[i].toObject()));
        if(s=="CourseTask")
            listComponents.append(CourseTask::Deserialize(questions[i].toObject()));
        if(s=="CourseTest")
            listComponents.append(CourseTest::Deserialize(questions[i].toObject()));
        if(s=="CourseTutorials")
            listComponents.append(CourseTutorials::Deserialize(questions[i].toObject()));
    }
}

Course* Course::Deserialize(QJsonObject jsonObj, bool IsNewCourse)
{
    QString latin = jsonObj["avaTitleUrl"].toString();
    QString url;
    if(!latin.isEmpty())
    {
        if(IsNewCourse)
        {
            url="./data/Courses/"+QString::number(QDateTime::currentMSecsSinceEpoch())+".jpg";
        }
        else{
            url="./data/Courses/"+QString::number(jsonObj["id"].toInt())+".jpg";
        }
        QFile file (url);
    if (file.open(QIODevice::WriteOnly))
        file.write(QByteArray::fromBase64( latin.toLatin1()));
    }
    else
    {
        url=":/img/resources/kap.jpg";
    }

    QDate start=QDate::fromString(jsonObj["startTime"].toString(),"yyyy.MM.dd");
    QDate end = QDate::fromString(jsonObj["endTime"].toString(),"yyyy.MM.dd");
    return new Course(jsonObj["id"].toInt(),jsonObj["title"].toString(),
                      url,start,end,jsonObj["sumpoints"].toInt(),jsonObj["maxSumpoints"].toInt());
}

QJsonObject Course::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["title"]=title;
    QByteArray data;
    data.clear();
    if(avaTitleUrl!=""&&avaTitleUrl!=":/img/resources/kap.jpg")
    {
    QFile file (avaTitleUrl);
    data.clear();
    if (file.open(QIODevice::ReadOnly))
        data = file.readAll();
    }
    json["avaTitleUrl"]=QLatin1String(data.toBase64());
    json["startTime"]= startTime.toString("yyyy.MM.dd");
    json["endTime"]= endTime.toString("yyyy.MM.dd");
    json["sumpoints"]=sumpoints;
    json["maxSumpoints"]=maxSumpoints;
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
