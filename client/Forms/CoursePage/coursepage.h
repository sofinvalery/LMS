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
    ~CoursePage();

private:
    Ui::CoursePage *ui;
    QList<QWidget*> widgets;
    int height = 0;
    QPixmap * iconIMG;
};

#endif // COURSEPAGE_H
