#include "potokadder.h"
#include "ui_potokadder.h"
#include <QFileDialog>
#include <QDir>
#include "ClientState/clientstate.h"

PotokAdder::PotokAdder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PotokAdder)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, false);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 80);
    StyleManager::GetInstance()->setLabelStyle(ui->Error_Box, "Ошибка, такой группы не существует", false, "red", true, 12);
    StyleManager::GetInstance()->setLabelStyle(ui->PotoknameError, "Ошибка, это название занято", false, "red", false, 12);
    StyleManager::GetInstance()->setLabelStyle(ui->label, "Путь до таблицы:", false, "black", true, 14);
    StyleManager::GetInstance()->setLabelStyle(ui->label_4, "Внимание, при загрузке таблицы приоритет\nзаполнения данных отдается ей", false, "black", true, 14);
    StyleManager::GetInstance()->setLineEditStyle(ui->Group_name, "Название группы", true, 16, 170, 30);
    StyleManager::GetInstance()->setLineEditStyle(ui->Potok_name, "Название потока", true, 16, 170, 30);
    StyleManager::GetInstance()->setCustomButtonStyle(ui->FoundExcel, "Добавить таблицу", "green", true, 16, 13);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->Add_line, "Добавить\nновую строку", true, 16, 13);
    StyleManager::GetInstance()->setCustomButtonStyle(ui->Add_line_2, "Удалить строку", "#E65D4F", true, 16, 13);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->Create_potok, "Создать поток", true, 16, 13);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->resize(this->frameGeometry().width()-25-350,this->frameGeometry().height() - 30);

    GroupNames.clear();
    GroupErrors.clear();
    GroupNames.append(ui->Group_name);
    GroupErrors.append(ui->Error_Box);
    qDebug() << ui->Group_name->geometry();
}

PotokAdder::~PotokAdder()
{
    delete ui;
}

void PotokAdder::on_Add_line_clicked()
{
    counter++;
    QLineEdit* newLine = new QLineEdit(ui->scrollAreaWidgetContents);
    QLabel* newLabel = new QLabel(ui->scrollAreaWidgetContents);
    StyleManager::GetInstance()->setLineEditStyle(newLine, "Название группы", true, 16, 170, 30);
    StyleManager::GetInstance()->setLabelStyle(newLabel, "Ошибка, такой группы не существует", false, "red", false, 12);
    GroupNames.append(newLine);
    GroupErrors.append(newLabel);
    GroupNames[counter]->setGeometry(ui->Group_name->x(), counter == 1 ? ui->Group_name->y()*2 : ui->Group_name->y()*(counter + 1), ui->Group_name->width(), ui->Group_name->height());
    GroupErrors[counter]->setGeometry(ui->Error_Box->x(), counter == 1 ? ui->Error_Box->y()*2 : ui->Error_Box->y()*(counter + 1), ui->Error_Box->width(), ui->Error_Box->height());

    GroupNames[counter]->show();
    GroupErrors[counter]->show();
    if (counter*(ui->Group_name->height()*4) > this->frameGeometry().height() - 20)
        ui->scrollAreaWidgetContents->setMinimumHeight(counter*(ui->Group_name->height()*4));
    //qDebug() << GroupNames[counter]->geometry();
    //GroupNames[counter]->move(ui->Group_name->x(), ui->Group_name->y()*counter+1);

}


void PotokAdder::on_Add_line_2_clicked()
{
    if (counter > 0){
    GroupErrors[counter]->close();
    GroupErrors.removeAt(counter);
    GroupNames[counter]->close();
    GroupNames.removeAt(counter);
    if (counter*(ui->Group_name->height()*4) < this->frameGeometry().height() - 20)
        ui->scrollAreaWidgetContents->setMinimumHeight(this->frameGeometry().height() - 20);
    counter--;
    }
}


void PotokAdder::on_FoundExcel_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбор таблицы", QDir::homePath(), "Excel files (*.xlsx *.xls);");

    ui->Excel_Path->setText(path);
}


void PotokAdder::on_Create_potok_clicked()
{
    if (!ClientState::GetInstance()->getGroupsName().contains(ui->Group_name->text()))
        ui->Error_Box->setVisible(true);
    for (int i = 1; i < counter+1; i++){
        if (!ClientState::GetInstance()->getGroupsName().contains(GroupNames[i]->text()))
            GroupErrors[i]->setVisible(true);
            }
    if (ClientState::GetInstance()->getPotoksName().contains(ui->Potok_name->text()))
                ui->PotoknameError->setVisible(true);

}

