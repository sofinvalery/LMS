#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Forms/Notification/notification.h"
#include "Forms/CoursePage/coursepage.h"

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
    ui->editGroupButton->hide();

    Authentication* auth =new Authentication("sds","gtht");
    auth->SetInformationAfterAuthentication("Max","bbbbb",ADMIN,55,QList<QString>{"O725B"});

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

    if (auth->GetCurrentRole() == ADMIN)
    {
        ui->addCourseButton->show();
        ui->addPotokButton->show();
        ui->addGroupButton->show();
        ui->verticalLine->show();
        ui->editGroupButton->show();
    }

    this->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());

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
    //widget = new Score();
    widget = new Notification();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_mainButton_clicked()
{
    on_button_clicked(ui->mainButton);

    widget->close();
    delete widget;
    widget = new CoursesMPWidget();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_addCourseButton_clicked()
{
    on_button_clicked(ui->addCourseButton);

    widget->close();
    delete widget;
    widget = new CourseAdder();
    widget->setParent(this);
    widget->show();
    // Reconnect* reconnect = new Reconnect(this);
    // reconnect->raise();
    // reconnect->show();
}

void MainWindow::on_addPotokButton_clicked()
{
    on_button_clicked(ui->addPotokButton);

    widget->close();
    delete widget;
    widget = new PotokAdder();
    widget->setParent(this);
    widget->show();

}

void MainWindow::on_editGroupButton_clicked()
{
    on_button_clicked(ui->editGroupButton);

    widget->close();
    delete widget;
    widget = new groupEditor();
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_addGroupButton_clicked()
{
    on_button_clicked(ui->addGroupButton);

    widget->close();
    delete widget;
    widget = new AddGroup();
    widget->setParent(this);
    widget->show();
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

void MainWindow::showCoursePage(Course *course)
{
    widget->close();
    delete widget;
    widget = new CoursePage(course);
    widget->setParent(this);
    widget->show();
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}



