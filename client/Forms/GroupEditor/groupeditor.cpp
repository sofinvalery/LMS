#include "groupeditor.h"
#include "ui_groupeditor.h"
#include "ClientState/clientstate.h"
#include <QCompleter>

groupEditor::groupEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::groupEditor)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 90);

    StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Данной группы не существует", true, "red", false, 16);
    ui->warningLabel->move(250,200);

    StyleManager::GetInstance()->setBlueButtonStyle(ui->addButton, "Изменить\nгруппу", true, 16, 13);
    ui->addButton->setFixedSize(145, 45);

    //searchLineEdit
    ui->searchLineEdit->setPlaceholderText("Название группы");
    QCompleter* completer = new QCompleter(ClientState::GetInstance()->getGroupsName());
    ui->searchLineEdit->setCompleter(completer);

    //showGroupButton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->showGroupButton, "Показать\nстудентов", true, 16, 13);
    ui->showGroupButton->setFixedSize(145, 45);
}

groupEditor::~groupEditor()
{
    delete ui;
}

void groupEditor::on_showGroupButton_clicked()
{
    heightLine = 0;
    nameList.clear();
    if (!ClientState::GetInstance()->getGroupsName().contains(ui->searchLineEdit->text()))
    {
        ui->warningLabel->show();
    }
    else
    {
        for (int i = 0; i < ClientState::GetInstance()->getGroup()->getParticipants().size(); i++)
        {
            heightLine += 30;
            Authentication* student = ClientState::GetInstance()->getGroup()->getParticipants()[i];
            QLabel* login = new QLabel(ui->groupBox);
            QPushButton* generateButton = new QPushButton(ui->groupBox);
            QPushButton* deleteButton = new QPushButton(ui->groupBox);
            QLineEdit* newLine = new QLineEdit(ui->groupBox);
            connect(generateButton, &QPushButton::clicked, this, &groupEditor::generateButton_clicked);
            connect(deleteButton, &QPushButton::clicked, this, &groupEditor::deleteButton_clicked);

            //generatebutton
            generateButton->move(345, 78 + heightLine);
            generateButton->setFixedSize(145, 25);
            StyleManager::GetInstance()->setBlueButtonStyle(generateButton, "Новый пароль", true, 16, 4);
            generateButton->show();

            //deletebutton
            deleteButton->move(310, 78 + heightLine);
            deleteButton->setFixedSize(25, 25);
            StyleManager::GetInstance()->setBlueButtonStyle(deleteButton, "Х", true, 16, 4);
            deleteButton->show();

            StyleManager::GetInstance()->setLabelStyle(login, student->GetLogin(), true, "black", false, 12);
            login->setGeometry(10, 78 + heightLine, 130, 25);
            login->show();

            nameList.append(newLine);
            nameList[i]->setGeometry(150, 78 + heightLine, 150, 25);
            nameList[i]->setText(student->GetFIO());
            nameList[i]->setPlaceholderText(student->GetFIO());
            nameList[i]->show();
        }
        ui->warningLabel->hide();
    }
}

void groupEditor::deleteButton_clicked()
{
    emit deleteButtonClicked();
}

void groupEditor::generateButton_clicked()
{
    emit generateButtonClicked();
}

void groupEditor::on_addButton_clicked()
{

}

