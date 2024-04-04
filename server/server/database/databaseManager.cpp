#include "databasemanager.h"

static QThreadStorage<QSqlDatabase> mDatabasePool;


DatabaseManager::DatabaseManager() {
    createConnection();
}

DatabaseManager::~DatabaseManager() {

}

bool DatabaseManager::createConnection() {
  /*  m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("lms_db");
    m_db.setUserName("root");
    m_db.setPassword("12345");

    if (!m_db.open()) {
        qDebug() << "Database error occurred:" << m_db.lastError().text();
        return false;
    }

    return true;
*/
    if(mDatabasePool.hasLocalData()) {
        m_db= mDatabasePool.localData();
        return true;
    } else {
        auto m_db = QSqlDatabase::addDatabase("QMYSQL", QUuid::createUuid().toString());
        m_db.setHostName("localhost");
        m_db.setDatabaseName("lms_db");
        m_db.setUserName("root");
        m_db.setPassword("12345");
        m_db.setPort(3306);
        if (!m_db.open()) {
            qInfo() << "Database error occurred:" << m_db.lastError().text();
            throw("bd bad");
        }
        else{
            while(!m_db.isOpen()){
                qInfo()<<"she is opening";
            }
            qInfo()<<"she opened";
        mDatabasePool.setLocalData(m_db);
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


