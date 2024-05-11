#include "courseadder.h"
#include "ui_courseadder.h"
#include <QFileDialog>
#include <QDir>
#include "ClientState/clientstate.h"
#include "StyleManager/stylemanager.h"
#include<QCompleter>


CourseAdder::CourseAdder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAdder)
{
    ui->setupUi(this);
    QCompleter* completer1= new QCompleter(ClientState::GetInstance()->getGroupsName());
    ui->GroupTeachers->setCompleter(completer1);
    QCompleter* completer2=new QCompleter(ClientState::GetInstance()->getPotoksName());
    ui->PotokStudents->setCompleter(completer2);
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setCalendarPopup(true);
    ui->dateEdit_2->setDate((QDate::currentDate()).addYears(1));
    StyleManager::GetInstance()->setWidgetGroupBoxStyle(this, ui->groupBox, 90);

    StyleManager::GetInstance()->setBlueButtonStyle(ui->Apply, "Применить\nизменения", true, 16, 13);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->CreateCourse, "Создать курс", true, 16, 13);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->FoundIMG, "Добавить\nизображение", true, 16, 13);
    StyleManager::GetInstance()->setLineEditStyle(ui->CourseName, "Название курса", false, 16, 150, 30);
    StyleManager::GetInstance()->setLineEditStyle(ui->GroupTeachers, "Группа преподавателей", false, 16, 235, 30);
    StyleManager::GetInstance()->setLineEditStyle(ui->PotokStudents, "Название потока", false, 16, 180, 30);
    StyleManager::GetInstance()->setLabelStyle(ui->label, "Путь к картинке", false, "black", true, 16);
    StyleManager::GetInstance()->setLabelStyle(ui->StudentsError, "Ошибка, такого потока не существует", false, "red", false, 12);
    StyleManager::GetInstance()->setLabelStyle(ui->TeachersError, "Ошибка, такой группы \nпреподователей не существует", false, "red", false, 12);
    StyleManager::GetInstance()->setLabelStyle(ui->ImgPath, "", false, "black", true, 16);
    course = new MyWidget(new Course(15,"Название предмета",":/img/resources/kap.jpg", QDate(2004,4,4),QDate(2005,1,1),11,80));
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
    bool isGood=true;
    if (!ClientState::GetInstance()->getPotoksName().contains(ui->PotokStudents->text())){
        ui->StudentsError->setText("Ошибка, такого потока не существует");
        isGood=0;
    }
    if (!ClientState::GetInstance()->getGroupsName().contains(ui->GroupTeachers->text())){
        ui->TeachersError->setText("Ошибка, такой группы \nпреподователей не существует");
        isGood=0;
    }
    if(ui->CourseName->text()==""){
        ui->TeachersError_2->setText("Имя курса не может быть пустым");
        isGood=0;
    }
    if(isGood)
    {
        QJsonObject json;
        Course course(1,ui->CourseName->text(), ui->ImgPath->text(),ui->dateEdit->date(),ui->dateEdit_2->date());
        json["Course"]=course.Serialize();
        json["teachersGroupName"]=ui->GroupTeachers->text();
        json["unionName"]=ui->PotokStudents->text();
        ClientManager::GetInstance()->SendJsonToServer(SETNEWCOURSE,json);
        ClientState::GetInstance()->getMainwindow()->on_mainButton_clicked();
    }
}

