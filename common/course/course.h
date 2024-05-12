#ifndef COURSE_H
#define COURSE_H

#include <QDate>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include "course_components/coursecomponent.h"
#include "course_components/coursemediafiles.h"
#include "course_components/coursetask.h"
#include "course_components/coursetest.h"
#include "course_components/coursetutorials.h"
class Course : public QObject
{
    Q_OBJECT
public:
    explicit Course(int32_t id, QString title, QString avaUrl, QDate start, QDate end,
                    int32_t sumpoints=0,int32_t maxSumpoints=0,QObject *parent = nullptr);
    ~Course();
private:
    int32_t id;
    QString title;
    QString avaTitleUrl;
    QDate startTime;
    QDate endTime;
    int32_t sumpoints;
    int32_t maxSumpoints;
    QList<CourseComponent*> listComponents = QList<CourseComponent*>();
public:
    void CreateDir(int32_t id);
    void AddCourseComponent(CourseComponent* component, int position){
        listComponents.insert(position, component);
    }

    void DeleteCourseComponent(int position){
        listComponents.removeAt(position);
    }

    QJsonObject SerializeListComponents();

    static QJsonObject SerializeListComponents(int32_t courseId, QList<CourseComponent*> listComponents);

    void DeserializeListComponents(QJsonObject jsonObj);

    static QList<CourseComponent*> DeserializeListComponentsCourse(QJsonObject jsonObj);

    static Course* Deserialize(QJsonObject jsonObj, bool IsNewCourse=false);

    QJsonObject Serialize();

    uint32_t GetCourseId(){return id;}

    QString GetTitle(){return title;}

    QString GetAvaTitleUrl(){return avaTitleUrl;}

    QDate GetStartTime() { return startTime; }

    QDate GetEndTime() { return endTime; }

    int32_t GetPoints() { return sumpoints; }

    QList<CourseComponent *>& getListComponents();

    int32_t getSumpoints() const;

    int32_t getMaxSumpoints() const;
    QString moveImageNewCourseToStandartName(int32_t id);
    void setListComponents(const QList<CourseComponent *> &newListComponents);

public slots:
    void ClickIcon();
    QWidget* QWidgetShow();
signals:
};

#endif // COURSE_H
