#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QSqlQuery>
#include "../../common/authentication/authentication.h"
#include "../../common/authentication/group.h"
#include "../../common/course/course.h"
#include "../../common/course/course_components/coursetest.h"
#include <QUuid>
#include <QThreadStorage>

class DatabaseManager {
public:
    DatabaseManager();
    //функции выполняющие запросы
    bool Login(Authentication* auth);
    QList<Course*> GetMainPage(Authentication* auth);
    void GetCourseComponents(Course* course);
    QString GetTestQuestion(int32_t testId);
    //bool SetNewGroupStudents(QList<Authentication*> listAuths, .....) //тут будет еще что то потом придумаю
    //тут скорее всего будет не bool я еще почитаю как лучше реализовать обновление этих штук
    bool SetNewTest(CourseTest* test);
    bool SetNewCourse(Course* course);
    QList<QString> GetEveryGroupName();
    QList<QString> GetEveryUnionName();
    bool AddNewGroup(Group*);
    bool AddNewUnion(QList<QString> groupsList, QString unionName);
    bool AddNewCourse(QString teachersGroupName, QString unionName, Course* course);
    bool UpdateGroup(Group* group);
    ~DatabaseManager();

private:
    bool createConnection();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
