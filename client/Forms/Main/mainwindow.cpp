#include <QScreen>
#include <QScrollArea>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FontManager/fontmanager.h"

#define arrlen 25

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet("background-color: white;");
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");

    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: none;"
        "}");
    //scrollarea
    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "border: none;"
        "border-top: 1px solid grey;"
        "}");
    //windowname
    ui->windowname->setText("Ваши курсы");
    ui->windowname->setFont(FontManager::GetInstance()->getRegular());
    ui->windowname->setStyleSheet(
        "QLabel {"
        "font-size: 32px;"
        "}");
    //profilebutton
    ui->profileButton->setIcon(QIcon(":/img/resources/profile.png"));
    ui->profileButton->setFixedSize(64, 64);
    ui->profileButton->setStyleSheet(
        "QPushButton {"
        "border-radius: 30px;"
        "padding: 6px;"
        "}"
        "QPushButton:hover {"
        "background-color: lightgrey;"
        "}"
        "QPushButton:pressed {"
        "background-color: grey;"
        "}");
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    ui->profileButton->move(screenGeometry.width() - 64 - 10, 13);
    ui->profileButton->setCursor(Qt::PointingHandCursor);

    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height());
    ui->scrollArea->setWidgetResizable(true);

    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->scrollArea->resize(this->frameGeometry().width(),this->frameGeometry().height() - 42);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //ui->scrollArea->resize(this->frameGeometry().width()-20,this->frameGeometry().height()-100);
    //ui->scrollAreaWidgetContents->setMinimumWidth(this->frameGeometry().width()-20); - ширина области в которой работает скролл
    ui->scrollAreaWidgetContents->setMinimumHeight((arrlen/4)*(65+262)+350);
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().width());
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().height());
    ui->gridLayoutWidget->resize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->gridLayoutWidget->setMinimumHeight((arrlen/4)*(65+262)+350);
    // ui->gridLayout->setColumnMinimumWidth(0,351);
    // ui->gridLayout->setColumnMinimumWidth(1,351);
    // ui->gridLayout->setColumnMinimumWidth(2,351);
    // ui->gridLayout->setColumnMinimumWidth(3,351);
    //ui->gridLayout->setRowMinimumHeight(0,0);
    ui->gridLayout->setVerticalSpacing(65);
    ui->gridLayout->setHorizontalSpacing(65);
    //ui->gridLayout->setContentsMargins(0,0,0,0);
    //ui->gridLayout->setGeometry(this->frameGeometry());
    for (int i = 0, j = 0, z = 0; z < arrlen; z++, j++){
        course[z] = new MyWidget();
        if (z % 4 == 0){
            j = 0;
            i++;
            //ui->gridLayout->setRowMinimumHeight(i,1);
        }
        ui->gridLayout->addWidget(course[z],i,j);

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

