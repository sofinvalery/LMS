#include "testtaskcomponents.h"
#include "ui_testtaskcomponents.h"
#include "StyleManager/stylemanager.h"

testTaskComponents::testTaskComponents(QString courseName, int currentScore, int maxScore, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::testTaskComponents)
{
    ui->setupUi(this);

    StyleManager::GetInstance()->setLabelStyle(ui->courseNameLabel, courseName, true, "black", true, 18);
    ui->courseNameLabel->setFixedSize(ui->courseNameLabel->sizeHint().width(), ui->courseNameLabel->sizeHint().height());

    StyleManager::GetInstance()->setLabelStyle(ui->currentScoreLabel, QString::number(currentScore), false, "black", true, 16, true, "rgba(0, 0, 0, 0)");
    ui->currentScoreLabel->setFixedSize(ui->currentScoreLabel->sizeHint().width(), ui->currentScoreLabel->sizeHint().height());
    ui->currentScoreLabel->move(210, 15);

    StyleManager::GetInstance()->setLabelStyle(ui->maxScoreLabel, QString::number(maxScore), false, "black", true, 16, true, "rgba(0, 0, 0, 0)");
    ui->maxScoreLabel->setFixedSize(ui->maxScoreLabel->sizeHint().width(), ui->maxScoreLabel->sizeHint().height());
    ui->maxScoreLabel->move(300, 15);

    StyleManager::GetInstance()->setProgressBarStyle(ui->progressBar, false);
    ui->progressBar->lower();
    ui->progressBar->setRange(0, maxScore);
    ui->progressBar->setValue(currentScore);
    ui->progressBar->setFixedSize(132, 30);
    ui->progressBar->move(200, 10);

}

testTaskComponents::~testTaskComponents()
{
    delete ui;
}
