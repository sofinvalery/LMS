#include "download.h"
#include "ui_download.h"
#include "StyleManager/stylemanager.h"
#include <QScreen>

Download::Download(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Download)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 90);
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    QMovie *movie = new QMovie(":/gif/resources/download.gif");
    ui->processLabel->setMovie(movie);
    movie->start();

    ui->processLabel->move(screenGeometry.width() / 2 - 105, screenGeometry.height() / 2 - 262);
    ui->infoLabel->move(screenGeometry.width() / 2 - 53, screenGeometry.height() / 2);

    ui->infoLabel->setText("Загрузка...");
    ui->infoLabel->setFont(StyleManager::GetInstance()->getBold());
}

Download::~Download()
{
    delete ui;
}
