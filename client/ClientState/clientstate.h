#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

#include <QObject>
#include "../../common/authentication/authentication.h"
#include "../../common/course/course.h"


class ClientState : public QObject
{
    Q_OBJECT
private:
    explicit ClientState(QObject *parent = nullptr);

    QList<Course*> currentListCourses;

    Authentication* auth=nullptr;

    static ClientState* s_Instance;

private slots:



public:
    static ClientState* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new ClientState()); }

    void setAuth(Authentication *newAuth);

    Authentication *getAuth() const;

    QList<Course *> getListCourses() const;

    void setListCourses(const QList<Course *> &newListCourses);

signals:
   void DataReady();
};

#endif // CLIENTSTATE_H
