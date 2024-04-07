#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Forms/Profile/profile.h"
#include "Forms/Reconnect/reconnect.h"
#include <QMessageBox>

#define arrlen 15

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->adminButton->hide();

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    Authentication* auth =new Authentication("sds","gtht");
    auth->SetInformationAfterAuthentication("Max","bbbbb",ADMIN,55,QList<QString>{"O725B"});
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
    //ui->exitButton->setFont(FontManager::GetInstance()->getRegular());
    ui->exitButton->setText("");
    ui->exitButton->setIcon(QIcon(":/img/resources/kap.jpg"));
    ui->exitButton->setFixedSize(64, 64);
    ui->exitButton->move(screenGeometry.width() - 84, 13);
    ui->exitButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "border-left: 2px solid grey;"
        "}"
        "QPushButton:hover {"
        "background-color: #ed3124;"
        "}"
        "QPushButton:pressed {"
        "background-color: #C9261E;"
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
    courses->setParent(this);
    //courses->move(0, ui->profileButton->height()+13);
    courses->move(0, 90);
    courses->show();


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

void MainWindow::on_mainButton_clicked()
{
    Reconnect* reconnect = new Reconnect(this);
    reconnect->raise();
    reconnect->exec();
}

void MainWindow::on_exitButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение выхода", "Вы уверены, что хотите выйти?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        QApplication::quit();
}

