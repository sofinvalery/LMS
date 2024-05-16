#include "testeditor.h"
#include "ui_testeditor.h"
#include <QButtonGroup>

TestEditor::TestEditor(QList<Question*> questions, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestEditor)
{
    ui->setupUi(this);
    this->questions = questions;
    QButtonGroup* radiobuttons = new QButtonGroup;
    radiobuttons->addButton(ui->OneAnswer1Button);
    radiobuttons->addButton(ui->OneAnswer2Button);
    radiobuttons->addButton(ui->OneAnswer3Button);
    radiobuttons->addButton(ui->OneAnswer4Button);
    if(questions.empty()){
        ui->CurrentQuestionSpinBox->setEnabled(false);
        OneAnswerToggle(false);
        ManyAnswersToggle(false);
        PossibleAnswersToggle(false);
        ui->DetailedAnswerLineEdit->setEnabled(false);
    }

}

TestEditor::~TestEditor()
{
    delete ui;
}

void TestEditor::OneAnswerToggle(bool status)
{
    ui->OneAnswer1Button->setEnabled(status);
    ui->OneAnswer2Button->setEnabled(status);
    ui->OneAnswer3Button->setEnabled(status);
    ui->OneAnswer4Button->setEnabled(status);
}

void TestEditor::ManyAnswersToggle(bool status)
{
    ui->ManyAnswers1Button->setEnabled(status);
    ui->ManyAnswers2Button->setEnabled(status);
    ui->ManyAnswers3Button->setEnabled(status);
    ui->ManyAnswers4Button->setEnabled(status);
}

void TestEditor::PossibleAnswersToggle(bool status)
{
    ui->FirstAnswerLineEdit->setEnabled(status);
    ui->SecondAnswerLineEdit->setEnabled(status);
    ui->ThirdAnswerLineEdit->setEnabled(status);
    ui->FourthAnswerLineEdit->setEnabled(status);
}


void TestEditor::on_exitButton_clicked()
{
    this->close();
    this->deleteLater();
}

