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
#include "../../common/course/course.h"
#include "../../common/course/course_components/coursetest.h"


class DatabaseManager {
public:
    static DatabaseManager* getInstance();
    //функции выполняющие запросы
    QList<Course*> Login(Authentication* auth);
    QList<Course*> GetMainPage(Authentication* auth);
    void GetCourseComponents(Course* course);
    QString GetTestQuestion(int32_t testId);
    //bool SetNewGroupStudents(QList<Authentication*> listAuths, .....) //тут будет еще что то потом придумаю
    //тут скорее всего будет не bool я еще почитаю как лучше реализовать обновление этих штук
    bool SetNewTest(CourseTest* test);
    bool SetNewCourse(Course* course);


private:
    ~DatabaseManager();

    bool createConnection();
    QSqlQuery executeQuery(const QString& query);
    QVariant getScalarValue(const QString& query);
    QList<QVariantMap> getQueryResults(const QString& query);
    DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    static DatabaseManager* s_Instance;
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
