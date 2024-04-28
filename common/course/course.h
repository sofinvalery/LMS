#ifndef COURSE_H
#define COURSE_H

#include <QDate>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "course_components/coursecomponent.h"
#include "course_components/coursepdf.h"
#include "course_components/coursetask.h"
#include "course_components/coursetest.h"
#include "course_components/coursetutorials.h"
#include "course_components/coursevideos.h"
class Course : public QObject
{
    Q_OBJECT
public:
    explicit Course(int32_t id, QString title, QString avaUrl, QDate start, QDate end,
                    int32_t sumpoints,int32_t maxSumpoints,QObject *parent = nullptr);
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

    void AddCourseComponent(CourseComponent* component){
        listComponents.append(component);
    }

    QJsonObject SerializeListComponents();

    void DeserializeListComponents(QJsonObject jsonObj);

    static Course* Deserialize(QJsonObject jsonObj);

    QJsonObject Serialize();

    uint32_t GetCourseId(){return id;}

    QString GetTitle(){return title;}

    QString GetAvaTitleUrl(){return avaTitleUrl;}

    QDate GetStartTime() { return startTime; }

    QDate GetEndTime() { return endTime; }

    int32_t GetPoints() { return sumpoints; }

    QList<CourseComponent *> getListComponents() const;

    int32_t getSumpoints() const;

    int32_t getMaxSumpoints() const;

    void setListComponents(const QList<CourseComponent *> &newListComponents);

public slots:
    void ClickIcon();
    QWidget* QWidgetShow();
signals:
};

#endif // COURSE_H
