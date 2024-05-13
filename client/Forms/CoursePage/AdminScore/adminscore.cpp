#include "adminscore.h"
#include "ui_adminscore.h"
#include "StyleManager/stylemanager.h"
#include "ClientState/clientstate.h"
#include "XlsxUtils/xlsxutils.h"
#include "ClientManager/socketparser.h"

AdminScore::AdminScore(Course* course,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminScore)
{
    ui->setupUi(this);
    this->course=course;
    connect(SocketParser::GetInstance(),SIGNAL(getSubmit(QList<Submit*>,Group*)),this,SLOT(getExecel(QList<Submit*>,Group*)));
    QList<QPushButton*> buttons = {ui->confirmButton, ui->getDoneButton, ui->getPatternButton, ui->setExcelButton};
    for(QPushButton* button : buttons) {
        button->setEnabled(false);
        StyleManager::GetInstance()->setDisableButtonStyle(button, button->text(), true, 16, 13);
    }

    StyleManager::GetInstance()->setLineEditStyle(ui->searchLineEdit, "Название группы", false, 16, 180, 50);
    QCompleter* completer = new QCompleter(ClientState::GetInstance()->getGroupsName());
    qInfo()<<ClientState::GetInstance()->getGroupsName();
    ui->searchLineEdit->setCompleter(completer);
    StyleManager::GetInstance()->setCompleterStyle(completer);

    StyleManager::GetInstance()->setCustomButtonStyle(ui->exitButton, ui->exitButton->text(), "#E65D4F", true, 16, 4);

    ui->getCheckBox->setFont(StyleManager::GetInstance()->getRegular());
    ui->getCheckBox->setFixedWidth(ui->getCheckBox->sizeHint().width());
    ui->updateCheckBox->setFont(StyleManager::GetInstance()->getRegular());
    ui->updateCheckBox->setFixedWidth(ui->updateCheckBox->sizeHint().width());

    StyleManager::GetInstance()->setLabelStyle(ui->pathLabel, "", false, "black", true, 14);

    StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Данной группы не  существует", true, "red", false, 16);
    ui->warningLabel->setFixedSize(ui->warningLabel->sizeHint().width(), ui->warningLabel->sizeHint().height());
}

AdminScore::~AdminScore()
{
    delete ui;
}

void AdminScore::on_exitButton_clicked()
{
    this->close();
}

//чекбокс получить
void AdminScore::on_getCheckBox_clicked()
{
    if (ui->updateCheckBox->isEnabled())
    {
        if (!ClientState::GetInstance()->getGroupsName().contains(ui->searchLineEdit->text()))
        {
            ui->getCheckBox->setChecked(false);
            ui->warningLabel->show();
            ui->searchLineEdit->setEnabled(true);
        }
        else
        {
            ui->getCheckBox->setChecked(true);
            ui->warningLabel->hide();
            ui->updateCheckBox->setEnabled(false);
            ui->getDoneButton->setEnabled(true);
            StyleManager::GetInstance()->setBlueButtonStyle(ui->getDoneButton, ui->getDoneButton->text(), true, 16, 13);
            ui->searchLineEdit->setEnabled(false);
        }
    }
    else
    {
        ui->getCheckBox->setChecked(false);
        ui->searchLineEdit->setEnabled(true);
        ui->updateCheckBox->setEnabled(true);
        ui->getDoneButton->setEnabled(false);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->getDoneButton, ui->getDoneButton->text(), true, 16, 13);
    }
}

//чекбокс обновить
void AdminScore::on_updateCheckBox_clicked()
{
    if (ui->getCheckBox->isEnabled())
    {
        if (!ClientState::GetInstance()->getGroupsName().contains(ui->searchLineEdit->text()))
        {
            ui->updateCheckBox->setChecked(false);
            ui->warningLabel->show();
            ui->searchLineEdit->setEnabled(true);
        }
        else
        {
            ui->updateCheckBox->setChecked(true);
            ui->searchLineEdit->setEnabled(false);
            ui->warningLabel->hide();
            ui->getCheckBox->setEnabled(false);
            QList<QPushButton*> buttons = {ui->confirmButton, ui->getPatternButton, ui->setExcelButton};
            for(QPushButton* button : buttons) {
                button->setEnabled(true);
                StyleManager::GetInstance()->setBlueButtonStyle(button, button->text(), true, 16, 13);
            }
        }
    }
    else
    {
        ui->updateCheckBox->setChecked(false);
        ui->searchLineEdit->setEnabled(true);
        ui->getCheckBox->setEnabled(true);
        QList<QPushButton*> buttons = {ui->confirmButton, ui->getPatternButton, ui->setExcelButton};
        for(QPushButton* button : buttons) {
            button->setEnabled(false);
            StyleManager::GetInstance()->setDisableButtonStyle(button, button->text(), true, 16, 13);
        }
    }
}

//получить группу
void AdminScore::on_getDoneButton_clicked()
{
    ClientState::GetInstance()->getMainwindow()->getDownload()->raise();
    ClientState::GetInstance()->getMainwindow()->getDownload()->show();
    ClientState::GetInstance()->getMainwindow()->doAllButtonDisable();
    QJsonObject json;
    json["GroupName"]=ui->searchLineEdit->text();
    json["CourseId"]=int(course->GetCourseId());
    ClientManager::GetInstance()->SendJsonToServer(GETSUBMITS,json);
}

//получить шаблон
void AdminScore::on_getPatternButton_clicked()
{
    on_getDoneButton_clicked();
}

//назначить эксель
void AdminScore::on_setExcelButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор таблицы", QDir::homePath(), "Excel files (*.xlsx)");
    ui->pathLabel->setText(path);
    ui->pathLabel->setFixedSize(ui->pathLabel->sizeHint().width(), ui->pathLabel->sizeHint().height());
}

//применить
void AdminScore::on_confirmButton_clicked()
{

}

void AdminScore::getExecel(QList<Submit *> submits, Group *group)
{
    XlsxUtils::GetInstance()->getCourseScoreTable(submits,course,group);
    this->close();
    ClientState::GetInstance()->getMainwindow()->getDownload()->close();
    ClientState::GetInstance()->getMainwindow()->doAllButtonClicked();
    for(auto temp:submits){
        delete temp->student;
        delete temp->work;
        delete temp;
    }
    submits.clear();
    delete group;
}

