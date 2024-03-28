#include "mywidget.h"
#include "ui_mywidget.h"
#include "FontManager/fontmanager.h"
#include <QPixmap>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: white;");
    //progressbar
    ui->progressBar->setFont(FontManager::GetInstance()->getRegular());
    ui->progressBar->setStyleSheet(
        "QProgressBar {"
        "border: none;"
        "border-radius: 10px;"
        "background-color: lightgrey;"
        "}"
        "QProgressBar::chunk {"
        "background-color: #2194DE;"
        "border-radius: 10px;"
        "}");
    //progressbarbutton
    ui->ProgressbarButton->setCursor(Qt::PointingHandCursor);
    //coursename
    ui->CourseName->setFont(FontManager::GetInstance()->getBold());
    ui->CourseName->setStyleSheet(
        "QLabel {"
        "font-size: 15px;"
        "}");
    //coursebuttonimg
    ui->CourseButtonIMG->setCursor(Qt::PointingHandCursor);
    ui->CourseButtonIMG->setStyleSheet(
        "QPushButton {"
        "border: 1px solid black;"
        "border-radius: 20px;"
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

    ui->CourseButtonIMG->setIcon(QIcon(":/img/resources/kap.jpg"));
    //ui->CourseButtonIMG->setIconSize(pixmap.rect().size());
}

MyWidget::~MyWidget()
{
    delete ui;
}
