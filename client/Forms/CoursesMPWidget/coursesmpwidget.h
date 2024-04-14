#ifndef COURSESMPWIDGET_H
#define COURSESMPWIDGET_H

#include "Forms/MyWidget/mywidget.h"
#include <QWidget>

namespace Ui {
class CoursesMPWidget;
}

class CoursesMPWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoursesMPWidget(QWidget *parent = nullptr);
    ~CoursesMPWidget();

private:
    Ui::CoursesMPWidget *ui;
};

#endif // COURSESMPWIDGET_H
