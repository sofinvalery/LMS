 #include "coursedownload.h"
#include "ui_coursedownload.h"
#include "StyleManager/stylemanager.h"

CourseDownload::CourseDownload(CourseComponent * pdf, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDownload)
{
    ui->setupUi(this);
    this->pdf =  qobject_cast<CourseMediaFiles*>(pdf);
    icon = new QPixmap(":/img/resources/dowloadicon.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
    StyleManager::GetInstance()->setLinkButtonStyle(ui->DownloadButton, "Лекция 1.111111111111111.pdf", true, 16, 15);
}

CourseDownload::~CourseDownload()
{
    delete ui;
}
