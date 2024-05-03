#include "loader.h"
#include "ui_loader.h"
#include "StyleManager/stylemanager.h"
#include "LoaderComponent/loadercomponent.h"

Loader::Loader(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Loader)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::FramelessWindowHint);
    StyleManager::GetInstance()->setLabelStyle(ui->loaderLabel, "Загрузки", true, "black", true, 20);
    ui->loaderLabel->setFixedSize(ui->loaderLabel->sizeHint().width(), ui->loaderLabel->sizeHint().height());
    ui->loaderLabel->move(this->size().width() / 2 - ui->loaderLabel->size().width() / 2, ui->loaderLabel->size().height() - 5);

    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);

    for (int i = 0; i < 6; i++)
    {
        LoaderComponent* loaderComponent = new LoaderComponent(ui->scrollAreaWidgetContents);
        loaderComponent->move(0, heightLine);
        heightLine += 100;
        ui->scrollAreaWidgetContents->setMinimumHeight(heightLine);
    }
}
Loader::~Loader()
{
    delete ui;
}
