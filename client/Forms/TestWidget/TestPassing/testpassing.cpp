#include "testpassing.h"
#include "ui_testpassing.h"




TestPassing::TestPassing(TestWidget * testwidget, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestPassing)
{
    ui->setupUi(this);
    ui->KostilRadioButton->hide();
    this->testWidget = testwidget;
    questionList = testWidget->getTest()->getListQuestions();
    for (int i = 0; i < questionList.size(); i++){
        answers.append(new QuestionAnswers);
        answers[i]->type = questionList[i]->getType();
        if (questionList[i]->getType() == 1 || questionList[i]->getType() == 2){
            for (int j = 0; j < 4; answers[i]->Answers.append(0), j++);
        }
    }
    ui->CurrentQuestionSpinBox->setMaximum(questionList.size());
    on_CurrentQuestionSpinBox_valueChanged(1);

    timeLeft = QTime(testWidget->getTest()->getTimeInSeconds()/3600, testWidget->getTest()->getTimeInSeconds()%3600/60, testWidget->getTest()->getTimeInSeconds()%60);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &TestPassing::updateTimer);
    timer->start(1000);

}

TestPassing::~TestPassing()
{
    delete ui;
}

void TestPassing::on_CurrentQuestionSpinBox_valueChanged(int arg1)
{
    ui->QuestionLabel->setText(questionList[arg1 - 1]->getQuestion());
    HideRadioButtons(true);
    HideCheckBoxes(true);
    ui->DetailedAnswerLineEdit->clear();
    ui->DetailedAnswerLineEdit->hide();
    if (questionList[arg1 - 1]->getType() == 1 || questionList[arg1 - 1]->getType() == 2){
        ui->Answer1Label->setText(questionList[arg1 - 1]->getAnswers()[0]);
        ui->Answer2Label->setText(questionList[arg1 - 1]->getAnswers()[1]);
        ui->Answer3Label->setText(questionList[arg1 - 1]->getAnswers()[2]);
        ui->Answer4Label->setText(questionList[arg1 - 1]->getAnswers()[3]);
    }



    if (questionList[arg1 - 1]->getType() == 1) HideRadioButtons(false);
    if (questionList[arg1 - 1]->getType() == 2) HideCheckBoxes(false);
    if (questionList[arg1 - 1]->getType() == 3) ui->DetailedAnswerLineEdit->show();
    if(questionList[arg1 - 1]->getType() == 1){
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] == 1)
            ui->Answer1RadioButton->setChecked(true);
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] == 1)
            ui->Answer2RadioButton->setChecked(true);
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] == 1)
            ui->Answer3RadioButton->setChecked(true);
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] == 1)
            ui->Answer4RadioButton->setChecked(true);
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] == 0 && answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] == 0 && answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] == 1 &&
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] == 0)
            ui->KostilRadioButton->setChecked(true);
    }
    if(questionList[arg1 - 1]->getType() == 2){
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] == 1)
            ui->Answer1CheckBox->setChecked(true);
        else
            ui->Answer1CheckBox->setChecked(false);
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] == 1)
            ui->Answer2CheckBox->setChecked(true);
        else
            ui->Answer2CheckBox->setChecked(false);
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] == 1)
            ui->Answer3CheckBox->setChecked(true);
        else
            ui->Answer3CheckBox->setChecked(false);
        if (answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] == 1)
            ui->Answer4CheckBox->setChecked(true);
        else
            ui->Answer4CheckBox->setChecked(false);
    }
    if(questionList[arg1 - 1]->getType() == 3){
        ui->DetailedAnswerLineEdit->setText(answers[ui->CurrentQuestionSpinBox->value()-1]->DetailedAnswer);
    }
}

void TestPassing::HidePossibleAnswers(bool hide)
{
    ui->Answer1Label->setVisible(!hide);
    ui->Answer2Label->setVisible(!hide);
    ui->Answer3Label->setVisible(!hide);
    ui->Answer4Label->setVisible(!hide);
}

void TestPassing::HideRadioButtons(bool hide)
{
    ui->KostilRadioButton->setChecked(true);
    if (hide){
        ui->Answer1RadioButton->hide();
        ui->Answer2RadioButton->hide();
        ui->Answer3RadioButton->hide();
        ui->Answer4RadioButton->hide();
        HidePossibleAnswers(hide);
    }
    else{
        ui->Answer1RadioButton->show();
        ui->Answer2RadioButton->show();
        ui->Answer3RadioButton->show();
        ui->Answer4RadioButton->show();
        HidePossibleAnswers(hide);
    }
}


