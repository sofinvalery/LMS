#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../ClientState/clientstate.h"
#include "../../ClientManager/clientmanager.h"
#include "../../ClientManager/socketparser.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    connect(SocketParser::GetInstance(),SIGNAL(getMainPage()),this,SLOT(ShowManePage()),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getAddPotok()),this,SLOT(ShowAddingPotok()),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getAddGroup()),this,SLOT(ShowAddingGroup()),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getAddCourse()),this,SLOT(ShowAddingCourse()),Qt::QueuedConnection);
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    ui->addCourseButton->hide();
    ui->addPotokButton->hide();
    ui->addGroupButton->hide();
    ui->verticalLine->hide();
    ui->editGroupButton->hide();

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    //mainbutton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->mainButton, "Курсы", true, 20, 13);
    ui->mainButton->setFixedSize(96, 45);
    ui->mainButton->move(104, 23);
    //scorebutton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->scoreButton, "Оценки", true, 20, 18);
    ui->scoreButton->setFixedSize(96, 45);
    ui->scoreButton->move(220, 23);
    //verticalLine
    ui->verticalLine->move(323, 0);
    ui->verticalLine->setStyleSheet(
        "QFrame {"
        "border: 3px solid lightgrey;"
        "}");
    //editGroupbutton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->editGroupButton, "Изменить группу", true, 20, 18);
    ui->editGroupButton->setFixedSize(200, 45);
    ui->editGroupButton->move(848, 23);
    //addCoursebutton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addCourseButton, "Новый курс", true, 20, 18);
    ui->addCourseButton->setFixedSize(128, 45);
    ui->addCourseButton->move(336, 23);
    //addPotokButton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addPotokButton, "Новый поток", true, 20, 18);
    ui->addPotokButton->setFixedSize(156, 45);
    ui->addPotokButton->move(492, 23);
    //addGroupButton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addGroupButton, "Новая группа", true, 20, 18);
    ui->addGroupButton->setFixedSize(156, 45);
    ui->addGroupButton->move(668, 23);
    //exitbutton
    ui->exitButton->setIcon(QIcon(":/img/resources/exit.png"));
    ui->exitButton->setFixedSize(64, 64);
    ui->exitButton->move(StyleManager::GetInstance()->getScreenWidth() - 84, 13);
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
        ui->editGroupButton->show();
    }
    widget = new CoursesMPWidget();
    widget->setParent(this);
    widget->show();

}

void MainWindow::ShowAddingPotok()
{
    download->close();
    widget = new PotokAdder();
    widget->setParent(this);
    widget->show();
}

void MainWindow::ShowAddingGroup()
{
    download->close();
    widget = new AddGroup();
    widget->setParent(this);
    widget->show();

}

void MainWindow::ShowAddingCourse()
{
    download->close();
    widget = new CourseAdder();
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
    on_button_clicked(ui->scoreButton);

    widget->close();
    delete widget;
    widget = new Score();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_mainButton_clicked()
{
    on_button_clicked(ui->mainButton);

    widget->close();
    download->show();
    delete widget;
    ClientManager::GetInstance()->SendJsonToServer(GETMAINPAGE,ClientState::GetInstance()->getAuth()->Serialize());
}

void MainWindow::on_addCourseButton_clicked()
{
    on_button_clicked(ui->addCourseButton);

    widget->close();
    download->show();
    delete widget;
    ClientManager::GetInstance()->SendJsonToServer(GETINFOFORAADDINGCOURSE,ClientState::GetInstance()->getAuth()->Serialize());
}

void MainWindow::on_addPotokButton_clicked()
{
    on_button_clicked(ui->addPotokButton);
    widget->close();
    download->show();
    delete widget;
    ClientManager::GetInstance()->SendJsonToServer(GETINFOFORADDINGPOTOK,ClientState::GetInstance()->getAuth()->Serialize());
}

void MainWindow::on_editGroupButton_clicked()
{
    on_button_clicked(ui->editGroupButton);

    widget->close();
    widget = new groupEditor();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_addGroupButton_clicked()
{
    on_button_clicked(ui->addGroupButton);
    widget->close();
    download->show();
    delete widget;
    ClientManager::GetInstance()->SendJsonToServer(GETINFOFORADDINGGROUP,ClientState::GetInstance()->getAuth()->Serialize());
}

void MainWindow::on_button_clicked(QPushButton* clickedButton)
{
    StyleManager::GetInstance()->setBlueButtonStyle(clickedButton, clickedButton->text(), true, 20, 13);

    QList<QPushButton*> buttons = {ui->scoreButton, ui->mainButton, ui->addGroupButton, ui->editGroupButton, ui->addCourseButton, ui->addPotokButton};
    for(QPushButton* button : buttons) {
        if(button != clickedButton) {
            StyleManager::GetInstance()->setSimpleButtonStyle(button, button->text(), true, 20, 18);
        }
    }
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}



