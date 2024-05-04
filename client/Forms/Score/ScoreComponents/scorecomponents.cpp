#include "scorecomponents.h"
#include "ui_scorecomponents.h"
#include "StyleManager/stylemanager.h"

ScoreComponents::ScoreComponents(QString courseName, int currentScore, int maxScore, QWidget *parent, Course* course)
    : QWidget(parent)
    , ui(new Ui::ScoreComponents)
{
    ui->setupUi(this);

    this->course = course;

    StyleManager::GetInstance()->setLabelStyle(ui->courseNameLabel, courseName, true, "black", true, 20, true, "rgba(0, 0, 0, 0)");
    ui->courseNameLabel->setFixedSize(ui->courseNameLabel->sizeHint().width(), ui->courseNameLabel->sizeHint().height());
    ui->courseNameLabel->raise();

    StyleManager::GetInstance()->setLabelStyle(ui->currentScoreLabel, QString::number(currentScore), false, "black", true, 18, true, "rgba(0, 0, 0, 0)");
    ui->currentScoreLabel->setFixedSize(ui->currentScoreLabel->sizeHint().width(), ui->currentScoreLabel->sizeHint().height());
    ui->currentScoreLabel->move(300, 30);
    ui->currentScoreLabel->raise();

    StyleManager::GetInstance()->setLabelStyle(ui->maxScoreLabel, QString::number(maxScore), false, "black", true, 18, true, "rgba(0, 0, 0, 0)");
    ui->maxScoreLabel->setFixedSize(ui->maxScoreLabel->sizeHint().width(), ui->maxScoreLabel->sizeHint().height());
    ui->maxScoreLabel->move(450, 30);
    ui->maxScoreLabel->raise();

    StyleManager::GetInstance()->setSimpleButtonStyle(ui->pushButton, "", false, 1, 1);
    ui->pushButton->raise();
    ui->pushButton->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    StyleManager::GetInstance()->setProgressBarStyle(ui->progressBar, false, 5, "white", "#7ECFFF");
    ui->progressBar->setRange(0, maxScore);
    ui->progressBar->setValue(currentScore);

    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-radius: 5px;"
        "border: 2px solid lightgrey;"
        "}");
}

ScoreComponents::~ScoreComponents()
{
    delete ui;
}

void ScoreComponents::on_pushButton_clicked()
{
    // StyleManager::GetInstance()->setLabelStyle(ui->courseNameLabel, ui->courseNameLabel->text(), true, "black", true, 19);
    // StyleManager::GetInstance()->setLabelStyle(ui->currentScoreLabel, ui->currentScoreLabel->text(), false, "black", true, 17);
    // StyleManager::GetInstance()->setLabelStyle(ui->maxScoreLabel, ui->maxScoreLabel->text(), false, "black", true, 17);
    emit showPathCourseScore(course);
}

