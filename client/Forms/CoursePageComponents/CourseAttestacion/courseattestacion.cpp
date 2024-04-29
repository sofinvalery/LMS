#include "courseattestacion.h"
#include "ui_courseattestacion.h"

CourseAttestacion::CourseAttestacion(CourseComponent * test, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAttestacion)
{
    ui->setupUi(this);
    this->test = qobject_cast<CourseTest*>(test);
    icon = new QPixmap(":/img/resources/test.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
}

CourseAttestacion::~CourseAttestacion()
{
    delete ui;
}
