#ifndef COURSEATTESTACION_H
#define COURSEATTESTACION_H

#include <QWidget>
#include "../../../../common/course/course_components/coursetest.h"

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
};

#endif // COURSEATTESTACION_H
