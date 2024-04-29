#include "courseattestacion.h"
#include "ui_courseattestacion.h"

CourseAttestacion::CourseAttestacion(CourseComponent * test, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAttestacion)
{
    ui->setupUi(this);
    this->test = qobject_cast<CourseTest*>(test);
}

CourseAttestacion::~CourseAttestacion()
{
    delete ui;
}
