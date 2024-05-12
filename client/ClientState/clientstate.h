#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

#include <QObject>
#include "../../common/authentication/authentication.h"
#include "../../common/course/course.h"
#include "../Forms/Main/mainwindow.h"
#include "../../common/authentication/group.h"
#include "Forms/Reconnect/reconnect.h"
#include"Forms/Notification/notification.h"

class ClientState : public QObject
{
    Q_OBJECT
private:
    explicit ClientState(QObject *parent = nullptr);

    QList<Course*> currentListCourses;

    Authentication* auth=nullptr;

    Group* group=nullptr;

    QList<QString> groupsName;

    QList<QString> potoksName;

    static ClientState* s_Instance;

    MainWindow* mainwindow = new MainWindow();

    Reconnect* rec = new Reconnect();

private slots:

    void ShowRec();

    void Notificate(QString notification, QString colour){
        Notification* notif = new Notification(nullptr,notification,colour);
        notif->show();
    }

public:
    static ClientState* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new ClientState()); }

    void setAuth(Authentication *newAuth);

    Authentication *getAuth() const;

    QList<Course *> getListCourses() const;

    void setListCourses(const QList<Course *> &newListCourses);

    MainWindow* getMainwindow() const;

    Group *getGroup() const;
    void setGroup(Group *newGroups);

    QList<QString> getGroupsName() const;
    void setGroupsName(const QList<QString> &newGroupsName);

    QList<QString> getPotoksName() const;
    void setPotoksName(const QList<QString> &newPotoksName);

    Reconnect *getRec() const;

    void ShowReconnect();

    void ShowNotifacate(QString notification, QString colour){
        emit ShowingNotification(notification,colour);
    }


signals:
   void DataReady();
    void ShowReconection();
   void ShowingNotification(QString notification, QString colour);
};

#endif // CLIENTSTATE_H
