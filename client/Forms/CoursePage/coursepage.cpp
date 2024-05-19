#include "coursepage.h"
#include "ui_coursepage.h"
#include "StyleManager/stylemanager.h"
#include "Forms/CoursePageComponents/componentswidgetfactory.h"
#include "Forms/CoursePage/CoursePageEditor/coursepageeditor.h"
#include "ClientState/clientstate.h"
#include "ClientManager/socketparser.h"

CoursePage::CoursePage(Course *course, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoursePage)
{
    connect(SocketParser::GetInstance(),SIGNAL(showTeacherScore()),this,SLOT(showScoreForTeacher()));
    ui->setupUi(this);
    this->course = course;
    ui->groupBox->setStyleSheet("background-color: white;");
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");
    this->move(0, 90);

    this->resize( StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    ui->scrollArea->setWidgetResizable(true);

    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->scrollArea->resize(this->frameGeometry().width(),this->frameGeometry().height() - 42);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    StyleManager::GetInstance()->setBlueButtonStyle(ui->EditCourseButton, ui->EditCourseButton->text(), true, 16, 13);
    ui->EditCourseButton->setFixedSize(ui->EditCourseButton->sizeHint().width() + 10, ui->EditCourseButton->sizeHint().height() + 10);
    ui->EditCourseButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->EditCourseButton->size().width() - 20, 30);

    if(ClientState::GetInstance()->getAuth()->GetCurrentRole()!=STUDENT)
    {
        StyleManager::GetInstance()->setBlueButtonStyle(ui->scoreButton, "Оценки", true, 16, 13);
        ui->scoreButton->setFixedSize(ui->scoreButton->sizeHint().width() + 10, ui->EditCourseButton->sizeHint().height() + 10);
        ui->scoreButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->scoreButton->size().width() - 20 - ui->EditCourseButton->size().width() - 20, 30);

        StyleManager::GetInstance()->setBlueButtonStyle(ui->checkButton, "Проверить", true, 16, 13);
        ui->checkButton->setFixedSize(ui->checkButton->sizeHint().width() + 10, ui->EditCourseButton->sizeHint().height() + 10);
        ui->checkButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->scoreButton->size().width() - 50 - ui->scoreButton->size().width() - 20 - ui->EditCourseButton->size().width() - 20, 30);
    }
    else{
        ui->scoreButton->close();
        ui->checkButton->close();
    }

    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: none;"
        "}");
    //scrollarea
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);
    ShowComponents();
    iconIMG = new QPixmap(course->GetAvaTitleUrl());
    ui->IconLabel->setPixmap(iconIMG->scaled(184, 120, Qt::IgnoreAspectRatio));
    ui->IconLabel->setFixedSize(ui->IconLabel->sizeHint().width(), ui->IconLabel->sizeHint().height());
    StyleManager::GetInstance()->setLabelStyle(ui->CourseNameLabel, course->GetTitle(), true, "black", true, 36);
    ui->CourseNameLabel->setFixedSize(ui->CourseNameLabel->sizeHint().width(), ui->CourseNameLabel->sizeHint().height());
    qInfo() << ui->CourseNameLabel->width() << " " << ui->CourseNameLabel->height();
    ui->CourseNameLabel->move(204, 40);

    ui->horizontalLine->setStyleSheet("border: 3px solid lightgrey;");
    ui->horizontalLine->setFixedSize(StyleManager::GetInstance()->getScreenWidth(), 3);
    ui->horizontalLine->move(0, 120);

    ui->verticalLine->setStyleSheet("border: 3px solid lightgrey;");
    ui->verticalLine->setFixedSize(3, 120);
    ui->verticalLine->move(184, 0);

    if(ClientState::GetInstance()->getAuth()->GetCurrentRole() == STUDENT){
        ui->EditCourseButton->hide();
    }

}

