#include "clientstate.h"



ClientState* ClientState::s_Instance = nullptr;


ClientState::ClientState(QObject *parent)
    : QObject{parent}
{
    connect(this,SIGNAL(ShowReconection()),this,SLOT(ShowRec()));
}

void ClientState::ShowRec()
{
    rec->setModal(true);
    rec->raise();
    rec->show();
}

Reconnect *ClientState::getRec() const
{
    return rec;
}

void ClientState::ShowReconnect()
{
    emit ShowReconection();
}

QList<QString> ClientState::getPotoksName() const
{
    return potoksName;
}

void ClientState::setPotoksName(const QList<QString> &newPotoksName)
{
    potoksName = newPotoksName;
}

QList<QString> ClientState::getGroupsName() const
{
    return groupsName;
}

void ClientState::setGroupsName(const QList<QString> &newGroupsName)
{
    groupsName = newGroupsName;
}

Group *ClientState::getGroup() const
{
    return group;
}

void ClientState::setGroup(Group *newGroup)
{
    group = newGroup;
}

MainWindow* ClientState::getMainwindow() const
{
    return mainwindow;
}

void ClientState::setListCourses(const QList<Course *> &newListCourses)
{
    currentListCourses.clear();
    currentListCourses = newListCourses;
}

QList<Course *> ClientState::getListCourses() const
{
    return currentListCourses;
}

Authentication *ClientState::getAuth() const
{
    return auth;
}

void ClientState::setAuth(Authentication *newAuth)
{
    if(auth!=nullptr)
        delete auth;
    auth = newAuth;
}
