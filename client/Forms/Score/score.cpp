#include "score.h"
#include "ui_score.h"
#include "StyleManager/stylemanager.h"
#include <QScreen>

Score::Score(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Score)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 90);
}

Score::~Score()
{
    delete ui;
}
