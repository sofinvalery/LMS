#include "coursetask.h"
#include "../../../client/Forms/CoursePageComponents/CourseDz/coursedz.h"

CourseTask::CourseTask(int32_t id,int32_t order,QString content, int32_t maxMark,
                       int32_t memoryLimit,
                       QString allowedTypeOfFiles, QString answerUrl,
                       QDate solutionTime, int32_t verdict,
                       QString notes, QString title, QObject *parent)
    : CourseComponent(id,order, parent)
{
    this->title = title;
    this->content=content;
    this->maxMark=maxMark;
    this->memoryLimit=memoryLimit;
    this->allowedTypeOfFiles=allowedTypeOfFiles;
    this->answerUrl=answerUrl;
    this->solutionTime=solutionTime;
    this->verdict=verdict;
    this->notes=notes;
}

QJsonObject CourseTask::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["content"]=content;
    json["maxMark"]=maxMark;
    json["order"]=order;
    json["title"]=title;
    json["memoryLimit"]= memoryLimit;
    json["allowedTypeOfFiles"]= allowedTypeOfFiles;
    json["answerUrl"]= answerUrl;
    json["solutionTime"]= solutionTime.toString("yyyy.MM.dd");
    json["verdict"]= verdict;
    json["notes"]= notes;
    QJsonObject main;
     main["CourseTask"]=json;
    return main;
}

CourseTask* CourseTask::Deserialize(QJsonObject json)
{
    QJsonObject jsonObj=json["CourseTask"].toObject();

    QDate solutionTime =QDate::fromString(jsonObj["solutionTime"].toString(),"yyyy.MM.dd");
    return new CourseTask(jsonObj["id"].toInt(),jsonObj["order"].toInt(),jsonObj["content"].toString(),
                      jsonObj["maxMark"].toInt(),jsonObj["memoryLimit"].toInt(),
                      jsonObj["allowedTypeOfFiles"].toString(),jsonObj["answerUrl"].toString(),
                      solutionTime,jsonObj["verdict"].toInt(),jsonObj["notes"].toString(),jsonObj["title"].toString());
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

void CourseTask::setContent(const QString &newContent)
{
    content = newContent;
}

void CourseTask::setMaxMark(int32_t newMaxMark)
{
    maxMark = newMaxMark;
}

void CourseTask::setAllowedTypeOfFiles(const QString &newAllowedTypeOfFiles)
{
    allowedTypeOfFiles = newAllowedTypeOfFiles;
}

void CourseTask::setTitle(const QString &newTitle)
{
    title = newTitle;
}

void CourseTask::setVerdict(int32_t newVerdict)
{
    verdict = newVerdict;
}



