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
    QString query = "SELECT id FROM users WHERE login = :username AND password = :password";
    query.bindValue(":username", auth->username);
    query.bindValue(":password", auth->password);

    QVariant userId = DatabaseManager::getInstance()->getScalarValue(query);
    if (userId.isValid()) {
        // Authentication successful, return a list of courses for the user
        return Getmainpage(userId.toInt());
    } else {
        // Authentication failed, return an empty list
        return QList<Course>();
    }
}

// Function to get the main page data
QList<Course> GetMainPage(int userId) {
    QString query = "SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time "
                    "FROM courses c "
                    "JOIN zachisleniya z ON z.groups_id = c.groups_id "
                    "WHERE z.users_id = :userId";
    query.bindValue(":userId", userId);

    QList<QVariantMap> results = DatabaseManager::getInstance()->getQueryResults(query);
    QList<Course> courses;
    for (const QVariantMap& row : results) {
        Course course;
        course.id = row["id"].toInt();
        course.title = row["title"].toString();
        course.avaUrl = row["ava_title_url"].toString();
        course.startTime = row["start_time"].toDateTime();
        course.endTime = row["end_time"].toDateTime();
        courses.append(course);
    }
    return courses;
}

// Function to get course components
Course GetCourseComponents(int32_t courseId) {
    QString query = "SELECT p.title, p.url, p.`order` "
                    "FROM path_course_pdfs p "
                    "WHERE p.courses_id1 = :courseId "
                    "UNION "
                    "SELECT pt.content, NULL, pt.`order` "
                    "FROM path_course_tasks pt "
                    "WHERE pt.courses_id1 = :courseId "
                    "UNION "
                    "SELECT pt.title, pt.url_json, pt.`order` "
                    "FROM path_course_tests pt "
                    "WHERE pt.courses_id1 = :courseId "
                    "UNION "
                    "SELECT pv.url, NULL, pv.`order` "
                    "FROM path_course_videos pv "
                    "WHERE pv.courses_id1 = :courseId "
                    "ORDER BY `order`";
    query.bindValue(":courseId", courseId);

    QList<QVariantMap> results = DatabaseManager::getInstance()->getQueryResults(query);
    Course course;
    for (const QVariantMap& row : results) {
        CourseComponent component;
        component.title = row["title"].toString();
        component.url = row["url"].toString();
        component.order = row["order"].toInt();
        course.components.append(component);
    }
    return course;
}

// Function to get test questions
CourseTest GetTestQuestion(int32_t testId) {
    QString query = "SELECT title, max_mark, url_json FROM path_course_tests WHERE id = :testId";
    query.bindValue(":testId", testId);

    QVariantMap result = DatabaseManager::getInstance()->getQueryResults(query).first();
    CourseTest test;
    test.title = result["title"].toString();
    test.maxMark = result["max_mark"].toInt();
    test.urlJson = result["url_json"].toString();
    return test;
}
