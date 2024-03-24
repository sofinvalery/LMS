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

class DatabaseManager {
public:
    static DatabaseManager* getInstance();
    ~DatabaseManager();

    bool createConnection();
    QSqlQuery executeQuery(const QString& query);
    QVariant getScalarValue(const QString& query);
    QList<QVariantMap> getQueryResults(const QString& query);

private:
    DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    static DatabaseManager* s_Instance;
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
