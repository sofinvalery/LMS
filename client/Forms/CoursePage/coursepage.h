#ifndef COURSEPAGE_H
#define COURSEPAGE_H

#include <QWidget>
#include "../common/course/course.h"
#include "AdminScore/adminscore.h"
#include "CheckDZ/checkdz.h"
#include <QPixmap>

namespace Ui {
class CoursePage;
}

class CoursePage : public QWidget
{
    Q_OBJECT

public:
    explicit CoursePage(Course *course, QWidget *parent = nullptr);
    void ShowComponents();
    void CleanComponents();
    Course * GetCourse(){return course;}
    ~CoursePage();
    QList<QWidget *> getWidgets() const;

private slots:
    void on_EditCourseButton_clicked();
    void showScoreForTeacher();
    void on_scoreButton_clicked();
    void showCheckTask(QList<Submit*>);
    void on_checkButton_clicked();

private:
    AdminScore* adminScore = nullptr;
    Ui::CoursePage *ui;
    QList<QWidget*> widgets;
    int height = 0;
    QPixmap * iconIMG;
    Course * course;
};

#endif // COURSEPAGE_H
