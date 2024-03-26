#include <QScreen>
#include <QScrollArea>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define arrlen 25

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QScreen* scr = QGuiApplication::primaryScreen();
    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height());
    ui->scrollArea->setWidgetResizable(true);
    ui->groupBox->setMinimumSize(this->frameGeometry().width()-50,this->frameGeometry().height()-43);
    ui->scrollArea->resize(this->frameGeometry().width()-70,this->frameGeometry().height()-100);
    //ui->scrollAreaWidgetContents->setMinimumWidth(this->frameGeometry().width()-20); - ширина области в которой работает скролл
    ui->scrollAreaWidgetContents->setMinimumHeight((arrlen/4)*(65+262)+350);
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().width());
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().height());
    ui->gridLayoutWidget->resize(this->frameGeometry().width()-70,this->frameGeometry().height()-100);
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

