#include "loadercomponent.h"
#include "ui_loadercomponent.h"
#include "StyleManager/stylemanager.h"

LoaderComponent::LoaderComponent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoaderComponent)
{
    ui->setupUi(this);

    StyleManager::GetInstance()->setLabelStyle(ui->downloadName, "Name", false, "black", true, 16);
    ui->downloadName->setFixedSize(ui->downloadName->sizeHint().width(), ui->downloadName->sizeHint().height());

    StyleManager::GetInstance()->setProgressBarStyle(ui->progressBar, false);

    ui->line->setStyleSheet("border: 2px solid lightgrey");
}

LoaderComponent::~LoaderComponent()
{
    delete ui;
}
