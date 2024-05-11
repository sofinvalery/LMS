#include "download.h"
#include "ui_download.h"
#include "StyleManager/stylemanager.h"

Download::Download(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Download)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetGroupBoxStyle(this, ui->groupBox, 90);

    QMovie *movie = new QMovie(":/gif/resources/download.gif");
    ui->processLabel->setMovie(movie);
    movie->start();

    ui->processLabel->move(StyleManager::GetInstance()->getScreenWidth() / 2 - 105, StyleManager::GetInstance()->getScreenHeight() / 2 - 262);
    ui->infoLabel->move(StyleManager::GetInstance()->getScreenWidth() / 2 - 53, StyleManager::GetInstance()->getScreenHeight() / 2);

    ui->infoLabel->setText("Загрузка...");
    ui->infoLabel->setFont(StyleManager::GetInstance()->getBold());
}

Download::~Download()
{
    delete ui;
}
