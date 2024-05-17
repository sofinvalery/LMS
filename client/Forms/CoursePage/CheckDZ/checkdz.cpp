#include "checkdz.h"
#include "ui_checkdz.h"
#include "StyleManager/stylemanager.h"
#include "CheckDzComponents/checkdzcomponents.h"
#include "../../../../common/authentication/authentication.h"
#include "../../../../common/course/course_components/coursetask.h"

CheckDz::CheckDz(QList<Submit*> submitList, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CheckDz)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");
    this->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    ui->scrollArea->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);

    Submit* sub=new Submit();
    sub->student = new Authentication("o725b12", "3123");
    sub->work = new CourseTask(10, 10, "dsada", 15, 1, "pdf", "dsa", QDate::currentDate(), 4, "dasd", "titleName");

    CheckDzComponents* check = new CheckDzComponents(sub, this);
    check->move(20, 60);

    StyleManager::GetInstance()->setCustomButtonStyle(ui->exitButton, "<--", "#E65D4F", true, 16, 4);
    ui->exitButton->move(20, 20);
}

CheckDz::~CheckDz()
{
    delete ui;
}

void CheckDz::on_exitButton_clicked()
{
    this->close();
    delete this;
}

