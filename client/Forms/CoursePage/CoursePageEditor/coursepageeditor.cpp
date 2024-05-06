#include "coursepageeditor.h"
#include "ui_coursepageeditor.h"
#include "StyleManager/stylemanager.h"
#include <QFileDialog>

CoursePageEditor::CoursePageEditor(CoursePage * coursepage, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoursePageEditor)
{
    ui->setupUi(this);
    this->coursepage = coursepage;
    //StyleManager::GetInstance()->setLineEditStyle(ui->ComponentOrderLineEdit, "Порядок компонента", false, 16, 300, 30);
    StyleManager::GetInstance()->setLabelStyle(ui->ComponentOrderLabel, "Номер компонента по порядку:", false, "black", true, 16);
    StyleManager::GetInstance()->setLabelStyle(ui->MaxMarkLabel, "Максимум баллов за задание:", false, "black", true, 16);
    StyleManager::GetInstance()->setLabelStyle(ui->TaskContentLabel, "Описание задания:", false, "black", true, 16);
    ui->ComponentOrderLabel->setFixedSize(ui->ComponentOrderLabel->sizeHint().width(), ui->ComponentOrderLabel->sizeHint().height());
    ui->ComponentOrderLabel->setFixedSize(ui->MaxMarkLabel->sizeHint().width(), ui->MaxMarkLabel->sizeHint().height());
    ui->ComponentOrderLabel->setFixedSize(ui->MaxMarkLabel->sizeHint().width(), ui->TaskContentLabel->sizeHint().height());
    StyleManager::GetInstance()->setLineEditStyle(ui->NameOnComponentLineEdit, "Название компонента", false, 16, 300, 30);
    StyleManager::GetInstance()->setLineEditStyle(ui->AllowedTypeOfFilesLineEdit, "Разрешенные типы файлов", false, 16, 300, 30);
    ui->ContentTextEdit->hide();
    ui->NameOnComponentLineEdit->hide();
    ui->ComponentOrderSpinBox->hide();
    ui->ComponentOrderLabel->hide();
    ui->AddDzButton->hide();
    ui->AddFileButton->hide();
    ui->AddTestButton->hide();
    ui->AddTextButton->hide();
    ui->LoadFileButton->hide();
    ui->PathLabel1->hide();
    ui->PathLabel2->hide();
    ui->AllowedTypeOfFilesLineEdit->hide();
    ui->MaxMarkLabel->hide();
    ui->MaxMarkSpinBox->hide();
    ui->TaskContentLabel->hide();
}

CoursePageEditor::~CoursePageEditor()
{
    delete ui;
}

void CoursePageEditor::on_LoadFileButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор картинки", QDir::homePath(), "All Files (*.*);");
    ui->PathLabel2->setText(path);
}


void CoursePageEditor::on_AddWidgetButton_clicked()
{
    if(ui->DeleteWidgetButton->isEnabled()){
        ui->ComponentOrderSpinBox->setMaximum(coursepage->GetCourse()->getListComponents().size() + 1);
        ui->ComponentOrderSpinBox->setValue(1);
        ui->DeleteWidgetButton->setEnabled(false);
        ui->EditWidgetButton->setEnabled(false);
        ui->AddDzButton->show();
        ui->AddFileButton->show();
        ui->AddTestButton->show();
        ui->AddTextButton->show();
        ui->AddDzButton->setEnabled(true);
        ui->AddTestButton->setEnabled(true);
        ui->AddTextButton->setEnabled(true);
        ui->AddFileButton->setEnabled(true);
    }
    else{
        ui->DeleteWidgetButton->setEnabled(true);
        ui->EditWidgetButton->setEnabled(true);
        ui->AddDzButton->hide();
        ui->AddFileButton->hide();
        ui->AddTestButton->hide();
        ui->AddTextButton->hide();

        AddingStatus = 0;
        ui->ContentTextEdit->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->ComponentOrderLabel->hide();
        ui->LoadFileButton->hide();
        ui->PathLabel1->hide();
        ui->PathLabel2->hide();
    }
}


void CoursePageEditor::on_EditWidgetButton_clicked()
{
    if(ui->AddWidgetButton->isEnabled()){
        ui->ComponentOrderSpinBox->setMaximum(coursepage->GetCourse()->getListComponents().size());
        ui->ComponentOrderSpinBox->setValue(1);
        ui->AddWidgetButton->setEnabled(false);
        ui->DeleteWidgetButton->setEnabled(false);
        ui->ComponentOrderSpinBox->show();
        ui->ComponentOrderLabel->show();
        //ui->NameOnComponent->show();
    }
    else{
        ui->AddWidgetButton->setEnabled(true);
        ui->DeleteWidgetButton->setEnabled(true);
        ui->ComponentOrderSpinBox->hide();
        ui->ComponentOrderLabel->hide();
        //ui->NameOnComponent->hide();
    }
}


void CoursePageEditor::on_DeleteWidgetButton_clicked()
{
    if(ui->AddWidgetButton->isEnabled()){
        ui->ComponentOrderSpinBox->setMaximum(coursepage->GetCourse()->getListComponents().size());
        ui->ComponentOrderSpinBox->setValue(1);
        DeletingStatus = 1;
        ui->AddWidgetButton->setEnabled(false);
        ui->EditWidgetButton->setEnabled(false);
        ui->ComponentOrderSpinBox->show();
        ui->ComponentOrderLabel->show();
    }
    else{
        DeletingStatus = 0;
        ui->AddWidgetButton->setEnabled(true);
        ui->EditWidgetButton->setEnabled(true);
        ui->ComponentOrderSpinBox->hide();
        ui->ComponentOrderLabel->hide();
    }
}


