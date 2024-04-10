#include "clientstate.h"



ClientState* ClientState::s_Instance = nullptr;


ClientState::ClientState(QObject *parent)
    : QObject{parent}
{}

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
