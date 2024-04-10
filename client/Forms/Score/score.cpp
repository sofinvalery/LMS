#include "score.h"
#include "ui_score.h"
#include <QScreen>

Score::Score(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Score)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-top: 3px solid lightgrey;"
        "}");

    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize(scr->availableGeometry().width(), scr->availableGeometry().height() - 20);
    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height() - 20);
    this->move(0, 90);
}

Score::~Score()
{
    delete ui;
}
