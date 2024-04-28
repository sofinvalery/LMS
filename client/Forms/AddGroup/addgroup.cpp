#include "addgroup.h"
#include "ui_addgroup.h"
#include "ClientState/clientstate.h"
#include <QCompleter>

AddGroup::AddGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddGroup)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 90);
    ui->addButton->setEnabled(false);
    ui->createButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);

    StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Данная группа уже существует", true, "red", false, 16);
    ui->warningLabel->move(250,200);

    StyleManager::GetInstance()->setLabelStyle(ui->infoLabel, "Внимание, при загрузке таблицы приоретет \n заполнения данных отдается ей", true, "black", true, 12);

    StyleManager::GetInstance()->setLabelStyle(ui->ExcelPath, "Путь к файлу", true, "black", true, 12);

    StyleManager::GetInstance()->setDisableButtonStyle(ui->createButton, "Создать группу", true, 16, 13);
    ui->createButton->setFixedSize(145, 45);

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->resize(ui->studentLineEdit->width() + ui->numberLabel->width() + 100, StyleManager::GetInstance()->getScreenHeight() - 300);
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, false);

    StyleManager::GetInstance()->setLineEditStyle(ui->studentLineEdit, "ФИО", true, 16, 150, 25);

    StyleManager::GetInstance()->setLineEditStyle(ui->groupLineEdit, "Название группы", true, 16, 200, 30);

    nameList.append(ui->studentLineEdit);
    numberList.append(ui->numberLabel);

    StyleManager::GetInstance()->setDisableButtonStyle(ui->deleteButton, "Удалить", true, 16, 13);

    ui->deleteButton->setFixedSize(145, 45);

    QCompleter* completer = new QCompleter(ClientState::GetInstance()->getGroupsName());
    ui->groupLineEdit->setCompleter(completer);

    StyleManager::GetInstance()->setCustomButtonStyle(ui->exampleExcelButton, "Получить\nпример таблицы", "green", true, 14, 13);
    ui->exampleExcelButton->setFixedSize(145, 45);

    //numberlabel
    ui->numberLabel->setFont(StyleManager::GetInstance()->getBold());
    ui->numberLabel->setStyleSheet("font-size: 16px;");

    //excelfind
    StyleManager::GetInstance()->setCustomButtonStyle(ui->FindExcelButton, "Выбрать таблицу", "green", true, 14, 13);
    ui->FindExcelButton->setFixedSize(145, 45);

    //addbutton
    StyleManager::GetInstance()->setDisableButtonStyle(ui->addButton, "Добавить", true, 16, 13);
    ui->addButton->setFixedSize(145, 45);
}

AddGroup::~AddGroup()
{
    delete ui;
}

void AddGroup::on_studentBox_clicked()
{
    if (!ui->addButton->isEnabled() && count != 50)
    {
        ui->addButton->setEnabled(true);
        StyleManager::GetInstance()->setBlueButtonStyle(ui->addButton, "Добавить", true, 16, 13);
    }

    if (!ui->createButton->isEnabled())
    {
        ui->createButton->setEnabled(true);
        StyleManager::GetInstance()->setBlueButtonStyle(ui->createButton, "Создать группу", true, 16, 13);
    }

    if (ui->teacherBox->isEnabled())
    {
        ui->teacherBox->setEnabled(false);
    }
    else
    {
        ui->addButton->setEnabled(false);
        ui->createButton->setEnabled(false);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->createButton, "Создать группу", true, 16, 13);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->addButton, "Добавить", true, 16, 13);
        ui->teacherBox->setEnabled(true);
    }
}


void AddGroup::on_teacherBox_clicked()
{
    if (!ui->addButton->isEnabled() && count != 50)
    {
        ui->addButton->setEnabled(true);
        StyleManager::GetInstance()->setBlueButtonStyle(ui->addButton, "Добавить", true, 16, 13);
    }

    if (!ui->createButton->isEnabled())
    {
        ui->createButton->setEnabled(true);
        StyleManager::GetInstance()->setBlueButtonStyle(ui->createButton, "Создать группу", true, 16, 13);
    }

    if (ui->studentBox->isEnabled())
    {
        ui->studentBox->setEnabled(false);
    }
    else
    {
        ui->addButton->setEnabled(false);
        ui->createButton->setEnabled(false);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->createButton, "Создать группу", true, 16, 13);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->addButton, "Добавить", true, 16, 13);
        ui->studentBox->setEnabled(true);
    }
}


void AddGroup::on_addButton_clicked()
{
    count++;
    heightLine += 30;
    ui->deleteButton->setEnabled(true);
    StyleManager::GetInstance()->setCustomButtonStyle(ui->deleteButton, "Удалить", "#E65D4F", true, 16, 13);
    if (count == 49)
    {
        ui->addButton->setEnabled(false);
    }
    QLineEdit* newLine = new QLineEdit(ui->scrollAreaWidgetContents);
    QLabel* newLabel = new QLabel(ui->scrollAreaWidgetContents);
    StyleManager::GetInstance()->setLineEditStyle(newLine, "ФИО", true, 16, 150, 25);
    nameList.append(newLine);
    newLabel->setFont(StyleManager::GetInstance()->getBold());
    newLabel->setText(QString::number(count + 1));
    newLabel->setStyleSheet("font-size: 16px;");
    numberList.append(newLabel);
    numberList[count]->setGeometry(ui->numberLabel->x(), ui->numberLabel->y() + heightLine, ui->numberLabel->width(), ui->numberLabel->height());
    nameList[count]->setGeometry(ui->studentLineEdit->x(), ui->studentLineEdit->y() + heightLine, ui->studentLineEdit->width(), ui->studentLineEdit->height());
    numberList[count]->setGeometry(ui->numberLabel->x(), ui->numberLabel->y() + heightLine, ui->numberLabel->width(), ui->numberLabel->height());
    nameList[count]->setGeometry(ui->studentLineEdit->x(), ui->studentLineEdit->y() + heightLine, ui->studentLineEdit->width(), ui->studentLineEdit->height());
    numberList[count]->show();
    nameList[count]->show();
    ui->scrollAreaWidgetContents->setMinimumHeight(heightLine + ui->studentLineEdit->height() + ui->numberLabel->y() + 10);
}

void AddGroup::on_deleteButton_clicked()
{
    if (count > 0){
        nameList[count]->close();
        nameList.removeAt(count);
        numberList[count]->close();
        numberList.removeAt(count);
        count--;
        heightLine -= 30;
        ui->scrollAreaWidgetContents->setMinimumHeight(heightLine + ui->studentLineEdit->height() + ui->numberLabel->y() + 10);
    }
    if (count == 0)
    {
        StyleManager::GetInstance()->setDisableButtonStyle(ui->deleteButton, "Удалить", true, 16, 13);
        ui->deleteButton->setEnabled(false);
    }
}

void AddGroup::on_createButton_clicked()
{
    // список ФИО - nameList
    // ui->studentBox->isEnabled(); - проверка нажат ли чекбокс студентов
    // ui->teacherBox->isEnabled(); - проверка нажат ли чекбокс преподов
    if (ClientState::GetInstance()->getGroupsName().contains(ui->groupLineEdit->text()))
    {
        ui->warningLabel->show();
    }
    else
    {
        ui->warningLabel->hide();
    }
}


void AddGroup::on_FindExcelButton_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбор таблицы", QDir::homePath(), "Excel files (*.xlsx *.xls);");

    ui->ExcelPath->setText(path);
}


//получить пример таблциы эксель
void AddGroup::on_exampleExcelButton_clicked()
{

}

