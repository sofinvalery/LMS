#include "coursetask.h"
#include "../../../client/Forms/CoursePageComponents/CourseDz/coursedz.h"

CourseTask::CourseTask(int32_t id,int32_t order, QString content, int32_t maxMark,
                       int32_t memoryLimit,
                       QString allowedTypeOfFiles, QString answerUrl,
                       QDate solutionTime, int32_t verdict,
                       QString notes, QObject *parent)
    : CourseComponent(id,order, parent)
{
    this->content=content;
    this->maxMark=maxMark;
    this->memoryLimit=memoryLimit;
    this->allowedTypeOfFiles=allowedTypeOfFiles;
    this->answerUrl=answerUrl;
    this->solutionTime=solutionTime;
    this->verdict=verdict;
    this->notes=notes;
}
//по нажатию тут передадим данные в новую форму запрос к серверу и т.д
void CourseTask::ClickIcon()
{

}

QWidget *CourseTask::QWidgetShow()
{
 return new CourseDz(this);
}

QJsonObject CourseTask::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["content"]=content;
    json["maxMark"]=maxMark;
    json["order"]=order;
    json["memoryLimit"]= memoryLimit;
    json["allowedTypeOfFiles"]= allowedTypeOfFiles;
    json["answerUrl"]= answerUrl;
    json["solutionTime"]= solutionTime.toString();
    json["verdict"]= verdict;
     json["notes"]= notes;
    QJsonObject main;
     main["CourseTask"]=json;
    return main;
}

CourseTask* CourseTask::Deserialize(QJsonObject json)
{
    QJsonObject jsonObj=json["CourseTask"].toObject();

    QDate solutionTime;
    solutionTime.fromString(jsonObj["solutionTime"].toString(),"dd/MM/YYYY");
    return new CourseTask(jsonObj["id"].toInt(),jsonObj["order"].toInt(),jsonObj["content"].toString(),
                      jsonObj["maxMark"].toInt(),jsonObj["memoryLimit"].toInt(),
                      jsonObj["allowedTypeOfFiles"].toString(),jsonObj["answerUrl"].toString(),
                      solutionTime,jsonObj["verdict"].toInt(),jsonObj["notes"].toString());
}


QString CourseTask::getNotes() const
{
    return notes;
}

int32_t CourseTask::getVerdict() const
{
    return verdict;
}

QDate CourseTask::getSolutionTime() const
{
    return solutionTime;
}

QString CourseTask::getAnswerUrl() const
{
    return answerUrl;
}

QString CourseTask::getAllowedTypeOfFiles() const
{
    return allowedTypeOfFiles;
}

int32_t CourseTask::getMemoryLimit() const
{
    return memoryLimit;
}

int32_t CourseTask::getMaxMark() const
{
    return maxMark;
}

QString CourseTask::getContent() const
{
    return content;
}



