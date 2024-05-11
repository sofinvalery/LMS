#include "coursedz.h"
#include "ui_coursedz.h"
#include "StyleManager/stylemanager.h"
#include "CourseDzPage/coursedzpage.h"
#include "ClientState/clientstate.h"

CourseDz::CourseDz(CourseComponent * dz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDz)
{
    ui->setupUi(this);
    this->dz = qobject_cast<CourseTask*>(dz);
    icon = new QPixmap(":/img/resources/dzicon3.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->giveDzButton, this->dz->getTitle(), true, 20, 19);
    ui->giveDzButton->setFixedSize(ui->giveDzButton->sizeHint().width(), ui->giveDzButton->sizeHint().height());
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-radius: 5px;"
        "border: 2px solid lightgrey;"
        "}");
    if (ui->giveDzButton->width() + ui->LabelIMG->width() + 5 < this->width())
    {
        ui->groupBox->setFixedWidth(this->width());
    }
    else
    {
        ui->groupBox->setFixedWidth(ui->giveDzButton->width() + ui->LabelIMG->width() + 5);
    }
    this->setFixedWidth(ui->groupBox->width() + 1);
}

CourseDz::~CourseDz()
{
    delete ui;
}

void CourseDz::SetTextOnButton(QString buttontext)
{
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->giveDzButton, buttontext, true, 16, 15);
}

void CourseDz::on_giveDzButton_clicked()
{
    CourseDzPage* dzpage = new CourseDzPage(dz);
    dzpage->setParent(ClientState::GetInstance()->getMainwindow()->getWidget());
    dzpage->raise();
    dzpage->show();
}

