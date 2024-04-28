#include "coursedownload.h"
#include "ui_coursedownload.h"
#include "StyleManager/stylemanager.h"

CourseDownload::CourseDownload(CoursePdf * pdf, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDownload)
{
    ui->setupUi(this);
    this->pdf = pdf;
    icon = new QPixmap(":/img/resources/dowloadicon.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
    StyleManager::GetInstance()->setLinkButtonStyle(ui->DownloadButton, "download", false, 9, -2);
}

CourseDownload::~CourseDownload()
{
    delete ui;
}
