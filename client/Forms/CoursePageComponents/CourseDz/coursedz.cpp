#include "coursedz.h"
#include "ui_coursedz.h"

CourseDz::CourseDz(CourseComponent * dz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDz)
{
    ui->setupUi(this);
    this->dz =  qobject_cast<CourseTask*>(dz);
    icon = new QPixmap(":/img/resources/dzicon3.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
}

CourseDz::~CourseDz()
{
    delete ui;
}
