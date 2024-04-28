#include "courseattestacion.h"
#include "ui_courseattestacion.h"

CourseAttestacion::CourseAttestacion(CourseTest * test, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAttestacion)
{
    ui->setupUi(this);
    this->test = test;
}

CourseAttestacion::~CourseAttestacion()
{
    delete ui;
}
