#ifndef COURSEPDF_H
#define COURSEPDF_H

#include "coursecomponent.h"
#include <QJsonObject>
#include <QJsonDocument>

class CoursePdf : public CourseComponent
{
    Q_OBJECT
public:
    explicit CoursePdf(int32_t id, int32_t order, QString title, QString url,QObject *parent = nullptr);

    QString getTitle() const;

    QString getUrl() const;

    QJsonObject Serialize() override;

    static CoursePdf* Deserialize(QJsonObject jsonObj);

    QString getType() override{
        return "CoursePdf";
    }

    void setTitle(const QString &newTitle);

    void setUrl(const QString &newUrl);

private:
    QString title;
    QString url;
};

#endif // COURSEPDF_H
