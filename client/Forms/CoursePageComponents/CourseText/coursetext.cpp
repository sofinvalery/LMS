#include "coursetext.h"
#include "ui_coursetext.h"

CourseText::CourseText(CourseTutorials * text, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseText)
{
    ui->setupUi(this);
    this->text = text;
}

CourseText::~CourseText()
{
    delete ui;
}
