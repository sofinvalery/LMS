#include "courseadder.h"
#include "ui_courseadder.h"
#include <QScreen>
#include <QFileDialog>
#include <QDir>
#include "ClientState/clientstate.h"


CourseAdder::CourseAdder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAdder)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-top: 3px solid lightgrey;"
        "}");

    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height() - 20);
    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height() - 20);
    this->move(0, 90);
    course = new MyWidget();
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
    path = QFileDialog::getOpenFileName(this, "Выбор картинки", QDir::homePath(), "JPEG Image (*.jpg);; PNG Image (*.png);");
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

