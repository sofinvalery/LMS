#include "coursepage.h"
#include "ui_coursepage.h"
#include "StyleManager/stylemanager.h"
#include "Forms/CoursePageComponents/componentswidgetfactory.h"
#include "Forms/CoursePage/CoursePageEditor/coursepageeditor.h"

CoursePage::CoursePage(Course *course, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoursePage)
{
    ui->setupUi(this);
    this->course = course;
    ui->groupBox->setStyleSheet("background-color: white;");
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");
    this->move(0, 90);

    this->resize( StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    ui->scrollArea->setWidgetResizable(true);

    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->scrollArea->resize(this->frameGeometry().width(),this->frameGeometry().height() - 42);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: none;"
        "}");
    //scrollarea
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);
    ShowComponents();
    iconIMG = new QPixmap(course->GetAvaTitleUrl());
    ui->IconLabel->setPixmap(iconIMG->scaled(111, 81, Qt::KeepAspectRatio));

    StyleManager::GetInstance()->setLabelStyle(ui->CourseNameLabel, course->GetTitle(), true, "black", true, 20);
    ui->CourseNameLabel->setFixedSize(ui->CourseNameLabel->sizeHint().width(), ui->CourseNameLabel->sizeHint().height());
}

void CoursePage::ShowComponents()
{
    height = 0;
    ComponentsWidgetFactory<QString,QWidget,CourseComponent*> widgetFactory;
    for (int i = 0; i < course->getListComponents().size(); i ++){
        QWidget * temp = widgetFactory.get(course->getListComponents()[i]->getType())(course->getListComponents()[i]);
        widgets.append(temp);
        temp->setParent(ui->scrollAreaWidgetContents);
        temp->move(0, height+81);
        height += temp->height()+20;
        temp->show();
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(height);
}

void CoursePage::CleanComponents()
{
    //qDeleteAll(widgets);
    for (int i = 0; i < widgets.size(); i++){
        widgets[i]->close();
    }
    widgets.clear();
}

CoursePage::~CoursePage()
{
    delete ui;
}

void CoursePage::on_EditCourseButton_clicked()
{
    CoursePageEditor * editor = new CoursePageEditor(this);
    editor->setParent(this);
    editor->show();
    editor->move(400, 400);
}

