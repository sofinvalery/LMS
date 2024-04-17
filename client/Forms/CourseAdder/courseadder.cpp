#include "courseadder.h"
#include "ui_courseadder.h"
#include <QScreen>
#include <QFileDialog>
#include <QDir>


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

}


void CourseAdder::on_FoundIMG_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбор картинки", QDir::homePath(), "JPEG Image (*.jpg);; PNG Image (*.png);");
    ui->ImgPath->setText(path);
}

