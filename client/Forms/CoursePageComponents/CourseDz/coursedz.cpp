#include "coursedz.h"
#include "ui_coursedz.h"

CourseDz::CourseDz(CourseTask * dz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDz)
{
    ui->setupUi(this);
    this->dz = dz;
}

CourseDz::~CourseDz()
{
    delete ui;
}
