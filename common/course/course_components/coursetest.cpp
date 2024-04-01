#include "coursetest.h"



CourseTest::CourseTest(int32_t id, int32_t order, QString title, int32_t maxMark,
                       QString urlJson, int32_t timeInSeconds, int32_t verdict,
                       QString notes,QDate time, QList<Question*> listQuestions, QObject *parent)
    :CourseComponent(id,order,parent)
{
    this->title=title;
    this->maxMark=maxMark;
    this->urlJson=urlJson;
    this->timeInSeconds=timeInSeconds;
    this->verdict=verdict;
    this->notes=notes;
    this->listQuestions=listQuestions;
    this->time=time;
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
    json["urlJson"]=urlJson;
    json["time"]=time.toString("yyyy.MM.dd");
    json["verdict"]= verdict;
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
                      jsonObj["verdict"].toInt(),jsonObj["notes"].toString(),solutionTime);
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

//по нажатию тут передадим данные в новую форму запрос к серверу и т.д
void CourseTest::ClickIcon()
{

}

QWidget *CourseTest::QWidgetShow()
{
    return new QTextEdit();
}
