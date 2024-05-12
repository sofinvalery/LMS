#ifndef XLSXUTILS_H
#define XLSXUTILS_H

#include <QObject>
#include "../../common/authentication/group.h"
#include "../common/transferEnum/transferEnum.h"
#include "../common/course/course.h"
#include "../common/authentication/group.h"

struct AddingData{
    QString titleName;
    QList<QString> pathName;
};

class XlsxUtils : public QObject
{
    Q_OBJECT
private:
    explicit XlsxUtils(QObject *parent = nullptr);
    static XlsxUtils* s_Instance;
    QList<QString> downloadPath;
    void getExample(QString titleName,QString pathName,QString fileName);
public:
    static XlsxUtils* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new XlsxUtils()); }
    void getExampleForAddingGroup();
    void getExampleForAddingPotok();
    void getAddedGroup(Group* group);
    void getAddedPotok(AddingData* data);
    AddingData* parsAddingXlsx(QString path);
    void getCourseScoreTable(QList<Submit*>& submits,Course* course, Group* group);
signals:
    void Readed(QString);
};

#endif // XLSXUTILS_H
