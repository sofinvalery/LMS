#ifndef SOCKETPARSER_H
#define SOCKETPARSER_H

#include <QObject>
#include "../../common/transferEnum/transferEnum.h"
#include "../../common/authentication/authentication.h"
#include "../../common/course/course.h"
#include "../ClientState/clientstate.h"
#include "../ClientManager/clientmanager.h"
#include<QJsonObject>

class SocketParser : public QObject
{
    Q_OBJECT
private slots:
    void socketparse(QJsonObject json);
private:
    explicit SocketParser(QObject *parent = nullptr);
    void logining(QJsonObject json);
    void getMainPage(QJsonObject json);
    void getAddPotok(QJsonObject json);
    void getAddGroup(QJsonObject json);
    void getAddCourse(QJsonObject json);
    void getEditGroup(QJsonObject json);
    void getGroup(QJsonObject json);
    void getCourseComponents(QJsonObject json);
    void getScore(QJsonObject json);
    void showTeacherScore(QJsonObject json);
    void getSubmit(QJsonObject json);
    static SocketParser* s_Instance;
public:
    static SocketParser* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new SocketParser()); }
signals:
    void logined();
    void getMainPage();
    void getAddPotok();
    void getAddGroup();
    void getAddCourse();
    void getEditGroup();
    void getShowEditGroup();
    void getCourseComponents(Course*);
    void getScore();
    void showTeacherScore();
    void getSubmit(QList<Submit *>submits, Group* group);
};

#endif // SOCKETPARSER_H
