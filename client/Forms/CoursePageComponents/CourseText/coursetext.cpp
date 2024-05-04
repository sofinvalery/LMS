#include "coursetext.h"
#include "ui_coursetext.h"

CourseText::CourseText(CourseComponent * text, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseText)
{
    ui->setupUi(this);
    this->text = qobject_cast<CourseTutorials*>(text);
    ui->label->setText(this->text->getContent());
    ui->label->setFixedSize(ui->label->sizeHint().width(), ui->label->sizeHint().height());
}

CourseText::~CourseText()
{
    delete ui;
}
