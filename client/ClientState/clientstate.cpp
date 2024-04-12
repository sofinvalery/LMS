#include "clientstate.h"



ClientState* ClientState::s_Instance = nullptr;


ClientState::ClientState(QObject *parent)
    : QObject{parent}
{}

QList<Group *> ClientState::getGroups() const
{
    return groups;
}

void ClientState::setGroups(const QList<Group *> &newGroups)
{
    for(auto temp:groups)
        delete temp;
    groups.clear();
    groups = newGroups;
}

MainWindow* ClientState::getMainwindow() const
{
    return mainwindow;
}

void ClientState::setListCourses(const QList<Course *> &newListCourses)
{
    for(auto temp:currentListCourses)
        delete temp;
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
