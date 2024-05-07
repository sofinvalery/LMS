#include "coursetext.h"
#include "ui_coursetext.h"
#include "StyleManager/stylemanager.h"

CourseText::CourseText(CourseComponent * text, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseText)
{
    ui->setupUi(this);
    this->text = qobject_cast<CourseTutorials*>(text);
    StyleManager::GetInstance()->setLabelStyle(ui->label, this->text->getContent(), false, "black", true, 18);
    ui->label->setFixedSize(ui->label->sizeHint().width(), ui->label->sizeHint().height());
    ui->label->setAlignment(Qt::AlignBottom);
    ui->label->setWordWrap(true);
    ui->label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->label->setMaximumWidth(StyleManager::GetInstance()->getScreenWidth()-50);
    ui->label->adjustSize();
    this->adjustSize();
}

CourseText::~CourseText()
{
    delete ui;
}
