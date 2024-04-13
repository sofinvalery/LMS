#include "courseadder.h"
#include "ui_courseadder.h"

CourseAdder::CourseAdder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAdder)
{
    ui->setupUi(this);
}

CourseAdder::~CourseAdder()
{
    delete ui;
}
