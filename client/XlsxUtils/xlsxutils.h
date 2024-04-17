#ifndef XLSXUTILS_H
#define XLSXUTILS_H

#include <QObject>
#include "../../common/authentication/group.h"

class XlsxUtils : public QObject
{
    Q_OBJECT
private:
    explicit XlsxUtils(QObject *parent = nullptr);
    static XlsxUtils* s_Instance;
    QList<QString> downloadPath;
public:
    static XlsxUtils* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new XlsxUtils()); }
    void getExampleForAddingGroup();
    void getAddedGroup(Group* group);
signals:
    void Readed(QString);
};

#endif // XLSXUTILS_H
