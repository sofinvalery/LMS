#include "loadercomponent.h"
#include "ui_loadercomponent.h"
#include "StyleManager/stylemanager.h"

LoaderComponent::LoaderComponent(QWidget *parent, QString fileName, qint64 totalSize)
    : QWidget(parent)
    , ui(new Ui::LoaderComponent)
{
    ui->setupUi(this);

    StyleManager::GetInstance()->setLabelStyle(ui->downloadName, fileName, false, "black", true, 16);
    ui->downloadName->setFixedSize(ui->downloadName->sizeHint().width(), ui->downloadName->sizeHint().height());

    StyleManager::GetInstance()->setProgressBarStyle(ui->progressBar, false, 10, "lightgrey", "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(78, 181, 255, 255), stop:1 rgba(108, 73, 217, 255));");
    ui->progressBar->setValue(currentDownload);
    ui->progressBar->setRange(0, totalSize);
    ui->line->setStyleSheet("border: 2px solid lightgrey");
}

LoaderComponent::~LoaderComponent()
{
    delete ui;
}

void LoaderComponent::increaseDownload(qint64 newValue)
{
    currentDownload += newValue;

    ui->progressBar->setValue(currentDownload);
}
