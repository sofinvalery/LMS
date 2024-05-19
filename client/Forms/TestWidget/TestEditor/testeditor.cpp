#include "testeditor.h"
#include "ui_testeditor.h"
#include <QButtonGroup>

TestEditor::TestEditor(CourseTest * test, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestEditor)
{
    ui->setupUi(this);
    this->test = test;
    QButtonGroup* radiobuttons = new QButtonGroup;
    ui->KostilRadioButton->hide();
    radiobuttons->addButton(ui->OneAnswer1Button);
    radiobuttons->addButton(ui->OneAnswer2Button);
    radiobuttons->addButton(ui->OneAnswer3Button);
    radiobuttons->addButton(ui->OneAnswer4Button);
    radiobuttons->addButton(ui->KostilRadioButton);
    ui->KostilRadioButton2->hide();
    if(test->getListQuestions().empty()){
        CleanAll();
        typeq = 0;
        QString tempq = "";
        QList<QString> tempa = {};
        QList<int32_t> temps = {};
        test->getListQuestions().append(new Question(tempq, tempa, typeq, temps));

    }
    else{
        ui->CurrentQuestionSpinBox->setMaximum(test->getListQuestions().size());
        on_CurrentQuestionSpinBox_valueChanged(1);
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

QList<int32_t> TestEditor::WhatRadioButtonIsChecked()
{
    QList<int32_t> Buttons;
    if (ui->OneAnswer1Button)
        Buttons.append(1);
    if (ui->OneAnswer2Button)
        Buttons.append(2);
    if (ui->OneAnswer3Button)
        Buttons.append(3);
    if (ui->OneAnswer4Button)
        Buttons.append(4);
    return Buttons;
}

QList<int32_t> TestEditor::WhatCheckBoxIsChecked()
{
    QList<int32_t> Buttons;
    if (ui->ManyAnswers1Button->isChecked())
        Buttons.append(1);
    else
        Buttons.append(0);
    if (ui->ManyAnswers2Button->isChecked())
        Buttons.append(1);
    else
        Buttons.append(0);
    if (ui->ManyAnswers3Button->isChecked())
        Buttons.append(1);
    else
        Buttons.append(0);
    if (ui->ManyAnswers4Button->isChecked())
        Buttons.append(1);
    else
        Buttons.append(0);
    return Buttons;
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

    switch (typeq){
    case 1:{
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setType(1);
        QString tempst = ui->WordingQuestionTextEdit->toPlainText();
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setQuestion(tempst);
        QList<QString> temp1;
        temp1.append(ui->FirstAnswerLineEdit->text());
        temp1.append(ui->SecondAnswerLineEdit->text());
        temp1.append(ui->ThirdAnswerLineEdit->text());
        temp1.append(ui->FourthAnswerLineEdit->text());
        QList<int32_t> tempnum = WhatRadioButtonIsChecked();
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setAnswers(temp1);
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setStudentAnswer(tempnum);
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setType(typeq);

    }
        break;
    case 2:{
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setType(2);
        QString tempst = ui->WordingQuestionTextEdit->toPlainText();
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setQuestion(tempst);
        QList<QString> temp1;
        temp1.append(ui->FirstAnswerLineEdit->text());
        temp1.append(ui->SecondAnswerLineEdit->text());
        temp1.append(ui->ThirdAnswerLineEdit->text());
        temp1.append(ui->FourthAnswerLineEdit->text());
        QList<int32_t> tempnum = WhatCheckBoxIsChecked();
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setAnswers(temp1);
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setStudentAnswer(tempnum);
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setType(typeq);

    }
        break;
    case 3:{
        QString tempst = ui->WordingQuestionTextEdit->toPlainText();
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setQuestion(tempst);
        QList<QString> temp1;
        temp1.append(ui->DetailedAnswerLineEdit->text());
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setAnswers(temp1);
        test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1]->setType(typeq);
    }
    break;
    }
}


void TestEditor::on_CurrentQuestionSpinBox_valueChanged(int arg1)
{

    Question * tempquestion = test->getListQuestions()[ui->CurrentQuestionSpinBox->value()-1];
    CleanAll();
    switch (tempquestion->getType()){
    case 1:{
        ui->OneAnswerButton->setChecked(true);
        ManyAnswersToggle(false);
        ui->DetailedAnswerLineEdit->setEnabled(false);
        OneAnswerToggle(true);
        PossibleAnswersToggle(true);
        ui->FirstAnswerLineEdit->setText(tempquestion->getAnswers()[0]);
        ui->SecondAnswerLineEdit->setText(tempquestion->getAnswers()[1]);
        ui->ThirdAnswerLineEdit->setText(tempquestion->getAnswers()[2]);
        ui->FourthAnswerLineEdit->setText(tempquestion->getAnswers()[3]);
        ui->WordingQuestionTextEdit->setText(tempquestion->getQuestion());
        switch(tempquestion->getStudentAnswer()[0]){
        case 1: ui->OneAnswer1Button->setChecked(true); break;
        case 2: ui->OneAnswer2Button->setChecked(true); break;
        case 3: ui->OneAnswer3Button->setChecked(true); break;
        case 4: ui->OneAnswer4Button->setChecked(true); break;
        };
    }
    break;
    case 2:{
        ui->ManyAnswersButton->setChecked(true);
        OneAnswerToggle(false);
        ui->DetailedAnswerLineEdit->setEnabled(false);
        ManyAnswersToggle(true);
        PossibleAnswersToggle(true);
        ui->FirstAnswerLineEdit->setText(tempquestion->getAnswers()[0]);
        ui->SecondAnswerLineEdit->setText(tempquestion->getAnswers()[1]);
        ui->ThirdAnswerLineEdit->setText(tempquestion->getAnswers()[2]);
        ui->FourthAnswerLineEdit->setText(tempquestion->getAnswers()[3]);
        ui->WordingQuestionTextEdit->setText(tempquestion->getQuestion());
        if (tempquestion->getStudentAnswer()[0] == 1) ui->ManyAnswers1Button->setChecked(true);
        if (tempquestion->getStudentAnswer()[1] == 1) ui->ManyAnswers2Button->setChecked(true);
        if (tempquestion->getStudentAnswer()[2] == 1) ui->ManyAnswers3Button->setChecked(true);
        if (tempquestion->getStudentAnswer()[3] == 1) ui->ManyAnswers4Button->setChecked(true);
    }
    break;
    case 3:{
        ui->DetailedAnswerButton->setChecked(true);
        OneAnswerToggle(false);
        ManyAnswersToggle(false);
        ui->DetailedAnswerLineEdit->setEnabled(true);
        ui->DetailedAnswerLineEdit->setText(tempquestion->getAnswers()[0]);
        ui->WordingQuestionTextEdit->setText(tempquestion->getQuestion());

    }
    break;
    case 4:{
        CleanAll();
    }
    break;
    }
}


void TestEditor::on_AddNewQuestionButton_clicked()
{
    typeq = 0;
    QString tempq = "";
    QList<QString> tempa = {};
    QList<int32_t> temps = {};

    test->getListQuestions().insert(ui->CurrentQuestionSpinBox->value(), new Question(tempq, tempa, typeq, temps));
    ui->CurrentQuestionSpinBox->setEnabled(true);
    ui->CurrentQuestionSpinBox->setMaximum(test->getListQuestions().size());
    ui->CurrentQuestionSpinBox->setValue(ui->CurrentQuestionSpinBox->value()+1);

    CleanAll();

}

void TestEditor::CleanAll()
{
    ui->FirstAnswerLineEdit->clear();
    ui->SecondAnswerLineEdit->clear();
    ui->ThirdAnswerLineEdit->clear();
    ui->FourthAnswerLineEdit->clear();
    ui->DetailedAnswerLineEdit->clear();
    ui->WordingQuestionTextEdit->clear();
    ui->DetailedAnswerLineEdit->setEnabled(false);
    OneAnswerToggle(false);
    ManyAnswersToggle(false);
    ui->KostilRadioButton2->setChecked(true);
}


void TestEditor::on_pushButton_clicked()
{
    if(test->getListQuestions().size() > 1){
        test->getListQuestions().removeAt(ui->CurrentQuestionSpinBox->value() - 1);
        CleanAll();
        ui->CurrentQuestionSpinBox->setMaximum(ui->CurrentQuestionSpinBox->maximum() - 1);
        ui->CurrentQuestionSpinBox->setValue(ui->CurrentQuestionSpinBox->value() - 1);
        on_CurrentQuestionSpinBox_valueChanged(ui->CurrentQuestionSpinBox->value());
    }
    if(test->getListQuestions().size() == 1){
        test->getListQuestions().removeAt(0);
        typeq = 0;
        QString tempq = "";
        QList<QString> tempa = {};
        QList<int32_t> temps = {};
        test->getListQuestions().append(new Question(tempq, tempa, typeq, temps));
        CleanAll();
    }
}

