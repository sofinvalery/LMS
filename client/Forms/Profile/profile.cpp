#include "profile.h"
#include "ui_profile.h"
#include "StyleManager/stylemanager.h"

Profile::Profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-top: 3px solid lightgrey;"
        "}");

    this->resize( StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight() - 20);
    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height() - 20);
    this->move(0, 90);
}

Profile::~Profile()
{
    delete ui;
}
