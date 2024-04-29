#ifndef COURSEVIDEOS_H
#define COURSEVIDEOS_H

#include "coursecomponent.h"
#include <QJsonObject>
#include <QJsonDocument>

class CourseVideos : public CourseComponent
{
    Q_OBJECT
public:
    explicit CourseVideos(int32_t id, int32_t order, QString title, QString url,QObject *parent = nullptr);


    QString getTitle() const;

    QString getUrl() const;

    QJsonObject Serialize() override;

    static CourseVideos* Deserialize(QJsonObject jsonObj);

    QString getType() override{
        return "CourseVideos";
    }

private:
    QString title;
    QString url;
};

#endif // COURSEVIDEOS_H
