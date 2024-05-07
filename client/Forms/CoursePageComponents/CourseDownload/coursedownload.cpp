#include "coursedownload.h"
#include "ui_coursedownload.h"
#include "StyleManager/stylemanager.h"
#include "ClientManager/clientmanager.h"

CourseDownload::CourseDownload(CourseComponent * pdf, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDownload)
{
    ui->setupUi(this);
    this->pdf =  qobject_cast<CourseMediaFiles*>(pdf);
    icon = new QPixmap(":/img/resources/dowloadicon.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
    StyleManager::GetInstance()->setLinkButtonStyle(ui->DownloadButton, this->pdf->getTitle(), true, 20, 19);
    ui->DownloadButton->setFixedSize(ui->DownloadButton->sizeHint().width(), ui->DownloadButton->sizeHint().height());
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-radius: 5px;"
        "border: 2px solid lightgrey;"
        "}");
    if (ui->DownloadButton->width() + ui->LabelIMG->width() + 5 < this->width())
    {
        ui->groupBox->setFixedWidth(this->width());
    }
    else
    {
        ui->groupBox->setFixedWidth(ui->DownloadButton->width() + ui->LabelIMG->width() + 5);
    }
    this->setFixedWidth(ui->groupBox->width() + 1);
}

CourseDownload::~CourseDownload()
{
    delete ui;
}

void CourseDownload::on_DownloadButton_clicked()
{
    ClientManager::GetInstance()->SendRequestFileToServer(pdf->getUrl());
}

void CourseDownload::SetTextOnButton(QString buttontext)
{
    StyleManager::GetInstance()->setLinkButtonStyle(ui->DownloadButton, buttontext, true, 16, 15);
    ui->DownloadButton->setFixedSize(ui->DownloadButton->sizeHint().width(), ui->DownloadButton->sizeHint().height());
}
