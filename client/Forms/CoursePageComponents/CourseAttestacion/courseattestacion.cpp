#include "courseattestacion.h"
#include "ui_courseattestacion.h"
#include "StyleManager/stylemanager.h"

CourseAttestacion::CourseAttestacion(CourseComponent * test, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAttestacion)
{
    ui->setupUi(this);
    this->test = qobject_cast<CourseTest*>(test);
    icon = new QPixmap(":/img/resources/test.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->DownloadButton, "Пройти тест", true, 16, 15);
}

CourseAttestacion::~CourseAttestacion()
{
    delete ui;
}