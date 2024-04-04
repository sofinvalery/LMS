#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Forms/Profile/profile.h"
#include <QMessageBox>

#define arrlen 25

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->groupBox->setStyleSheet("background-color: white;");
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");

    ui->adminButton->hide();

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    Authentication* auth =new Authentication("sds","gtht");
    auth->SetInformationAfterAuthentication("Max","bbbbb",ADMIN,55,QList<QString>{"O725B"});

    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: none;"
        "}");
    //scrollarea
    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "border: none;"
        "border-top: 2px solid grey;"
        "}");
    //mainbutton
    ui->mainButton->setCursor(Qt::PointingHandCursor);
    ui->mainButton->setFont(FontManager::GetInstance()->getRegular());
    ui->mainButton->setText("Главная");
    ui->mainButton->setFixedSize(screenGeometry.width() / 4, 90);
    ui->mainButton->move(104, 0);
    ui->mainButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 32px;"
        "border-right: 2px solid grey;"
        "border-left: 2px solid grey;"
        "}"
        "QPushButton:hover {"
        "background-color: #4EB5FF;"
        "}"
        "QPushButton:pressed {"
        "background-color: #2194DE;"
        "}");
    //scorebutton
    ui->scoreButton->setCursor(Qt::PointingHandCursor);
    ui->scoreButton->setFont(FontManager::GetInstance()->getRegular());
    ui->scoreButton->setText("Оценки");
    ui->scoreButton->setFixedSize(screenGeometry.width() / 4, 90);
    ui->scoreButton->move(screenGeometry.width() / 4 + 104, 0);
    ui->scoreButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 32px;"
        "border-right: 2px solid grey;"
        "}"
        "QPushButton:hover {"
        "background-color: #4EB5FF;"
        "}"
        "QPushButton:pressed {"
        "background-color: #2194DE;"
        "}");
    //adminbutton
    ui->adminButton->setCursor(Qt::PointingHandCursor);
    ui->adminButton->setFont(FontManager::GetInstance()->getRegular());
    ui->adminButton->setText("Админ панель");
    ui->adminButton->setFixedSize(screenGeometry.width() / 4, 90);
    ui->adminButton->move(screenGeometry.width() / 2 + 104, 0);
    ui->adminButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 32px;"
        "border-right: 2px solid grey;"
        "}"
        "QPushButton:hover {"
        "background-color: #4EB5FF;"
        "}"
        "QPushButton:pressed {"
        "background-color: #2194DE;"
        "}");
    //exitbutton
    ui->exitButton->setCursor(Qt::PointingHandCursor);
    ui->exitButton->setFont(FontManager::GetInstance()->getRegular());
    ui->exitButton->setText("X");
    ui->exitButton->setFixedSize(screenGeometry.width() / 35, 20);
    ui->exitButton->move(screenGeometry.width() - screenGeometry.width() / 35, 0);
    ui->exitButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "border-left: 2px solid grey;"
        "border-bottom: 2px solid grey;"
        "}"
        "QPushButton:hover {"
        "background-color: #ed3124;"
        "border-left: 1px solid #ed3124;"
        "border-bottom: 1px solid #ed3124;"
        "}"
        "QPushButton:pressed {"
        "background-color: #C9261E;"
        "border-left: 1px solid #C9261E;"
        "border-bottom: 1px solid #C9261E;"
        "}");
    //profilebutton
    ui->profileButton->setIcon(QIcon(":/img/resources/profile.png"));
    ui->profileButton->setFixedSize(64, 64);
    // ui->profileButton->move(screenGeometry.width() / 2 + 20, 13);
    ui->profileButton->move(20, 13);
    ui->profileButton->setStyleSheet(
        "QPushButton {"
        "border-radius: 32px;"
        "padding: 6px;"
        "}"
        "QPushButton:hover {"
        "background-color: #4EB5FF;"
        "}"
        "QPushButton:pressed {"
        "background-color: #2194DE;"
        "}");
    ui->profileButton->setCursor(Qt::PointingHandCursor);

    if (auth->GetCurrentRole() == ADMIN)
    {
        ui->adminButton->show();
    }

    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height());
    ui->scrollArea->setWidgetResizable(true);

    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->scrollArea->resize(this->frameGeometry().width(),this->frameGeometry().height() - 42);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    int widgetwidth = MyWidget().width();
    int widgetheight = MyWidget().height();
    int vertspace = scr->availableGeometry().height()/ 17;
    int horizspace = scr->availableGeometry().width()/ 30;

    int columncnt = scr->availableGeometry().width()/ (widgetwidth + 2 * horizspace);

    //ui->scrollArea->resize(this->frameGeometry().width()-20,this->frameGeometry().height()-100);
    //ui->scrollAreaWidgetContents->setMinimumWidth(this->frameGeometry().width()-20); - ширина области в которой работает скролл
    ui->scrollAreaWidgetContents->setMinimumHeight((arrlen/columncnt)*(vertspace+widgetheight));//+350);
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().width());
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().height());
    ui->gridLayoutWidget->resize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->gridLayoutWidget->setMinimumHeight((arrlen/columncnt)*(2*vertspace+widgetheight));//+350);
    // ui->gridLayout->setColumnMinimumWidth(0,351);
    // ui->gridLayout->setColumnMinimumWidth(1,351);
    // ui->gridLayout->setColumnMinimumWidth(2,351);
    // ui->gridLayout->setColumnMinimumWidth(3,351);
    //ui->gridLayout->setRowMinimumHeight(0,0);
    ui->gridLayout->setVerticalSpacing(vertspace);
    ui->gridLayout->setHorizontalSpacing(horizspace);
    //ui->gridLayout->setContentsMargins(0,0,0,0);
    //ui->gridLayout->setGeometry(this->frameGeometry());
    for (int i = 0, j = 0, z = 0; z < arrlen; z++, j++){
        course[z] = new MyWidget();
        if (z % columncnt == 0){
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

void MainWindow::on_profileButton_clicked()
{
    Profile* profileWidget = new Profile(this);
    profileWidget->raise();
    profileWidget->show();
}

void MainWindow::on_exitButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение выхода", "Вы уверены, что хотите выйти?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        QApplication::quit();
}

