#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include "authentication.h"
#include <QJsonObject>

class Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(int32_t id, QString classname, bool isTeacherGroup,  QList<Authentication*> participants=QList<Authentication*>(), QObject *parent = nullptr);
    int32_t getId() const;

    QString getClassname() const;

    bool getIsTeacherGroup() const;

    QList<Authentication *> getParticipants() const;

    QJsonObject Serialize();

    static Group* Deserialize(QJsonObject jsonObj);

private:
    int32_t id;
    QString classname;
    bool isTeacherGroup;
    QList<Authentication*> participants;
signals:
};

#endif // GROUP_H
