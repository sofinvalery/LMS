#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StyleManager/stylemanager.h"
#include "Forms/Reconnect/reconnect.h"

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
    ui->addCourseButton->setFixedSize(128, 45);
    ui->addCourseButton->move(336, 23);
    //addPotokButton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addPotokButton, "Новый поток", "bold", 20, 18);
    ui->addPotokButton->setFixedSize(156, 45);
    ui->addPotokButton->move(492, 23);
    //addGroupButton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addGroupButton, "Новая группа", "bold", 20, 18);
    ui->addGroupButton->setFixedSize(156, 45);
    ui->addGroupButton->move(668, 23);
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowManePage()
{
    widget = new CoursesMPWidget();
    widget->setParent(this);
    widget->show();

}

void MainWindow::on_profileButton_clicked()
{
    widget->close();
    widget = new Profile();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_scoreButton_clicked()
{
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->mainButton, "Курсы", "bold", 20, 18);
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addGroupButton, "Новая группа", "bold", 20, 18);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->scoreButton, "Оценки", "bold", 20, 13);
    widget->close();
    widget = new Score();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_mainButton_clicked()
{
    StyleManager::GetInstance()->setBlueButtonStyle(ui->mainButton, "Курсы", "bold", 20, 13);
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->scoreButton, "Оценки", "bold", 20, 18);
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addGroupButton, "Новая группа", "bold", 20, 18);
    widget->close();
    widget = new CoursesMPWidget();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_addCourseButton_clicked()
{
    widget->close();
    Reconnect* reconnect = new Reconnect(this);
    reconnect->raise();
    reconnect->show();
}

void MainWindow::on_addPotokButton_clicked()
{
    widget->close();

    widget = new PotokAdder();
    widget->setParent(this);
    widget->show();

}

void MainWindow::on_addGroupButton_clicked()
{
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->mainButton, "Курсы", "bold", 20, 18);
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->scoreButton, "Оценки", "bold", 20, 18);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->addGroupButton, "Новая группа", "bold", 20, 13);
    widget->close();
    widget = new AddGroup();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

