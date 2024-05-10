#include "adminscore.h"
#include "ui_adminscore.h"
#include "StyleManager/stylemanager.h"
#include "ClientState/clientstate.h"

AdminScore::AdminScore(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminScore)
{
    ui->setupUi(this);

    QList<QPushButton*> buttons = {ui->confirmButton, ui->getDoneButton, ui->getPatternButton, ui->setExcelButton};
    for(QPushButton* button : buttons) {
        button->setEnabled(false);
        StyleManager::GetInstance()->setDisableButtonStyle(button, button->text(), true, 16, 13);
    }

    StyleManager::GetInstance()->setLineEditStyle(ui->searchLineEdit, "Название группы", false, 16, 180, 50);
    QCompleter* completer = new QCompleter(ClientState::GetInstance()->getGroupsName());
    ui->searchLineEdit->setCompleter(completer);
    StyleManager::GetInstance()->setCompleterStyle(completer);

    StyleManager::GetInstance()->setCustomButtonStyle(ui->exitButton, ui->exitButton->text(), "#E65D4F", true, 16, 4);

    ui->getCheckBox->setFont(StyleManager::GetInstance()->getRegular());
    ui->getCheckBox->setFixedWidth(ui->getCheckBox->sizeHint().width());
    ui->updateCheckBox->setFont(StyleManager::GetInstance()->getRegular());
    ui->updateCheckBox->setFixedWidth(ui->updateCheckBox->sizeHint().width());

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
            ui->warningLabel->show();
        }
        else
        {
            ui->warningLabel->hide();
            ui->updateCheckBox->setEnabled(false);
            ui->getDoneButton->setEnabled(true);
            StyleManager::GetInstance()->setBlueButtonStyle(ui->getDoneButton, ui->getDoneButton->text(), true, 16, 13);
        }
    }
    else
    {
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
            ui->warningLabel->show();
        }
        else
        {
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

}

//получить шаблон
void AdminScore::on_getPatternButton_clicked()
{

}

//назначить эксель
void AdminScore::on_setExcelButton_clicked()
{

}

//применить
void AdminScore::on_confirmButton_clicked()
{

}

