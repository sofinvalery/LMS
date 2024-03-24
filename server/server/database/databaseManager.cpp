#include "databasemanager.h"
#include "../../common/authentication/authentication.h"
#include "../../common/course/course.h"

DatabaseManager* DatabaseManager::s_Instance = nullptr;

DatabaseManager* DatabaseManager::getInstance() {
    if (s_Instance == nullptr) {
        s_Instance = new DatabaseManager();
    }
    return s_Instance;
}

DatabaseManager::DatabaseManager() {
    createConnection();
}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::createConnection() {
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("LMS_db");
    m_db.setUserName("root");
    m_db.setPassword("blessedNbest");

    if (!m_db.open()) {
        qDebug() << "Database error occurred:" << m_db.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseManager::executeQuery(const QString& query) {
    QSqlQuery q(m_db);
    if (!q.exec(query)) {
        qDebug() << "Query failed:" << q.lastError().text();
        qDebug() << "Executed query:" << q.executedQuery();
    }
    return q;
}

QVariant DatabaseManager::getScalarValue(const QString& query) {
    QSqlQuery q = executeQuery(query);
    if (q.next()) {
        return q.value(0);
    }
    return QVariant();
}

QList<QVariantMap> DatabaseManager::getQueryResults(const QString& query) {
    QList<QVariantMap> results;
    QSqlQuery q = executeQuery(query);
    while (q.next()) {
        QVariantMap row;
        for (int i = 0; i < q.record().count(); i++) {
            row[q.record().fieldName(i)] = q.value(i);
        }
        results.append(row);
    }
    return results;
}

QList<Course> Login(Authentication* auth) {
    QSqlQuery query;

    // query

    query.bindValue(":login", auth->GetLogin());
    query.bindValue(":password", auth->GetPassword());

    QVariant userId = DatabaseManager::getInstance()->getScalarValue(query);
    if (userId.isValid()) {
        // return Getmainpage(userId.toInt());
    } else {
        // Authentication failed, return an empty list
        return QList<Course>();
    }
}

// QList<Course> GetMainPage(int userId) {
//     QSqlQuery query;

//     // query

//     query.bindValue(":userId", userId);

//     QList<QVariantMap> results = DatabaseManager::getInstance()->getQueryResults(query);
//     QList<Course> courses;
//     for (const QVariantMap& row : results) {
//         Course course;
//         course.get = row["id"].toInt();
//         course.title = row["title"].toString();
//         course.avaUrl = row["ava_title_url"].toString();
//         course.startTime = row["start_time"].toDateTime();
//         course.endTime = row["end_time"].toDateTime();
//         courses.append(course);
//     }
//     return courses;
// }

// // Function to get course components
// Course GetCourseComponents(int32_t courseId) {
//     QSqlQuery query;

//     // query

//     query.bindValue(":courseId", courseId);

//     QList<QVariantMap> results = DatabaseManager::getInstance()->getQueryResults(query);
//     Course course;
//     for (const QVariantMap& row : results) {
//         CourseComponent component;
//         component.title = row["title"].toString();
//         component.url = row["url"].toString();
//         component.order = row["order"].toInt();
//         course.components.append(component);
//     }
//     return course;
// }

// // Function to get test questions
// CourseTest GetTestQuestion(int32_t testId) {
//     QSqlQuery query;

//     // query

//     query.bindValue(":testId", testId);

//     QVariantMap result = DatabaseManager::getInstance()->getQueryResults(query).first();
//     CourseTest test;
//     test.title = result["title"].toString();
//     test.maxMark = result["max_mark"].toInt();
//     test.urlJson = result["url_json"].toString();
//     return test;
// }
