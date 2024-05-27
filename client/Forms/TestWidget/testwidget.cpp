#include "testwidget.h"
#include "ui_testwidget.h"
#include "Forms/Main/mainwindow.h"
#include "TestPassing/testpassing.h"
#include "ClientState/clientstate.h"

TestWidget::TestWidget(CourseTest * test, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidget)
{
    ui->setupUi(this);
    this->test = test;
    ui->groupBox->setStyleSheet("background-color: white;");

    this->resize( StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());

    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height());

    ui->TitleLabel->setText(test->getTitle());

    ui->MaxMarkLabel->setText("Максимальное количество баллов: " + QString::number(test->getMaxMark()));
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::on_BackButton_clicked()
{
    this->close();
    this->deleteLater();
}


void TestWidget::on_EditTestButton_clicked()
{
    TestEditor * editor = new TestEditor(test, this);
    editor->move(StyleManager::GetInstance()->getScreenWidth() / 2 - 290, StyleManager::GetInstance()->getScreenHeight() / 2 - 250);
    editor->show();

}


void TestWidget::on_StartTestButton_clicked()
{
    if(test->getListQuestions().size()>=test->getTestSize())
    {
        TestPassing * testpassing = new TestPassing(this);
        testpassing->showFullScreen();
    }
    else{
        ClientState::GetInstance()->ShowNotifacate("В тесте не достаточно вопросов","red");
    }
}

CourseTest * TestWidget::getTest()
{
    return test;
}

void TestWidget::setVerdict(QString verdict)
{
    ui->NotesLabel->setText(verdict);
}

