#include "testwidget.h"
#include "ui_testwidget.h"
#include "Forms/Main/mainwindow.h"

TestWidget::TestWidget(CourseTest * test, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidget)
{
    ui->setupUi(this);
    this->test = test;
    ui->groupBox->setStyleSheet("background-color: white;");
    this->move(0, 75+140);

    this->resize( StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());

    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height());
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

