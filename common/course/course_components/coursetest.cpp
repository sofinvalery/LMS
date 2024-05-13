#include "coursetest.h"
#include "../../../client/Forms/CoursePageComponents/CourseAttestacion/courseattestacion.h"



CourseTest::CourseTest(int32_t id, int32_t order, QString title, int32_t maxMark,
                       QString urlJson, int32_t timeInSeconds, int32_t verdict,
                       QString notes,QDate time,int32_t testSize, QList<Question*> listQuestions, QObject *parent)
    :CourseComponent(id,order,parent)
{
    this->testSize=testSize;
    this->title=title;
    this->maxMark=maxMark;
    this->urlJson=urlJson;
    this->timeInSeconds=timeInSeconds;
    this->verdict=verdict;
    this->notes=notes;
    this->listQuestions=listQuestions;
    this->time=time;
    this->testSize = testSize;
}

QString CourseTest::getTitle() const
{
    return title;
}

int32_t CourseTest::getMaxMark() const
{
    return maxMark;
}

QString CourseTest::getUrlJson() const
{
    return urlJson;
}

int32_t CourseTest::getTimeInSeconds() const
{
    return timeInSeconds;
}

int32_t CourseTest::getVerdict() const
{
    return verdict;
}

QString CourseTest::getNotes() const
{
    return notes;
}

QList<Question*> CourseTest::getListQuestions() const
{
    return listQuestions;
}

QJsonObject CourseTest::Serialize()
{
    QJsonObject json;
    json["id"]=id;
    json["title"]=title;
    json["maxMark"]=maxMark;
    json["order"]=order;
    json["timeInSeconds"]= timeInSeconds;
    json["notes"]= notes;
    json["testSize"]= testSize;
    json["urlJson"]=urlJson;
    json["time"]=time.toString("yyyy.MM.dd");
    json["verdict"]= verdict;
    json["testSize"]= testSize;
    QJsonObject main;
    main["CourseTest"]=json;
    return main;
}

CourseTest* CourseTest::Deserialize(QJsonObject json)
{
    QJsonObject jsonObj=json["CourseTest"].toObject();
    QDate solutionTime=QDate::fromString(jsonObj["time"].toString(),"yyyy.MM.dd");
    return new CourseTest(jsonObj["id"].toInt(),jsonObj["order"].toInt(),
                     jsonObj["title"].toString(),jsonObj["maxMark"].toInt(),
                     jsonObj["urlJson"].toString(),jsonObj["timeInSeconds"].toInt(),
                      jsonObj["verdict"].toInt(),jsonObj["notes"].toString(),solutionTime,jsonObj["testSize"].toInt());
}

QJsonObject CourseTest::SerializeQuestionList()
{
    QJsonObject json;
    QJsonArray questions;
    for (auto & user : listQuestions)
        questions.append(user->Serialize());
    json["listQuestions"]=questions;
    json["TestId"]=id;
    //QJsonDocument doc(json);
    //QString jsonString = doc.toJson();
    return json;
}

void CourseTest::DeserializeQuestionList(QJsonObject jsonObj)
{
    for(auto temp:listQuestions)
        delete temp;
    listQuestions.clear();
    QJsonArray questions=jsonObj["listQuestions"].toArray();
    for(int i=0;i<questions.size();i++)
        listQuestions.append(Question::Deserialize(questions[i].toObject()));
}

QDate CourseTest::getTime() const
{
    return time;
}

int32_t CourseTest::getTestSize() const
{
    return testSize;
}

void CourseTest::setTitle(const QString &newTitle)
{
    title = newTitle;
}

void CourseTest::setMaxMark(int32_t newMaxMark)
{
    maxMark = newMaxMark;
}

void CourseTest::setTimeInSeconds(int32_t newTimeInSeconds)
{
    timeInSeconds = newTimeInSeconds;
}

void CourseTest::setTestSize(int32_t newTestSize)
{
    testSize = newTestSize;
}

void CourseTest::setVerdict(int32_t newVerdict)
{
    verdict = newVerdict;
}
