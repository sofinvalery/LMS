#include "download.h"
#include "ui_download.h"
#include "StyleManager/stylemanager.h"
#include <QScreen>

Download::Download(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Download)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-top: 3px solid lightgrey;"
        "}");

    QScreen* scr = QGuiApplication::primaryScreen();
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height() - 20);
    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height() - 20);
    this->move(0, 90);

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
