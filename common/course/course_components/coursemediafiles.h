#ifndef COURSEMEDIAFILES_H
#define COURSEMEDIAFILES_H

#include <QObject>
#include "coursecomponent.h"
#include <QJsonObject>
#include <QJsonDocument>

enum TypeFile{
    PDF=1,
    VIDEO=2,
};

class CourseMediaFiles : public CourseComponent
{
    Q_OBJECT
public:
    explicit CourseMediaFiles(int32_t id, int32_t order, QString title, QString url,TypeFile typeFile,QObject *parent = nullptr);

    TypeFile getTypeFile() const;

    QString getTitle() const;

    QString getUrl() const;

    QJsonObject Serialize() override;

    static CourseMediaFiles* Deserialize(QJsonObject jsonObj);

private:
    QString title;
    QString url;
    TypeFile typeFile;
public slots:
    void ClickIcon() override;
    QWidget* QWidgetShow() override;
};

#endif // COURSEMEDIAFILES_H
