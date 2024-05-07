#include "coursedownload.h"
#include "ui_coursedownload.h"
#include "StyleManager/stylemanager.h"

CourseDownload::CourseDownload(CourseComponent * pdf, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDownload)
{
    ui->setupUi(this);
    this->pdf =  qobject_cast<CoursePdf*>(pdf);
    icon = new QPixmap(":/img/resources/dowloadicon.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
    StyleManager::GetInstance()->setLinkButtonStyle(ui->DownloadButton, this->pdf->getTitle(), true, 16, 15);
    ui->DownloadButton->setFixedSize(ui->DownloadButton->sizeHint().width(), ui->DownloadButton->sizeHint().height());
}

CourseDownload::~CourseDownload()
{
    delete ui;
}

void CourseDownload::SetTextOnButton(QString buttontext)
{
    StyleManager::GetInstance()->setLinkButtonStyle(ui->DownloadButton, buttontext, true, 16, 15);
    ui->DownloadButton->setFixedSize(ui->DownloadButton->sizeHint().width(), ui->DownloadButton->sizeHint().height());
}
