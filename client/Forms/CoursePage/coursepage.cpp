#include "coursepage.h"
#include "ui_coursepage.h"
#include "StyleManager/stylemanager.h"
#include "Forms/CoursePageComponents/componentswidgetfactory.h"

CoursePage::CoursePage(Course *course, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoursePage)
{
    ui->setupUi(this);
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
    ComponentsWidgetFactory<QString,QWidget,CourseComponent*> widgetFactory;
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);
    for (int i = 0; i < course->getListComponents().length(); i ++){
        //height += course->getListComponents()[i]->height

        QWidget * temp = widgetFactory.get(course->getListComponents()[i]->getType())(course->getListComponents()[i]);
        widgets.append(temp);
        temp->setParent(ui->scrollAreaWidgetContents);
        temp->move(0, height+81);
        height += temp->height()+20;
        temp->show();
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(height);
    iconIMG = new QPixmap(course->GetAvaTitleUrl());
    qDebug() << course->GetAvaTitleUrl();
    ui->IconLabel->setPixmap(iconIMG->scaled(111, 81, Qt::KeepAspectRatio));

    StyleManager::GetInstance()->setLabelStyle(ui->CourseNameLabel, course->GetTitle(), true, "black", true, 20);
    ui->CourseNameLabel->setFixedSize(ui->CourseNameLabel->sizeHint().width(), ui->CourseNameLabel->sizeHint().height());
}

CoursePage::~CoursePage()
{
    delete ui;
}
