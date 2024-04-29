#ifndef COURSEDZ_H
#define COURSEDZ_H

#include <QWidget>
#include "../../../../common/course/course_components/coursetask.h"
#include "QPixmap"


namespace Ui {
class CourseDz;
}

class CourseDz : public QWidget
{
    Q_OBJECT

public:
    explicit CourseDz(CourseComponent * dz, QWidget *parent = nullptr);
    ~CourseDz();

private:
    Ui::CourseDz *ui;
    CourseTask * dz;
    QPixmap * icon;
};

#endif // COURSEDZ_H
