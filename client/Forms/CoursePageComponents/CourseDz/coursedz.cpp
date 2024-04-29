#include "coursedz.h"
#include "ui_coursedz.h"

CourseDz::CourseDz(CourseComponent * dz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDz)
{
    ui->setupUi(this);
    this->dz =  qobject_cast<CourseTask*>(dz);
}

CourseDz::~CourseDz()
{
    delete ui;
}
