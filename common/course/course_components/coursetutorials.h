#ifndef COURSETUTORIALS_H
#define COURSETUTORIALS_H

#include "coursecomponent.h"
#include <QJsonObject>
#include <QJsonDocument>
class CourseTutorials : public CourseComponent
{
public:
    explicit CourseTutorials(int32_t id, int32_t order,QString content, QObject *parent = nullptr);

    QString Serialize();

    static CourseTutorials Deserialize(QString jsonString);

    QString getContent() const;

private:
    QString content;

public slots:
    void ClickIcon() override;
};

#endif // COURSETUTORIALS_H
