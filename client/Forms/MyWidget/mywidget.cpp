#include "mywidget.h"
#include "ui_mywidget.h"
#include "StyleManager/stylemanager.h"
#include <QPixmap>
#include "ClientState/clientstate.h"

MyWidget::MyWidget(Course* course,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->course=course;
    //progressbar
    StyleManager::GetInstance()->setProgressBarStyle(ui->progressBar, false, 10, "lightgrey",
                                                     "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(78, 181, 255, 255), stop:1 rgba(108, 73, 217, 255));");
    //progressbarbutton
    ui->ProgressbarButton->raise();
    ui->ProgressbarButton->setCursor(Qt::PointingHandCursor);
    ui->ProgressbarButton->setFixedSize(341, 25);
    ui->progressBar->setRange(0, course->getMaxSumpoints()!=0?course->getMaxSumpoints():1);
    ui->progressBar->setValue(course->getSumpoints());
    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-radius: 10px;"
        "border: 2px solid lightgrey;"
        "}");
    //coursename
    StyleManager::GetInstance()->setLabelStyle(ui->CourseName, course->GetTitle(), true, "black", true, 15);

    //coursebuttonimg
    ui->CourseButtonIMG->setCursor(Qt::PointingHandCursor);
    ui->CourseButtonIMG->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "background-color: lightgrey;"
        "}"
        "QPushButton:pressed {"
        "background-color: grey;"
        "}");

    //QWidget::setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    //QPixmap pixmap("kapipng.png");
    //QIcon ButtonIcon(pixmap);

    ui->CourseButtonIMG->setIcon(QIcon(course->GetAvaTitleUrl()));
    //ui->CourseButtonIMG->setIconSize(pixmap.rect().size());
}

void MyWidget::setName(QString name)
{
    ui->CourseName->setText(name);
}

void MyWidget::setIMG(QString path)
{
    ui->CourseButtonIMG->setIcon(QIcon(path));
}


MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_CourseButtonIMG_clicked()
{
    ClientState::GetInstance()->getMainwindow()->clickCoursePage(course);
}

