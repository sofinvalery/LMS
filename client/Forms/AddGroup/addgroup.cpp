#include "addgroup.h"
#include "ui_addgroup.h"
#include "ClientState/clientstate.h"
#include <QScreen>

AddGroup::AddGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddGroup)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-top: 3px solid lightgrey;"
        "}");

    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height() - 20);
    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height() - 20);
    this->move(0, 90);

}

AddGroup::~AddGroup()
{
    delete ui;
}

void AddGroup::on_studentBox_clicked()
{
    if (ui->teacherBox->isEnabled())
        ui->teacherBox->setEnabled(false);
    else
        ui->teacherBox->setEnabled(true);
}


void AddGroup::on_teacherBox_clicked()
{
    if (ui->studentBox->isEnabled())
        ui->studentBox->setEnabled(false);
    else
        ui->studentBox->setEnabled(true);
}

