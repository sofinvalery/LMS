#include "databaseManager.h"

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


