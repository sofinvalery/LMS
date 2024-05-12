#ifndef SCORECOMPONENTS_H
#define SCORECOMPONENTS_H

#include <QWidget>
#include "../common/course/course.h"

namespace Ui {
class ScoreComponents;
}

class ScoreComponents : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreComponents(QString courseName = "CourseName", int currentScore = 0, int maxScore = 100, QWidget *parent = nullptr, Course* course = nullptr);
    ~ScoreComponents();

private slots:
    void on_pushButton_clicked();

signals:
    void showPathCourseScore(Course* course);

private:
    Course* course;
    Ui::ScoreComponents *ui;
};

#endif // SCORECOMPONENTS_H
