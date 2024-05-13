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
#include "../../common/transferEnum/transferEnum.h"
#include <QUuid>
#include <QThreadStorage>

class DatabaseManager {
public:
    DatabaseManager();
    //функции выполняющие запросы
    bool Login(Authentication* auth);

    QList<Course*> GetMainPage(Authentication* auth);
    QList<CourseComponent*>* GetCourseComponents(int32_t courseId,Authentication* auth);
    QString GetTestQuestion(int32_t testId);
    QList<QString> GetEveryGroupName();
    QList<QString> GetEveryUnionName();
    bool AddNewGroup(Group*);
    bool AddGroupsToUnion(QList<QString> groupsList, QString unionName);
    bool AddNewCourse(QString teachersGroupName, QString unionName, Course* course);
    bool UpdateGroup(Group* group);
    QList<QString> GetAllStudentGroupName();
    QList<QString> GetEveryTeacherGroupName();
    Group* GetGroupByName(QString groupName);
    bool SetCourseTutorial(CourseTutorials* tutorial, int32_t courseId);
    bool SetCourseMediaFiles(CourseMediaFiles* mediaFiles, int32_t courseId);
    bool SetCourseTasks(CourseTask* tasks, int32_t courseId);
    bool SetCourseTests(CourseTest* tests, int32_t courseId);
    bool DeleteCourseMedia(int32_t courseMediaId, int32_t courseId);
    bool DeleteCourseTutorial(int32_t courseTutorialId, int32_t courseId);
    bool DeleteCourseTask(int32_t courseTaskId, int32_t courseId);
    bool DeleteCourseTest(int32_t courseTaskId, int32_t courseId);
    bool EditCourseMediaFiles(CourseMediaFiles* mediaFiles);
    bool EditCourseTutorial(CourseTutorials* tutorials);
    bool EditCourseTask(CourseTask* task);
    bool EditCourseTest(CourseTest* test);
    QList<QString>GetGroupsOfStudentByCourseId(int32_t courseId);
    QList<Submit*> GetTestSubmits(int32_t courseId);
    QList<Submit*> GetTaskSubmits(int32_t courseId);
    bool AddStudentTaskSubmit(Submit* submit);
    QList<Submit*> GetUncheckedTaskSubmitsFromCourse(int32_t path_course_tasks_id);
    bool UpdateCheckedTaskSubmit(Submit* task);
    bool SetTestSubmits(QList<Submit*> submits);
    bool SetTaskSubmits(QList<Submit*> submits);

    ~DatabaseManager();

private:
    bool createConnection();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