void TestPassing::CleanCheckBoxes()
{
    ui->Answer1CheckBox->setChecked(false);
    ui->Answer1CheckBox->setChecked(false);
    ui->Answer1CheckBox->setChecked(false);
    ui->Answer1CheckBox->setChecked(false);
}

void TestPassing::HideCheckBoxes(bool hide)
{
    CleanCheckBoxes();
    if (hide){
        ui->Answer1CheckBox->hide();
        ui->Answer2CheckBox->hide();
        ui->Answer3CheckBox->hide();
        ui->Answer4CheckBox->hide();
        HidePossibleAnswers(hide);
    }
    else{
        ui->Answer1CheckBox->show();
        ui->Answer2CheckBox->show();
        ui->Answer3CheckBox->show();
        ui->Answer4CheckBox->show();
        HidePossibleAnswers(hide);
    }
}

void TestPassing::on_Answer1RadioButton_toggled(bool checked)
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 1){
        if (checked){
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] = 1;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] = 0;
        }
        else answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] = 0;
    }
}


void TestPassing::on_Answer2RadioButton_toggled(bool checked)
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 1){
        if (checked){
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] = 1;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] = 0;
        }
        else answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] = 0;
    }
}


void TestPassing::on_Answer3RadioButton_toggled(bool checked)
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 1){
        if (checked){
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] = 1;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] = 0;
        }
        else answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] = 0;
    }
}


void TestPassing::on_Answer4RadioButton_toggled(bool checked)
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 1){
        if (checked){
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] = 0;
            answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] = 1;
        }
        else answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] = 0;
    }
}


void TestPassing::on_Answer1CheckBox_toggled(bool checked)
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 2){
        if (checked) answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] = 1;
        else answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[0] = 0;
    }
}


void TestPassing::on_Answer2CheckBox_toggled(bool checked)
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 2){
        if (checked) answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] = 1;
        else answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[1] = 0;
    }
}


void TestPassing::on_Answer3CheckBox_toggled(bool checked)
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 2){
        if (checked) answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] = 1;
        else answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[2] = 0;
    }
}


void TestPassing::on_Answer4CheckBox_toggled(bool checked)
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 2){
        if (checked) answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] = 1;
        else answers[ui->CurrentQuestionSpinBox->value()-1]->Answers[3] = 0;
    }
}


void TestPassing::on_DetailedAnswerLineEdit_editingFinished()
{
    if (answers[ui->CurrentQuestionSpinBox->value()-1]->type == 3)
    answers[ui->CurrentQuestionSpinBox->value()-1]->DetailedAnswer = ui->DetailedAnswerLineEdit->text();
}

double TestPassing::SummPoints()
{
    double summ = 0;
    for (int i = 0; i < questionList.size(); i++){
        if (questionList[i]->getType() == 1){
            if(answers[i]->Answers == questionList[i]->getStudentAnswer()) summ += 1;
        }
        if (questionList[i]->getType() == 2){
            double ball = 0.0;
            for (int z = 0; z < 4; z ++) ball += questionList[i]->getStudentAnswer()[z];
            ball = 1.0 / ball;
            for(int j = 0; j < 4; j++){
                if (answers[i]->Answers[j] == questionList[i]->getStudentAnswer()[j] && answers[i]->Answers[j] == 1) summ += ball;
            }
        }
        if (questionList[i]->getType() == 3){
            if (answers[i]->DetailedAnswer.toLower() == questionList[i]->getAnswers()[0].toLower()) summ += 1;
        }
    }
    return summ;
}


void TestPassing::on_EndTestButton_clicked() // результат теста - summpoints
{
    testWidget->setVerdict("Количество баллов за тест: " +  QString::number(int32_t(SummPoints()), 'g', 2 ));
    testWidget->getTest()->setVerdict(int32_t(SummPoints()));
    qDebug() << SummPoints();

    this->close();
    this->deleteLater();
}

void TestPassing::updateTimer()
{
    if (timeLeft == QTime(0, 0, 0)) {
        timer->stop();
        on_EndTestButton_clicked();
    } else {
        timeLeft = timeLeft.addSecs(-1);
        ui->TimerLabel->setText(timeLeft.toString("hh:mm:ss"));
    }
}

