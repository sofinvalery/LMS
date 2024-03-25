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
    query.prepare("");

    // Bind parameters
    query.bindValue(":login", auth->GetLogin());
    query.bindValue(":password", auth->GetPassword());

    // Execute the query
    QVariant userId = DatabaseManager::getInstance()->getScalarValue(query.executedQuery());

    if (userId.isValid()) {
        QList<Course> courses;

        QSqlQuery courseQuery;
        courseQuery.prepare("");
        courseQuery.bindValue(":userId", userId.toInt());
        QSqlQuery result = DatabaseManager::getInstance()->executeQuery(courseQuery.executedQuery());

        while (result.next()) {
            int courseId = result.value("id").toInt();
            QString title = result.value("title").toString();
            QString avaUrl = result.value("avaUrl").toString();
            QDate start = result.value("start").toDate();
            QDate end = result.value("end").toDate();
            int sumpoints = result.value("sumpoints").toInt();

            Course course(courseId, title, avaUrl, start, end, sumpoints);
            courses.append(course);
        }
        return courses;
    } else {
        // ???????????????
        return QList<Course>();
    }
}
