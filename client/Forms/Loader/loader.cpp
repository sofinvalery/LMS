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
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->move(StyleManager::GetInstance()->getScreenWidth() - this->width() - 104, 55);
    this->setStyleSheet("background-color: white;");
    StyleManager::GetInstance()->setLabelStyle(ui->loaderLabel, "Загрузки", true, "white", true, 20, true);
    ui->loaderLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->loaderLabel->setFixedSize(this->width(), 59);
    ui->loaderLabel->move(this->size().width() / 2 - ui->loaderLabel->size().width() / 2, 0);

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
