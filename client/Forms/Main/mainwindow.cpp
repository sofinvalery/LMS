#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    ui->addCourseButton->hide();
    ui->addPotokButton->hide();
    ui->addGroupButton->hide();
    ui->verticalLine->hide();

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    Authentication* auth =new Authentication("sds","gtht");
    auth->SetInformationAfterAuthentication("Max","bbbbb",ADMIN,55,QList<QString>{"O725B"});

    //mainbutton
    ui->mainButton->setCursor(Qt::PointingHandCursor);
    ui->mainButton->setFont(FontManager::GetInstance()->getBold());
    ui->mainButton->setText("Курсы");
    ui->mainButton->setFixedSize(96, 45);
    ui->mainButton->move(104, 23);
    ui->mainButton->setStyleSheet(
        "QPushButton {"
        "background-color: #4AB8FF;"
        "border-radius: 13px;"
        "border: none;"
        "color: white;"
        "font-size: 20px;"
        "}"
        "QPushButton:hover {"
        "background-color: #2194DE;"
        "}"
        "QPushButton:pressed {"
        "background-color: #0E5FA8;"
        "}");
    //scorebutton
    ui->scoreButton->setCursor(Qt::PointingHandCursor);
    ui->scoreButton->setFont(FontManager::GetInstance()->getBold());
    ui->scoreButton->setText("Оценки");
    ui->scoreButton->setFixedSize(96, 30);
    ui->scoreButton->move(220, 30);
    ui->scoreButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 20px;"
        "}"
        "QPushButton:pressed {"
        "font-size: 18px;"
        "}");
    //verticalLine
    ui->verticalLine->move(323, 0);
    ui->verticalLine->setStyleSheet(
        "QFrame {"
        "border: 3px solid lightgrey;"
        "}");
    //addCoursebutton
    ui->addCourseButton->setCursor(Qt::PointingHandCursor);
    ui->addCourseButton->setFont(FontManager::GetInstance()->getBold());
    ui->addCourseButton->setText("Новый курс");
    ui->addCourseButton->setFixedSize(128, 30);
    ui->addCourseButton->move(336, 30);
    ui->addCourseButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 20px;"
        "}"
        "QPushButton:pressed {"
        "font-size: 18px;"
        "}");
    //addPotokButton
    ui->addPotokButton->setCursor(Qt::PointingHandCursor);
    ui->addPotokButton->setFont(FontManager::GetInstance()->getBold());
    ui->addPotokButton->setText("Новый поток");
    ui->addPotokButton->setFixedSize(156, 30);
    ui->addPotokButton->move(492, 30);
    ui->addPotokButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 20px;"
        "}"
        "QPushButton:pressed {"
        "font-size: 18px;"
        "}");
    //addGroupButton
    ui->addGroupButton->setCursor(Qt::PointingHandCursor);
    ui->addGroupButton->setFont(FontManager::GetInstance()->getBold());
    ui->addGroupButton->setText("Новая группа");
    ui->addGroupButton->setFixedSize(156, 30);
    ui->addGroupButton->move(668, 30);
    ui->addGroupButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 20px;"
        "}"
        "QPushButton:pressed {"
        "font-size: 18px;"
        "}");
    //exitbutton
    ui->exitButton->setIcon(QIcon(":/img/resources/exit.png"));
    ui->exitButton->setFixedSize(64, 64);
    ui->exitButton->move(screenGeometry.width() - 84, 13);
    ui->exitButton->setStyleSheet(
        "QPushButton {"
        "border-radius: 10px;"
        "padding: 0px;"
        "}"
        "QPushButton:hover {"
        "background-color: #ed3124;"
        "}"
        "QPushButton:pressed {"
        "background-color: #C9261E;"
        "}");
    ui->exitButton->setCursor(Qt::PointingHandCursor);
    //profilebutton
    ui->profileButton->setIcon(QIcon(":/img/resources/profile.png"));
    ui->profileButton->setFixedSize(64, 64);
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
        ui->addCourseButton->show();
        ui->addPotokButton->show();
        ui->addGroupButton->show();
        ui->verticalLine->show();
    }


    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height());
    courses->setParent(this);
    profile->setParent(this);
    score->setParent(this);
    profile->hide();
    score->hide();
    courses->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_profileButton_clicked()
{
    courses->hide();
    score->hide();
    profile->show();
}

void MainWindow::on_scoreButton_clicked()
{
    courses->hide();
    profile->hide();
    score->show();
}

void MainWindow::on_mainButton_clicked()
{
    profile->hide();
    score->hide();
    courses->show();
}

void MainWindow::on_addCourseButton_clicked()
{

}

void MainWindow::on_addPotokButton_clicked()
{

}

void MainWindow::on_addGroupButton_clicked()
{

}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

