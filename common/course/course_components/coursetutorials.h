#ifndef COURSETUTORIALS_H
#define COURSETUTORIALS_H

#include "coursecomponent.h"
#include <QJsonObject>
#include <QJsonDocument>
class CourseTutorials : public CourseComponent
{
    Q_OBJECT
public:
    explicit CourseTutorials(int32_t id, int32_t order,QString content, QObject *parent = nullptr);

    QJsonObject Serialize() override;

    static CourseTutorials* Deserialize(QJsonObject jsonObj);

    QString getContent() const;

    QString getType() override { return "CourseTutorials"; }

    int32_t getOrder() { return order; }

    ~CourseTutorials(){}

private:
    QString content;
};

#endif // COURSETUTORIALS_H
