#include "addgroup.h"
#include "ui_addgroup.h"
#include "ClientState/clientstate.h"
#include "StyleManager/stylemanager.h"
#include "qforeach.h"

AddGroup::AddGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddGroup)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 90);
    ui->addButton->setEnabled(false);
    ui->createButton->setEnabled(false);

    StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Данная группа уже существует", true, "red", false, 16);
    ui->warningLabel->move(250,200);

    StyleManager::GetInstance()->setLabelStyle(ui->successLabel, "Группа успешно создана", true, "green", false, 16);
    ui->successLabel->move(250,200);

    ui->ExcelPath->setFont(StyleManager::GetInstance()->getBold());
    ui->ExcelPath->move(500, 500);
    ui->ExcelPath->setStyleSheet("font-size: 12px;");

    StyleManager::GetInstance()->setDisableButtonStyle(ui->createButton, "Создать группу", true, 16, 13);
    ui->createButton->setFixedSize(145, 45);

    nameList.append(ui->studentLineEdit);
    numberList.append(ui->numberLabel);

    //numberlabel
    ui->numberLabel->setFont(StyleManager::GetInstance()->getBold());
    ui->numberLabel->setStyleSheet("font-size: 16px;");

    //excelfind
    StyleManager::GetInstance()->setBlueButtonStyle(ui->FindExcelButton, "Выбрать таблицу", true, 14, 13);
    ui->FindExcelButton->setFixedSize(145, 45);
    ui->FindExcelButton->move(1000, 700);

    //addbutton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addButton, "", true, 1, 1);
    ui->addButton->setIconSize(QSize(40, 40));
    ui->addButton->setIcon(QIcon(":/img/resources/addButton.png"));
    ui->addButton->setFixedSize(40, 40);
    connect(ui->addButton, &QPushButton::pressed, [=]() {
        ui->addButton->setIconSize(QSize(35, 35)); //
    });
    connect(ui->addButton, &QPushButton::released, [=]() {
        ui->addButton->setIconSize(QSize(40, 40));
    });
}

AddGroup::~AddGroup()
{
    delete ui;
}

void AddGroup::on_studentBox_clicked()
{
    if (!ui->addButton->isEnabled() && count != 25)
    {
        ui->addButton->setEnabled(true);
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
        ui->teacherBox->setEnabled(true);
    }
}


void AddGroup::on_teacherBox_clicked()
{
    if (!ui->addButton->isEnabled() && count != 25)
    {
        ui->addButton->setEnabled(true);
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
        ui->studentBox->setEnabled(true);
    }
}


void AddGroup::on_addButton_clicked()
{
    count++;
    heightLine += 30;
    if (count == 25)
    {
        ui->addButton->setEnabled(false);
    }
    QLineEdit* newLine = new QLineEdit(ui->groupBox);
    QLabel* newLabel = new QLabel(ui->groupBox);
    newLine->setPlaceholderText("ФИО");
    nameList.append(newLine);
    newLabel->setFont(StyleManager::GetInstance()->getBold());
    newLabel->setText(QString::number(count + 1));
    newLabel->setStyleSheet("font-size: 16px;");
    numberList.append(newLabel);
    numberList[count]->setGeometry(ui->numberLabel->x(), ui->numberLabel->y() + heightLine, ui->numberLabel->width(), ui->numberLabel->height());
    nameList[count]->setGeometry(ui->studentLineEdit->x(), ui->studentLineEdit->y() + heightLine, ui->studentLineEdit->width(), ui->studentLineEdit->height());
    numberList[count]->show();
    nameList[count]->show();
}

void AddGroup::on_deleteButton_clicked()
{
    if (count > 1){
        nameList[count]->close();
        nameList.removeAt(count);
        numberList[count]->close();
        numberList.removeAt(count);
        count--;
        heightLine -= 30;
    }
}

void AddGroup::on_createButton_clicked()
{
    bool groupExist = false;
    // список ФИО - nameList
    // ui->studentBox->isEnabled(); - проверка нажат ли чекбокс студентов
    // ui->teacherBox->isEnabled(); - проверка нажат ли чекбокс преподов
    foreach(QString name, ClientState::GetInstance()->getGroupsName()) // проверка на группы
    {
        //qDebug() << name;
        if (name == ui->groupLineEdit->text())
        {
            groupExist = true;
            break;
        }
    }
    if (groupExist)
    {
        ui->warningLabel->show();
        ui->successLabel->hide();
    }
    else
    {
        //добавление группы

        ui->warningLabel->hide();
        ui->successLabel->show();
    }
}


void AddGroup::on_FindExcelButton_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбор таблицы", QDir::homePath(), "Excel files (*.xlsx *.xls);");

    ui->ExcelPath->setText(path);
}


