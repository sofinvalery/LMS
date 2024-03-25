#include "databasemanager.h"


QList<Course*> DatabaseManager::Login(Authentication* auth) {
    QSqlQuery query;
    query.prepare("");

    // Bind parameters
    query.bindValue(":login", auth->GetLogin());
    query.bindValue(":password", auth->GetPassword());

    // Execute the query
    QVariant userId = getScalarValue(query.executedQuery());
    QList<Course*> courses;
    if (userId.isValid()) {


        QSqlQuery courseQuery;
        courseQuery.prepare("");
        courseQuery.bindValue(":userId", userId.toInt());
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
        return courses;
    }
}
