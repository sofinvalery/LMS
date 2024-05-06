#include "profile.h"
#include "ui_profile.h"
#include "StyleManager/stylemanager.h"
#include "../common/authentication/authentication.h"
#include "ClientState/clientstate.h"

Profile::Profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->move(15, 80);
    this->setStyleSheet("background-color: white;");

    Authentication* auth = ClientState::GetInstance()->getAuth();
    QString role;
    EnumRoles roles = auth->GetCurrentRole();
    switch(roles) {
        case STUDENT:
            role = "Студент";
            break;
        case ADMIN:
            role = "Администратор";
            break;
        case TEACHER:
            role = "Преподаватель";
            break;
        }

    StyleManager::GetInstance()->setLabelStyle(ui->profileWidgetLbl, "Профиль", true, "white", true, 20, true);
    ui->profileWidgetLbl->setFixedSize(this->width(), 50);
    ui->profileWidgetLbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->profileWidgetLbl->move(this->size().width() / 2 - ui->profileWidgetLbl->size().width() / 2, 0);

    ui->line->setStyleSheet("border: 2px solid lightgrey;");

    StyleManager::GetInstance()->setLabelStyle(ui->nameLbl, "ФИО:", true, "black", true, 16);
    ui->nameLbl->setFixedSize(ui->nameLbl->sizeHint().width(), ui->nameLbl->sizeHint().height());
    ui->nameLbl->move(20, 80);

    StyleManager::GetInstance()->setLabelStyle(ui->name, auth->GetFIO(), false, "black", true, 16);
    ui->name->setFixedSize(ui->name->sizeHint().width(), ui->name->sizeHint().height());
    ui->name->move(80, 80);

    StyleManager::GetInstance()->setLabelStyle(ui->groupNameLbl, "Группа:", true, "black", true, 16);
    ui->groupNameLbl->setFixedSize(ui->groupNameLbl->sizeHint().width(), ui->groupNameLbl->sizeHint().height());
    ui->groupNameLbl->move(20, 140);

    QString group;
    for(QString temp:auth->getGroups())
        group+=" "+temp;
    StyleManager::GetInstance()->setLabelStyle(ui->groupName, group, false, "black", true, 16);
    ui->groupName->setFixedSize(ui->groupName->sizeHint().width(), ui->groupName->sizeHint().height());
    ui->groupName->move(100, 140);

    StyleManager::GetInstance()->setLabelStyle(ui->accountLbl, "Роль:", true, "black", true, 16);
    ui->accountLbl->setFixedSize(ui->accountLbl->sizeHint().width(), ui->accountLbl->sizeHint().height());
    ui->accountLbl->move(20, 200);

    StyleManager::GetInstance()->setLabelStyle(ui->account, role, false, "black", true, 16);
    ui->account->setFixedSize(ui->account->sizeHint().width(), ui->account->sizeHint().height());
    ui->account->move(80, 200);
}

Profile::~Profile()
{
    delete ui;
}