void CoursePageEditor::on_DoneButton_clicked()
{
    if(AddingStatus == 1){                                  // добавить на сервер тест (не доделано)
        coursepage->CleanComponents();
        coursepage->GetCourse()->AddCourseComponent(new CourseTest(-100, ui->ComponentOrderSpinBox->value(), ui->NameOnComponentLineEdit->text(), 10, "", 1000, 9, "сдал", QDate(2004,4,4)), ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
    }
    if(AddingStatus == 2){                                  // добавить на сервер загрузочный файл
        coursepage->CleanComponents();
        coursepage->GetCourse()->AddCourseComponent(new CoursePdf(-100, ui->ComponentOrderSpinBox->value(), ui->NameOnComponentLineEdit->text(),  ui->PathLabel2->text()), ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
    }
    if (AddingStatus == 3){                                  // добавить на сервер дз (не доделано)
        coursepage->CleanComponents();
        coursepage->GetCourse()->AddCourseComponent(new CourseTask(-100, ui->ComponentOrderSpinBox->value(), ui->ContentTextEdit->toPlainText(), ui->MaxMarkSpinBox->value(), 7000, ui->AllowedTypeOfFilesLineEdit->text(), "", QDate(2004,4,4), 0, "", ui->NameOnComponentLineEdit->text()), ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
    }
    if(AddingStatus == 4){                                  // добавить на сервер туториал
        coursepage->CleanComponents();
        coursepage->GetCourse()->AddCourseComponent(new CourseTutorials(-100, ui->ComponentOrderSpinBox->value(), ui->ContentTextEdit->toPlainText()), ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
    }
    if (DeletingStatus == 1){                               // удалить из сервера элемент  ui->ComponentOrderSpinBox->value()-1
        coursepage->CleanComponents();
        coursepage->GetCourse()->DeleteCourseComponent(ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
    }
    this->close();
}


void CoursePageEditor::on_AddFileButton_clicked()
{
    if(ui->LoadFileButton->isHidden()){
        AddingStatus = 2;
        ui->LoadFileButton->show();
        ui->PathLabel1->show();
        ui->PathLabel2->show();
        ui->ComponentOrderLabel->show();
        ui->ComponentOrderSpinBox->show();
        ui->NameOnComponentLineEdit->show();
        ui->AddDzButton->setEnabled(false);
        ui->AddTestButton->setEnabled(false);
        ui->AddTextButton->setEnabled(false);
    }
    else{
        AddingStatus = 0;
        ui->LoadFileButton->hide();
        ui->PathLabel1->hide();
        ui->PathLabel2->hide();
        ui->ComponentOrderLabel->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->AddDzButton->setEnabled(true);
        ui->AddTestButton->setEnabled(true);
        ui->AddTextButton->setEnabled(true);
    }
}


void CoursePageEditor::on_AddTextButton_clicked()
{
    if (ui->ContentTextEdit->isHidden()){
        AddingStatus = 4;
        ui->ContentTextEdit->show();
        ui->ComponentOrderLabel->show();
        ui->ComponentOrderSpinBox->show();
        ui->AddDzButton->setEnabled(false);
        ui->AddTestButton->setEnabled(false);
        ui->AddFileButton->setEnabled(false);
    }
    else{
        AddingStatus = 0;
        ui->ContentTextEdit->clear();
        ui->ContentTextEdit->hide();
        ui->ComponentOrderLabel->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->AddDzButton->setEnabled(true);
        ui->AddTestButton->setEnabled(true);
        ui->AddFileButton->setEnabled(true);
    }
}


void CoursePageEditor::on_AddTestButton_clicked()
{
    if (ui->ComponentOrderLabel->isHidden()){
        AddingStatus = 1;
        ui->ComponentOrderLabel->show();
        ui->ComponentOrderSpinBox->show();
        ui->NameOnComponentLineEdit->show();
        ui->AddTextButton->setEnabled(false);
        ui->AddDzButton->setEnabled(false);
        ui->AddFileButton->setEnabled(false);
    }
    else
    {
        AddingStatus = 0;
        ui->ComponentOrderLabel->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->AddTextButton->setEnabled(true);
        ui->AddDzButton->setEnabled(true);
        ui->AddFileButton->setEnabled(true);
    }
}


void CoursePageEditor::on_AddDzButton_clicked()
{
    if (ui->ComponentOrderLabel->isHidden()){
        AddingStatus = 3;
        ui->ComponentOrderLabel->show();
        ui->ComponentOrderSpinBox->show();
        ui->NameOnComponentLineEdit->show();
        ui->ContentTextEdit->show();
        ui->AllowedTypeOfFilesLineEdit->show();
        ui->MaxMarkLabel->show();
        ui->MaxMarkSpinBox->show();
        ui->TaskContentLabel->show();
        ui->AddTextButton->setEnabled(false);
        ui->AddTestButton->setEnabled(false);
        ui->AddFileButton->setEnabled(false);
    }
    else
    {
        AddingStatus = 0;
        ui->ContentTextEdit->clear();
        ui->ComponentOrderLabel->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->ContentTextEdit->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->AllowedTypeOfFilesLineEdit->hide();
        ui->MaxMarkLabel->hide();
        ui->MaxMarkSpinBox->hide();
        ui->TaskContentLabel->hide();
        ui->AddTextButton->setEnabled(true);
        ui->AddTestButton->setEnabled(true);
        ui->AddFileButton->setEnabled(true);
    }
}

