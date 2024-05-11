#ifndef COURSEDZPAGE_H
#define COURSEDZPAGE_H

#include <QWidget>
#include "../../../../../common/course/course_components/coursetask.h"

namespace Ui {
class CourseDzPage;
}

class CourseDzPage : public QWidget
{
    Q_OBJECT

public:
    explicit CourseDzPage(CourseTask* dz, QWidget *parent = nullptr);
    ~CourseDzPage();

private slots:
    void on_exitButton_clicked();

private:
    Ui::CourseDzPage *ui;
};

#endif // COURSEDZPAGE_H
