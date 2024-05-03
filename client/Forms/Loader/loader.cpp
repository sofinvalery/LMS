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
    this->move(StyleManager::GetInstance()->getScreenWidth() - this->width() - 104, 55);
    StyleManager::GetInstance()->setLabelStyle(ui->loaderLabel, "Загрузки", true, "black", true, 20);
    ui->loaderLabel->setFixedSize(ui->loaderLabel->sizeHint().width(), ui->loaderLabel->sizeHint().height());
    ui->loaderLabel->move(this->size().width() / 2 - ui->loaderLabel->size().width() / 2, ui->loaderLabel->size().height() - 5);

    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);
}
Loader::~Loader()
{
    delete ui;
}

void Loader::createWidget(QString fileName, qint64 totalSize)
{
    LoaderComponent* loaderComponent = new LoaderComponent(ui->scrollAreaWidgetContents, fileName, totalSize);
    widgetHash.insert(fileName, loaderComponent);

    for (QWidget* item : widgetHash)
    {
        QWidget* widget = item;
        widget->move(0, heightLine);
        heightLine += 100;
        widget->show();
        ui->scrollAreaWidgetContents->setMinimumHeight(heightLine);
    }
}

void Loader::deleteWidget(QString fileName)
{
    if (widgetHash.contains(fileName))
    {
        QWidget* widget = widgetHash.value(fileName);
        widget->close();
        delete widget;
        widgetHash.remove(fileName);
    }
}
