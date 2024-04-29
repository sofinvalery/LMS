#ifndef COURSEATTESTACION_H
#define COURSEATTESTACION_H

#include <QWidget>

#include "../../../../common/course/course_components/coursetest.h"
#include "QPixmap"


namespace Ui {
class CourseAttestacion;
}

class CourseAttestacion : public QWidget
{
    Q_OBJECT

public:
    explicit CourseAttestacion(CourseComponent * test, QWidget *parent = nullptr);
    ~CourseAttestacion();

private:
    Ui::CourseAttestacion *ui;
    CourseTest * test;
    QPixmap * icon;
};

#endif // COURSEATTESTACION_H
