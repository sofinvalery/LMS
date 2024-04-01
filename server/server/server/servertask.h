#ifndef SERVERTASK_H
#define SERVERTASK_H

#include <QObject>
#include <QRunnable>
#include<QJsonObject>
#include "../jsonManager/jsonmanager.h"
#include "../../common/authentication/authentication.h"

class ServerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ServerTask(QJsonObject json, Authentication* auth,QObject *parent=nullptr);

signals:
    void Result(QJsonObject json);
private:
    QJsonObject json;
    Authentication* auth;
protected:
    void run();
};

#endif // SERVERTASK_H
