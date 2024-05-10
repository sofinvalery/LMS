#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../ClientState/clientstate.h"
#include "../../ClientManager/clientmanager.h"
#include "../../ClientManager/socketparser.h"
#include "Forms/CoursePage/coursepage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    connect(SocketParser::GetInstance(),SIGNAL(getScore()),this,SLOT(ShowScore()),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getMainPage()),this,SLOT(ShowManePage()),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getAddPotok()),this,SLOT(ShowAddingPotok()),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getAddGroup()),this,SLOT(ShowAddingGroup()),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getCourseComponents(Course*)),this,SLOT(ShowCoursePage(Course*)),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getAddCourse()),this,SLOT(ShowAddingCourse()),Qt::QueuedConnection);
    connect(SocketParser::GetInstance(),SIGNAL(getEditGroup()),this,SLOT(ShowEditGroup()),Qt::QueuedConnection);
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    ui->addCourseButton->hide();
    ui->addPotokButton->hide();
    ui->addGroupButton->hide();
    ui->verticalLine->hide();
    ui->editGroupButton->hide();

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    StyleManager::GetInstance()->setSimpleButtonStyle(ui->loaderButton, "", false, 1, 1);
    ui->loaderButton->setIconSize(QSize(48, 48));
    ui->loaderButton->setIcon(QIcon(":/img/resources/dowloadicon.png"));
    ui->loaderButton->setFixedSize(ui->loaderButton->sizeHint().width(), ui->loaderButton->sizeHint().height());
    ui->loaderButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->loaderButton->size().width() - 104, 13);

    StyleManager::GetInstance()->setSimpleButtonStyle(ui->loaderButton, "", false, 1, 1);
    ui->loaderButton->setIconSize(QSize(48, 48));
    ui->loaderButton->setIcon(QIcon(":/img/resources/dowloadicon.png"));
    ui->loaderButton->setFixedSize(ui->loaderButton->sizeHint().width(), ui->loaderButton->sizeHint().height());
    ui->loaderButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->loaderButton->size().width() - 104, 13);

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
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->profileButton, "", true, 20, 18);

    //QScreen* scr = QGuiApplication::primaryScreen();

    this->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());

    download->setParent(this);
    dialogLoader->setParent(this);
    dialogLoader->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ShowManePage()
{
    download->close();
    doAllButtonClicked();
    if ( ClientState::GetInstance()->getAuth()->GetCurrentRole() == ADMIN)
    {
        ui->addCourseButton->show();
        ui->addPotokButton->show();
        ui->addGroupButton->show();
        ui->verticalLine->show();
        ui->editGroupButton->show();

        ui->scoreButton->hide();
        ui->verticalLine->move(220, 0);
        ui->addCourseButton->move(240, 23);
        ui->addPotokButton->move(396, 23);
        ui->addGroupButton->move(572, 23);
        ui->editGroupButton->move(752, 23);
    }
    widget = new CoursesMPWidget();
    widget->setParent(this);
    widget->show();
    raiseDownloadAndLoader();

}

void MainWindow::ShowAddingPotok()
{
    download->close();
    doAllButtonClicked();
    widget = new PotokAdder();
    widget->setParent(this);
    widget->show();
    raiseDownloadAndLoader();
}

void MainWindow::ShowAddingGroup()
{
    download->close();
    doAllButtonClicked();
    widget = new AddGroup();
    widget->setParent(this);
    widget->show();
    raiseDownloadAndLoader();
}

void MainWindow::ShowAddingCourse()
{
    download->close();
    doAllButtonClicked();
    widget = new CourseAdder();
    widget->setParent(this);
    widget->show();
    raiseDownloadAndLoader();
}

void MainWindow::ShowEditGroup()
{
    download->close();
    doAllButtonClicked();
    widget = new groupEditor();
    widget->setParent(this);
    widget->show();
    raiseDownloadAndLoader();
}

void MainWindow::ShowCoursePage(Course *course)
{
    download->close();
    doAllButtonClicked();
    if (widget != nullptr)
    {
        widget->close();
        delete widget;
        widget = nullptr;
    }
    widget = new CoursePage(course);
    widget->setParent(this);
    widget->show();
    raiseDownloadAndLoader();
}

void MainWindow::ShowScore()
{
    download->close();
    doAllButtonClicked();
    if (widget != nullptr)
    {
        widget->close();
        delete widget;
        widget = nullptr;
    }
    widget = new Score();
    widget->setParent(this);
    widget->show();
    raiseDownloadAndLoader();
}

void MainWindow::on_profileButton_clicked()
{
    if(dialogProfile==nullptr)
    {
        dialogProfile = new Profile();
        dialogProfile->setParent(this);
    }
    if (dialogProfile->isVisible())
    {
        StyleManager::GetInstance()->setSimpleButtonStyle(ui->profileButton, ui->profileButton->text(), true, 20, 18);
        dialogProfile->close();
    }
    else
    {
        StyleManager::GetInstance()->setBlueButtonStyle(ui->profileButton, ui->profileButton->text(), true, 20, 32);
        dialogProfile->show();
    }
    raiseDownloadAndLoader();
}

