#ifndef ADMINSCORE_H
#define ADMINSCORE_H

#include <QWidget>
#include"../common/transferEnum/transferEnum.h"
#include "../common/authentication/group.h"
#include "../common/course/course.h"


namespace Ui {
class AdminScore;
}

class AdminScore : public QWidget
{
    Q_OBJECT

public:
    explicit AdminScore(Course* course,QWidget *parent = nullptr);
    ~AdminScore();

private slots:
    void on_exitButton_clicked();

    void on_getCheckBox_clicked();

    void on_updateCheckBox_clicked();

    void on_getDoneButton_clicked();

    void on_getPatternButton_clicked();

    void on_setExcelButton_clicked();

    void on_confirmButton_clicked();

    void getExecel(QList<Submit *> submits, Group* group);

    void parseExel();

private:
    Course* course;
    Ui::AdminScore *ui;
    QList<Submit*> submits;
    QString path;
};

#endif // ADMINSCORE_H
