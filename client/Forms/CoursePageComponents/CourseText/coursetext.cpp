#include "coursetext.h"
#include "ui_coursetext.h"

CourseText::CourseText(CourseComponent * text, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseText)
{
    ui->setupUi(this);
    this->text = qobject_cast<CourseTutorials*>(text);
}

CourseText::~CourseText()
{
    delete ui;
}