void MainWindow::on_scoreButton_clicked()
{
    on_button_clicked(ui->scoreButton);
    download->raise();
    download->show();
    if (widget != nullptr)
    {
        widget->close();
        delete widget;
        widget = nullptr;
    }
    QJsonObject json;
    QJsonArray components;
    for (auto & user : ClientState::GetInstance()->getListCourses())
        components.append((int)user->GetCourseId());
    json["ids"]=components;
    ClientManager::GetInstance()->SendJsonToServer(GETALLCOURSECOMPONENTS,json);
    raiseDownloadAndLoader();
}

void MainWindow::on_mainButton_clicked()
{
    on_button_clicked(ui->mainButton);
    download->raise();
    download->show();
    if (widget != nullptr)
    {
        widget->close();
        delete widget;
        widget = nullptr;
    }
    ClientManager::GetInstance()->SendJsonToServer(GETMAINPAGE,ClientState::GetInstance()->getAuth()->Serialize());
    raiseDownloadAndLoader();
}

void MainWindow::on_addCourseButton_clicked()
{
    on_button_clicked(ui->addCourseButton);

    download->show();
    if (widget != nullptr)
    {
        widget->close();
        delete widget;
        widget = nullptr;
    }
    ClientManager::GetInstance()->SendJsonToServer(GETINFOFORAADDINGCOURSE,ClientState::GetInstance()->getAuth()->Serialize());
    raiseDownloadAndLoader();
}

void MainWindow::on_addPotokButton_clicked()
{
    on_button_clicked(ui->addPotokButton);
    download->show();
    if (widget != nullptr)
    {
        widget->close();
        delete widget;
        widget = nullptr;
    }
    ClientManager::GetInstance()->SendJsonToServer(GETINFOFORADDINGPOTOK,ClientState::GetInstance()->getAuth()->Serialize());
    raiseDownloadAndLoader();
}

void MainWindow::on_editGroupButton_clicked()
{
    on_button_clicked(ui->editGroupButton);
    download->show();
    if (widget != nullptr)
    {
        widget->close();
        delete widget;
        widget = nullptr;
    }
    ClientManager::GetInstance()->SendJsonToServer(GETINFOFOREDITGROUP,ClientState::GetInstance()->getAuth()->Serialize());
    raiseDownloadAndLoader();
}

void MainWindow::doAllButtonClicked()
{
    QList<QPushButton*> buttons = {ui->scoreButton, ui->mainButton, ui->addGroupButton, ui->editGroupButton, ui->addCourseButton, ui->addPotokButton, ui->profileButton};
    for (auto temp : buttons)
    {
        temp->setEnabled(true);
    }
}

Download *MainWindow::getDownload() const
{
    return download;
}

void MainWindow::on_addGroupButton_clicked()
{
    on_button_clicked(ui->addGroupButton);
    download->raise();
    download->show();
    if (widget != nullptr)
    {
        widget->close();
        delete widget;
        widget = nullptr;
    }
    ClientManager::GetInstance()->SendJsonToServer(GETINFOFORADDINGGROUP,ClientState::GetInstance()->getAuth()->Serialize());
    raiseDownloadAndLoader();
}

void MainWindow::on_button_clicked(QPushButton* clickedButton)
{
    if (clickedButton != ui->profileButton)
    {
        StyleManager::GetInstance()->setBlueButtonStyle(clickedButton, clickedButton->text(), true, 20, 13);
    }
    QList<QPushButton*> buttons = {ui->scoreButton, ui->mainButton, ui->addGroupButton, ui->editGroupButton, ui->addCourseButton, ui->addPotokButton, ui->profileButton};
    for(QPushButton* button : buttons) {
        if(button != clickedButton) {
            StyleManager::GetInstance()->setSimpleButtonStyle(button, button->text(), true, 20, 18);
            button->setEnabled(false);
        }
    }
}

void MainWindow::clickCoursePage(Course *course)
{
    download->raise();
    QList<QPushButton*> buttons = {ui->scoreButton, ui->mainButton, ui->addGroupButton, ui->editGroupButton, ui->addCourseButton, ui->addPotokButton, ui->profileButton};
    for(QPushButton* button : buttons) {
            StyleManager::GetInstance()->setSimpleButtonStyle(button, button->text(), true, 20, 18);
            button->setEnabled(false);
    }
    download->show();
    QJsonObject json;
    json["id"]=(int)course->GetCourseId();
    ClientManager::GetInstance()->SendJsonToServer(GETCOURSECOMPONENTS,json);
    raiseDownloadAndLoader();

}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_loaderButton_clicked()
{
    if (dialogLoader->isVisible())
    {
        dialogLoader->close();
    }
    else
    {
        dialogLoader->show();
    }
    raiseDownloadAndLoader();
}

Loader *MainWindow::getDialogLoader() const
{
    return dialogLoader;
}

void MainWindow::raiseDownloadAndLoader()
{
    if(dialogProfile!=nullptr)
    {
    if (dialogProfile->isVisible())
        {
            dialogProfile->raise();
            StyleManager::GetInstance()->setBlueButtonStyle(ui->profileButton, ui->profileButton->text(), true, 20, 32);
        }
    }
    if(dialogLoader->isVisible())
        dialogLoader->raise();
}
