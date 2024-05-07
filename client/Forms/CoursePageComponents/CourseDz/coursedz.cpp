#include "coursedz.h"
#include "ui_coursedz.h"
#include "StyleManager/stylemanager.h"

CourseDz::CourseDz(CourseComponent * dz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDz)
{
    ui->setupUi(this);
    this->dz =  qobject_cast<CourseTask*>(dz);
    icon = new QPixmap(":/img/resources/dzicon3.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->giveDzButton, this->dz->getTitle(), true, 16, 15);
}

CourseDz::~CourseDz()
{
    delete ui;
}

void CourseDz::SetTextOnButton(QString buttontext)
{
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->giveDzButton, buttontext, true, 16, 15);
}
