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
    ui->KostilRadioButton->hide();
    radiobuttons->addButton(ui->OneAnswer1Button);
    radiobuttons->addButton(ui->OneAnswer2Button);
    radiobuttons->addButton(ui->OneAnswer3Button);
    radiobuttons->addButton(ui->OneAnswer4Button);
    radiobuttons->addButton(ui->KostilRadioButton);
    if(questions.empty()){
        ui->CurrentQuestionSpinBox->setEnabled(false);
        OneAnswerToggle(false);
        ManyAnswersToggle(false);
        PossibleAnswersToggle(false);
        ui->DetailedAnswerLineEdit->setEnabled(false);
        IsAdding = true;
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
    if (!status){
        ui->KostilRadioButton->setChecked(true);
    }

}

void TestEditor::ManyAnswersToggle(bool status)
{
    ui->ManyAnswers1Button->setEnabled(status);
    ui->ManyAnswers2Button->setEnabled(status);
    ui->ManyAnswers3Button->setEnabled(status);
    ui->ManyAnswers4Button->setEnabled(status);
    if (!status){
        ui->ManyAnswers1Button->setChecked(status);
        ui->ManyAnswers2Button->setChecked(status);
        ui->ManyAnswers3Button->setChecked(status);
        ui->ManyAnswers4Button->setChecked(status);
    }
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


void TestEditor::on_OneAnswerButton_toggled(bool checked)
{
    OneAnswerToggle(checked);
    PossibleAnswersToggle(checked);
    if(checked)
        typeq = 1;
}


void TestEditor::on_ManyAnswersButton_toggled(bool checked)
{
    ManyAnswersToggle(checked);
    PossibleAnswersToggle(checked);
    if(checked)
        typeq = 2;
}


void TestEditor::on_DetailedAnswerButton_toggled(bool checked)
{
    ui->DetailedAnswerLineEdit->setEnabled(checked);
    if(checked)
        typeq = 3;
}


void TestEditor::on_ApplyChangesButton_clicked()
{
    switch (typeq){                                                                                         /*void setQuestion(const QString &newQuestion);

                                                                                                                void setAnswers(const QList<QString> &newAnswers);

                                                                                                                void setType(int32_t newType);*/
                                                                                                               //void setStudentAnswer(const QList<int32_t> &newStudentAnswer);
    case 1:
        if (IsAdding){
            questions.insert(ui->CurrentQuestionSpinBox->value()-1, new Question(ui->WordingQuestionTextEdit->toPlainText(), new QList<QString));
        }
        questions[ui->CurrentQuestionSpinBox->value()-1]->setQuestion(ui->WordingQuestionTextEdit->toPlainText());
        break;
    }
}

