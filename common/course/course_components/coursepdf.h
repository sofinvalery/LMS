#ifndef COURSEPDF_H
#define COURSEPDF_H

#include "coursecomponent.h"
#include <QJsonObject>
#include <QJsonDocument>

class CoursePdf : public CourseComponent
{
public:
    explicit CoursePdf(int32_t id, int32_t order, QString title, QString url,QObject *parent = nullptr);


    QString getTitle() const;

    QString getUrl() const;

    QJsonObject Serialize() override;

    static CoursePdf* Deserialize(QJsonObject jsonObj);

private:
    QString title;
    QString url;

public slots:
    void ClickIcon() override;
    QWidget* QWidgetShow() override;
};

#endif // COURSEPDF_H
