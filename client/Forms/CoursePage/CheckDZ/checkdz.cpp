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
    HeightLine=80;
    for(auto sub: submitList)
    {
        CheckDzComponents* check = new CheckDzComponents(sub, ui->scrollAreaWidgetContents);
        check->move(20, HeightLine);
        HeightLine+=100;
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(HeightLine+200);
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

