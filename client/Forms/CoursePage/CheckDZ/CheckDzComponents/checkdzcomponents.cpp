#include "checkdzcomponents.h"
#include "ui_checkdzcomponents.h"
#include "StyleManager/stylemanager.h"
#include "ClientState/clientstate.h"

CheckDzComponents::CheckDzComponents(Submit* submit,QList<Submit*> submitList, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CheckDzComponents)
{
    ui->setupUi(this);
    ui->pushButton->lower();
    this->submitList=submitList;
    CourseTask* task = qobject_cast<CourseTask*>(submit->work);
    StyleManager::GetInstance()->setLabelStyle(ui->titleLbl, task->getTitle(), true, "black", true, 20);
    ui->titleLbl->setFixedSize(ui->titleLbl->sizeHint().width(), ui->titleLbl->sizeHint().height());
    sub = submit;
    StyleManager::GetInstance()->setLabelStyle(ui->fioLbl, submit->student->GetLogin(), false, "black", true, 18);
    ui->fioLbl->setFixedSize(ui->fioLbl->sizeHint().width(), ui->fioLbl->sizeHint().height());
    ui->fioLbl->move(ui->titleLbl->width() + 40, ui->titleLbl->y());

    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-radius: 5px;"
        "border: 2px solid lightgrey;"
        "}");

    StyleManager::GetInstance()->setLabelStyle(ui->maxMarkLbl, QString::number(task->getMaxMark()), false, "black", true, 18);
    ui->maxMarkLbl->setFixedSize(ui->maxMarkLbl->sizeHint().width(), ui->maxMarkLbl->sizeHint().height());
    ui->maxMarkLbl->move(ui->fioLbl->x() + ui->fioLbl->width() + 40, ui->titleLbl->y());

    StyleManager::GetInstance()->setSimpleButtonStyle(ui->pushButton, "", false, 1, 1);
}

CheckDzComponents::~CheckDzComponents()
{
    delete ui;
}

void CheckDzComponents::on_pushButton_clicked()
{
    DzMarkEditer* editer = new DzMarkEditer(sub,submitList);
    editer->setParent(ClientState::GetInstance()->getMainwindow()->getWidget());
    editer->raise();
    editer->show();
}

