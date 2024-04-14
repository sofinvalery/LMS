#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../ClientState/clientstate.h"
#include "../../ClientManager/clientmanager.h"
#include "../../ClientManager/socketparser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    connect(SocketParser::GetInstance(),SIGNAL(getMainPage()),this,SLOT(ShowManePage()));
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    ui->addCourseButton->hide();
    ui->addPotokButton->hide();
    ui->addGroupButton->hide();
    ui->verticalLine->hide();

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    //mainbutton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->mainButton, "Курсы", "bold", 20, 13);
    ui->mainButton->setFixedSize(96, 45);
    ui->mainButton->move(104, 23);
    //scorebutton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->scoreButton, "Оценки", "bold", 20, 18);
    ui->scoreButton->setFixedSize(96, 45);
    ui->scoreButton->move(220, 23);
    //verticalLine
    ui->verticalLine->move(323, 0);
    ui->verticalLine->setStyleSheet(
        "QFrame {"
        "border: 3px solid lightgrey;"
        "}");
    //addCoursebutton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addCourseButton, "Новый курс", "bold", 20, 18);
    ui->addCourseButton->setFixedSize(128, 30);
    ui->addCourseButton->move(336, 30);
    //addPotokButton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addPotokButton, "Новый поток", "bold", 20, 18);
    ui->addPotokButton->setFixedSize(156, 30);
    ui->addPotokButton->move(492, 30);
    //addGroupButton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addGroupButton, "Новая группа", "bold", 20, 18);
    ui->addGroupButton->setFixedSize(156, 30);
    ui->addGroupButton->move(668, 30);
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

    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height());
    download->setParent(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ShowManePage()
{
    download->close();
    if ( ClientState::GetInstance()->getAuth()->GetCurrentRole() == ADMIN)
    {
        ui->addCourseButton->show();
        ui->addPotokButton->show();
        ui->addGroupButton->show();
        ui->verticalLine->show();
    }
    widget = new CoursesMPWidget();
    widget->setParent(this);
    widget->show();

}

void MainWindow::on_profileButton_clicked()
{
    widget->close();
    delete widget;
    widget = new Profile();
    widget->setParent(this);
    widget->show();

}

void MainWindow::on_scoreButton_clicked()
{
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->mainButton, "Курсы", "bold", 20, 18);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->scoreButton, "Оценки", "bold", 20, 13);

    widget->close();
    delete widget;
    widget = new Score();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_mainButton_clicked()
{
    StyleManager::GetInstance()->setBlueButtonStyle(ui->mainButton, "Курсы", "bold", 20, 13);
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->scoreButton, "Оценки", "bold", 20, 18);
    widget->close();
    download->show();
    delete widget;
    ClientManager::GetInstance()->Send(GETMAINPAGE,ClientState::GetInstance()->getAuth()->Serialize());
}

void MainWindow::on_addCourseButton_clicked()
{

}

void MainWindow::on_addPotokButton_clicked()
{
    Profile* profileWidget = new Profile(this);
    profileWidget->raise();
    profileWidget->show();
}


void MainWindow::on_addGroupButton_clicked()
{

}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