void CoursePage::ShowComponents()
{
    height = 140;
    ComponentsWidgetFactory<QString,QWidget,CourseComponent*> widgetFactory;
    for (int i = 0; i < course->getListComponents().size(); i ++){
        QWidget * temp = widgetFactory.get(course->getListComponents()[i]->getType())(course->getListComponents()[i]);
        widgets.append(temp);
        temp->setParent(ui->scrollAreaWidgetContents);
        temp->move(10, height+30);
        height += temp->height()+30;
        temp->show();
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(height+200);
    iconIMG = new QPixmap(course->GetAvaTitleUrl());
    ui->IconLabel->setPixmap(iconIMG->scaled(184, 120, Qt::IgnoreAspectRatio));

    StyleManager::GetInstance()->setLabelStyle(ui->CourseNameLabel, course->GetTitle(), true, "black", true, 20);
    ui->CourseNameLabel->setFixedSize(ui->CourseNameLabel->sizeHint().width(), ui->CourseNameLabel->sizeHint().height());
}

void CoursePage::CleanComponents()
{
    //qDeleteAll(widgets);
    for (int i = 0; i < widgets.size(); i++){
        widgets[i]->close();
        widgets[i]->deleteLater();
    }
    widgets.clear();
}

CoursePage::~CoursePage()
{
    delete ui;
}

void CoursePage::on_EditCourseButton_clicked()
{
    CoursePageEditor* editor = new CoursePageEditor(this, this);
    editor->move(StyleManager::GetInstance()->getScreenWidth() / 2 - 290, StyleManager::GetInstance()->getScreenHeight() / 2 - 250);
    editor->show();
}

void CoursePage::showScoreForTeacher()
{
    ClientState::GetInstance()->getMainwindow()->getDownload()->close();
    ClientState::GetInstance()->getMainwindow()->doAllButtonClicked();
    if (adminScore!=nullptr&&adminScore->isVisible())
    {
        adminScore->close();
        adminScore->deleteLater();
        adminScore=nullptr;
    }
    else if(adminScore!=nullptr && !adminScore->isVisible())
    {
        adminScore->deleteLater();
        adminScore=nullptr;
        adminScore = new AdminScore(course);
        adminScore->setParent(this);
        adminScore->raise();
        adminScore->move(StyleManager::GetInstance()->getScreenWidth() / 2 - 290, StyleManager::GetInstance()->getScreenHeight() / 2 - 250);
        adminScore->show();
    }
    else{
        adminScore = new AdminScore(course);
        adminScore->setParent(this);
        adminScore->raise();
        adminScore->move(StyleManager::GetInstance()->getScreenWidth() / 2 - 290, StyleManager::GetInstance()->getScreenHeight() / 2 - 250);
        adminScore->show();
    }
}

QList<QWidget *> CoursePage::getWidgets() const
{
    return widgets;
}


void CoursePage::on_scoreButton_clicked()
{
    ClientState::GetInstance()->getMainwindow()->getDownload()->raise();
    ClientState::GetInstance()->getMainwindow()->getDownload()->show();
    ClientState::GetInstance()->getMainwindow()->doAllButtonDisable();
    QJsonObject json;
    json["CourseId"]=int(course->GetCourseId());
    ClientManager::GetInstance()->SendJsonToServer(GETGROUPSBYCOURSEID,json);
}

void CoursePage::showCheckTask(QList<Submit*> submits)
{
    ClientState::GetInstance()->getMainwindow()->getDownload()->close();
    ClientState::GetInstance()->getMainwindow()->doAllButtonClicked();
    CheckDz* checkdz = new CheckDz(submits);
    checkdz->setParent(ClientState::GetInstance()->getMainwindow()->getWidget());
    checkdz->raise();
    checkdz->show();
}


void CoursePage::on_checkButton_clicked()
{
    ClientState::GetInstance()->getMainwindow()->getDownload()->raise();
    ClientState::GetInstance()->getMainwindow()->getDownload()->show();
    ClientState::GetInstance()->getMainwindow()->doAllButtonDisable();
    QJsonObject json;
    json["CourseId"]=int(course->GetCourseId());
    ClientManager::GetInstance()->SendJsonToServer(GETGROUPSBYCOURSEID,json);
}

