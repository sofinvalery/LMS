#ifndef COURSETEST_H
#define COURSETEST_H

#include "coursecomponent.h"
#include "question.h"
#include<QList>
#include <QDate>
class CourseTest : public CourseComponent
{
    Q_OBJECT
public:
    explicit CourseTest(int32_t id, int32_t order, QString title,
                        int32_t maxMark, QString urlJson, int32_t timeInSeconds,
                        int32_t verdict, QString notes,QDate time,int32_t testSize=10, QList<Question*> listQuestions=QList<Question*>(),
                        QObject *parent = nullptr);



    QString getTitle() const;

    int32_t getMaxMark() const;

    QString getUrlJson() const;

    int32_t getTimeInSeconds() const;

    int32_t getVerdict() const;

    QString getNotes() const;

    void AddQuestionToList(Question* question) { listQuestions.append(question); }

    QList<Question*> getListQuestions() const;

    QJsonObject Serialize() override;

    static CourseTest* Deserialize(QJsonObject jsonObj);

    QJsonObject SerializeQuestionList();

    void DeserializeQuestionList(QJsonObject jsonObj);

    QString getType() override { return "CourseTest"; }

    QDate getTime() const;

    int32_t getOrder() { return order; }

    int32_t getTestSize() { return testSize; }

    ~CourseTest() {
        for(auto temp:listQuestions)
            delete temp;
    }
private:
    QString title;
    int32_t maxMark;
    QString urlJson;
    int32_t timeInSeconds;
    int32_t verdict;
    int32_t testSize;
    QString notes;
    QDate time;
    QList<Question*> listQuestions;

};

#endif // COURSETEST_H
