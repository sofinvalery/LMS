#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPixmap>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //QWidget::setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    //QPixmap pixmap("kapipng.png");
    //QIcon ButtonIcon(pixmap);

    ui->CourseButtonIMG->setIcon(QIcon(":/img/resources/kap.jpg"));
    //ui->CourseButtonIMG->setIconSize(pixmap.rect().size());
}

MyWidget::~MyWidget()
{
    delete ui;
}
