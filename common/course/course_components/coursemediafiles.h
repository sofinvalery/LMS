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

    QString getType() override { return "CourseMediaFiles"; }

    int32_t getOrder() { return order; }

    static CourseMediaFiles* Deserialize(QJsonObject jsonObj);
    ~CourseMediaFiles(){};
private:
    QString title;
    QString url;
    TypeFile typeFile;
};

#endif // COURSEMEDIAFILES_H
