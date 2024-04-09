#include "databasemanager.h"

static QThreadStorage<QSqlDatabase> mDatabasePool;


DatabaseManager::DatabaseManager() {
    createConnection();
}

DatabaseManager::~DatabaseManager() {

}

bool DatabaseManager::createConnection() {
    if(mDatabasePool.hasLocalData()) {
        m_db = mDatabasePool.localData();
        return true;
    } else {
        m_db = QSqlDatabase::addDatabase("QPSQL", QUuid::createUuid().toString());
        m_db.setHostName("localhost");
        m_db.setDatabaseName("LMS_db");
        m_db.setUserName("root");
        m_db.setPassword("12345");
        m_db.setPort(5432);
        if (!m_db.open()) {
            qInfo() << "Database error occurred:" << m_db.lastError().text();
            throw("bd bad");
        }
        else{
        mDatabasePool.setLocalData(m_db);
        m_db = mDatabasePool.localData();
                return true;
        }
    }
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


