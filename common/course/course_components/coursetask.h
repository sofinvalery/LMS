#ifndef COURSETASK_H
#define COURSETASK_H
#include <QDate>
#include "coursecomponent.h"
#include <QJsonObject>
#include <QJsonDocument>
class CourseTask : public CourseComponent
{
    Q_OBJECT
public:
    explicit CourseTask(int32_t id,int32_t order, QString content, int32_t maxMark,
                        int32_t memoryLimit,
                        QString allowedTypeOfFiles, QString answerUrl, QDate solutionTime,
                        int32_t verdict, QString notes, QString title = "", QObject *parent = nullptr);

    QJsonObject Serialize() override;

    static CourseTask* Deserialize(QJsonObject jsonObj);

    QString getTitle() const {return title;}

    QString getNotes() const;

    int32_t getVerdict() const;

    QDate getSolutionTime() const;

    QString getAnswerUrl() const;

    QString getAllowedTypeOfFiles() const;

    int32_t getMemoryLimit() const;

    int32_t getMaxMark() const;

    QString getContent() const;

    QString getType() override { return "CourseTask"; }

    ~CourseTask(){};

    void setContent(const QString &newContent);

    void setMaxMark(int32_t newMaxMark);

    void setAllowedTypeOfFiles(const QString &newAllowedTypeOfFiles);

    void setTitle(const QString &newTitle);

    void setVerdict(int32_t newVerdict);

    void setAnswerUrl(const QString &newAnswerUrl);

    void setNotes(const QString &newNotes);

private:
    QString content;
    int32_t maxMark;
    int32_t memoryLimit;
    QString allowedTypeOfFiles;
    QString answerUrl;
    QDate solutionTime;
    int32_t verdict;
    QString notes;
    QString title;
};

#endif // COURSETASK_H
