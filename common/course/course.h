#ifndef COURSE_H
#define COURSE_H
#include <QDate>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class Course : public QObject
{
    Q_OBJECT
public:
    explicit Course(int32_t id, QString title, QString avaUrl, QDate start, QDate end,QObject *parent = nullptr);
private:
    int32_t id;
    QString title;
    QString avaTitleUrl;
    QDate startTime;
    QDate endTime;
public:
    static Course Deserialize(QString jsonString);
    QString Serialize();
    uint32_t GetCourseId(){return id;}
    QString GetTitle(){return title;}
    QString GetAvaTitleUrl(){return avaTitleUrl;}
signals:
};

#endif // COURSE_H
