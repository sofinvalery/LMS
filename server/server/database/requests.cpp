#include "databasemanager.h"
#include "../../common/authentication/authentication.h"


QList<Course*> DatabaseManager::Login(Authentication* auth) {
    QSqlQuery query;
    query.prepare("");

    query.bindValue(":login", auth->GetLogin());
    query.bindValue(":password", auth->GetPassword());

    QVariant userId = getScalarValue(query.executedQuery());
    QList<Course*> courses;
    if (userId.isValid()) {

        QString fullName = query.value("full_name").toString();
        QString avatarUrl = query.value("avatar_url").toString();
        EnumRoles userRole = EnumRoles(query.value("role").toInt());
        int32_t userId = query.value("id").toInt();

        auth->SetInformationAfterAuthentication(fullName, avatarUrl, userRole, userId);

        /*QSqlQuery courseQuery;
        courseQuery.prepare("");
        courseQuery.bindValue(":userId", (int32_t )userId.toInt());
        QSqlQuery result = executeQuery(courseQuery.executedQuery());

        while (result.next()) {
            int courseId = result.value("id").toInt();
            QString title = result.value("title").toString();
            QString avaUrl = result.value("avaUrl").toString();
            QDate start = result.value("start").toDate();
            QDate end = result.value("end").toDate();
            int sumpoints = result.value("sumpoints").toInt();

            Course* course= new Course(courseId, title, avaUrl, start, end, sumpoints);
            courses.append(course);
        }
        return courses;
    } else {
        auth->setIsAuthenticated(false);
        return courses;*/
        return GetMainPage(auth);
    }
}

QList<Course*> DatabaseManager::GetMainPage(Authentication* auth) {
    QSqlQuery query;
    query.prepare("");

    QList<Course*> courses;
    QSqlQuery result = executeQuery(query.executedQuery());

    while (result.next()) {
        int courseId = result.value("id").toInt();
        QString title = result.value("title").toString();
        QString avaUrl = result.value("avaUrl").toString();
        QDate start = result.value("start").toDate();
        QDate end = result.value("end").toDate();
        int sumpoints = result.value("sumpoints").toInt();

        Course* course = new Course(courseId, title, avaUrl, start, end, sumpoints);
        courses.append(course);
    }

    return courses;
}


