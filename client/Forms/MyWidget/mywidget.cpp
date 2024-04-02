#include "mywidget.h"
#include "ui_mywidget.h"
#include "FontManager/fontmanager.h"
#include <QPixmap>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //progressbar
    ui->progressBar->setFont(FontManager::GetInstance()->getRegular());
    ui->progressBar->setStyleSheet(
        "QProgressBar {"
        "border: none;"
        "border-radius: 10px;"
        "background-color: lightgrey;"
        "}"
        "QProgressBar::chunk {"
        "border-radius: 10px;"
        "background: #4EB5FF;"
        "}");
    //progressbarbutton
    ui->ProgressbarButton->raise();
    ui->ProgressbarButton->setCursor(Qt::PointingHandCursor);
    ui->ProgressbarButton->setFixedSize(341, 25);
    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-radius: 10px;"
        "border: 2px solid lightgrey;"
        "}");
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

    ui->CourseButtonIMG->setIcon(QIcon(":/img/resources/kap.jpg"));
    //ui->CourseButtonIMG->setIconSize(pixmap.rect().size());
}

MyWidget::~MyWidget()
{
    delete ui;
}
