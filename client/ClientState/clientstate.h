#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

#include <QObject>
#include "../../common/authentication/authentication.h"
#include "../../common/course/course.h"
#include "../Forms/Main/mainwindow.h"
#include "../../common/authentication/group.h"

class ClientState : public QObject
{
    Q_OBJECT
private:
    explicit ClientState(QObject *parent = nullptr);

    QList<Course*> currentListCourses;

    Authentication* auth=nullptr;

    QList<Group*> groups;

    static ClientState* s_Instance;

    MainWindow* mainwindow = new MainWindow();

private slots:



public:
    static ClientState* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new ClientState()); }

    void setAuth(Authentication *newAuth);

    Authentication *getAuth() const;

    QList<Course *> getListCourses() const;

    void setListCourses(const QList<Course *> &newListCourses);

    MainWindow* getMainwindow() const;

    QList<Group *> getGroups() const;
    void setGroups(const QList<Group *> &newGroups);

signals:
   void DataReady();
};

#endif // CLIENTSTATE_H
