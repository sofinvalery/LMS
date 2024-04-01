#include "servertask.h"

ServerTask::ServerTask(QJsonObject json, Authentication* auth, QObject *parent)
    : QObject{parent}
{
    this->json=json;
    this->auth=auth;
}


void ServerTask::run()
{
    emit Result(jsonManager(json,auth));
}
