#ifndef COURSEPAGE_H
#define COURSEPAGE_H

#include <QWidget>
#include "../common/course/course.h"
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
private slots:
    void on_EditCourseButton_clicked();

private:
    Ui::CoursePage *ui;
    QList<QWidget*> widgets;
    int height = 0;
    QPixmap * iconIMG;
    Course * course;
};

#endif // COURSEPAGE_H
