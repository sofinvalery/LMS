#include "coursepage.h"
#include "ui_coursepage.h"
#include "StyleManager/stylemanager.h"
#include "Forms/CoursePageComponents/componentswidgetfactory.h"
#include "Forms/CoursePage/CoursePageEditor/coursepageeditor.h"
#include "ClientState/clientstate.h"

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

    StyleManager::GetInstance()->setBlueButtonStyle(ui->EditCourseButton, ui->EditCourseButton->text(), true, 16, 13);
    ui->EditCourseButton->setFixedSize(ui->EditCourseButton->sizeHint().width() + 10, ui->EditCourseButton->sizeHint().height() + 10);
    ui->EditCourseButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->EditCourseButton->size().width() - 20, 30);
    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: none;"
        "}");
    //scrollarea
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);
    ShowComponents();
    iconIMG = new QPixmap(course->GetAvaTitleUrl());
    ui->IconLabel->setPixmap(iconIMG->scaled(184, 120, Qt::IgnoreAspectRatio));
    ui->IconLabel->setFixedSize(ui->IconLabel->sizeHint().width(), ui->IconLabel->sizeHint().height());
    StyleManager::GetInstance()->setLabelStyle(ui->CourseNameLabel, course->GetTitle(), true, "black", true, 36);
    ui->CourseNameLabel->setFixedSize(ui->CourseNameLabel->sizeHint().width(), ui->CourseNameLabel->sizeHint().height());
    qInfo() << ui->CourseNameLabel->width() << " " << ui->CourseNameLabel->height();
    ui->CourseNameLabel->move(204, 40);

    ui->horizontalLine->setStyleSheet("border: 3px solid lightgrey;");
    ui->horizontalLine->setFixedSize(StyleManager::GetInstance()->getScreenWidth(), 3);
    ui->horizontalLine->move(0, 120);

    ui->verticalLine->setStyleSheet("border: 3px solid lightgrey;");
    ui->verticalLine->setFixedSize(3, 120);
    ui->verticalLine->move(184, 0);

    if(ClientState::GetInstance()->getAuth()->GetCurrentRole() == STUDENT){
        ui->EditCourseButton->hide();
    }

}

void CoursePage::ShowComponents()
{
    height = 140;
    ComponentsWidgetFactory<QString,QWidget,CourseComponent*> widgetFactory;
    for (int i = 0; i < course->getListComponents().size(); i ++){
        QWidget * temp = widgetFactory.get(course->getListComponents()[i]->getType())(course->getListComponents()[i]);
        widgets.append(temp);
        temp->setParent(ui->scrollAreaWidgetContents);
        temp->move(10, height+30);
        height += temp->height()+30;
        temp->show();
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(height+200);
    iconIMG = new QPixmap(course->GetAvaTitleUrl());
    ui->IconLabel->setPixmap(iconIMG->scaled(111, 81, Qt::KeepAspectRatio));

    StyleManager::GetInstance()->setLabelStyle(ui->CourseNameLabel, course->GetTitle(), true, "black", true, 20);
    ui->CourseNameLabel->setFixedSize(ui->CourseNameLabel->sizeHint().width(), ui->CourseNameLabel->sizeHint().height());
}

void CoursePage::CleanComponents()
{
    //qDeleteAll(widgets);
    for (int i = 0; i < widgets.size(); i++){
        widgets[i]->close();
        widgets[i]->deleteLater();
    }
    widgets.clear();
}

CoursePage::~CoursePage()
{
    delete ui;
}

void CoursePage::on_EditCourseButton_clicked()
{
    CoursePageEditor* editor = new CoursePageEditor(this, this);
    editor->move(StyleManager::GetInstance()->getScreenWidth() / 2 - 290, StyleManager::GetInstance()->getScreenHeight() / 2 - 250);
    editor->show();
}

