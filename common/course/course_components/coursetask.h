#ifndef COURSETASK_H
#define COURSETASK_H
#include <QDate>
#include "coursecomponent.h"
#include <QJsonObject>
#include <QJsonDocument>
class CourseTask : public CourseComponent
{
public:
    explicit CourseTask(int32_t id,int32_t order, QString content, int32_t maxMark,
                        int32_t memoryLimit,
                        QString allowedTypeOfFiles, QString answerUrl, QDate solutionTime,
                        int32_t verdict, QString notes, QObject *parent = nullptr);

    QString Serialize();

    static CourseTask Deserialize(QString jsonString);

    QString getNotes() const;

    int32_t getVerdict() const;

    QDate getSolutionTime() const;

    QString getAnswerUrl() const;

    QString getAllowedTypeOfFiles() const;

    int32_t getMemoryLimit() const;

    int32_t getMaxMark() const;

    QString getContent() const;

private:
    QString content;
    int32_t maxMark;
    int32_t memoryLimit;
    int32_t order;
    QString allowedTypeOfFiles;
    QString answerUrl;
    QDate solutionTime;
    int32_t verdict;
    QString notes;
public slots:
    void ClickIcon() override;
};

#endif // COURSETASK_H
