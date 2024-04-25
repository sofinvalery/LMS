#include "courseadder.h"
#include "ui_courseadder.h"
#include <QScreen>
#include <QFileDialog>
#include <QDir>
#include "ClientState/clientstate.h"
#include "StyleManager/stylemanager.h"



CourseAdder::CourseAdder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAdder)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 81);

    course = new MyWidget(new Course(15,"Название предмета","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80));
    ui->verticalLayout->addWidget(course);
    course->show();
}

CourseAdder::~CourseAdder()
{
    delete ui;
}

void CourseAdder::on_Apply_clicked()
{
    course->setName(ui->CourseName->text());
    if (ui->ImgPath->text() != "")
        course->setIMG(ui->ImgPath->text());
    // for (QString temp : ClientState::GetInstance()->getPotoksName())
    // {
    //     if (ui->PotokStudents->text() != temp);

    // }


}


void CourseAdder::on_FoundIMG_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбор картинки", QDir::homePath(), "JPEG Image (*.jpg);;PNG Image (*.png);;All Image Files (*.jpg *.png)");

    ui->ImgPath->setText(path);
}


void CourseAdder::on_CreateCourse_clicked()
{
    // for (QString temp : ClientState::GetInstance()->getPotoksName())
    // {
    //     if (ui->PotokStudents->text() != temp);

    // }
    if (!ClientState::GetInstance()->getPotoksName().contains(ui->PotokStudents->text())){
        ui->StudentsError->setText("Ошибка, такого потока не существует");
    }
    if (!ClientState::GetInstance()->getGroupsName().contains(ui->GroupTeachers->text())){
        ui->TeachersError->setText("Ошибка, такой группы \nпреподователей не существует");
    }
}

