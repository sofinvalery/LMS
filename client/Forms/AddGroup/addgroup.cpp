#include "addgroup.h"
#include "ui_addgroup.h"
#include "ClientState/clientstate.h"
#include "StyleManager/stylemanager.h"
#include <QScreen>

AddGroup::AddGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddGroup)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-top: 3px solid lightgrey;"
        "}");
    ui->addButton->setEnabled(false);
    ui->createButton->setEnabled(false);
    StyleManager::GetInstance()->setDisableButtonStyle(ui->createButton, "Создать группу", "bold", 16, 13);
    ui->createButton->setFixedSize(145, 45);

    QScreen* scr = QGuiApplication::primaryScreen();

    nameList.append(ui->studentLineEdit);

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height() - 20);
    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height() - 20);
    this->move(0, 90);

    //numberlabel
    ui->numberLabel->setFont(StyleManager::GetInstance()->getBold());
    ui->numberLabel->setStyleSheet("font-size: 16px;");

    //addbutton
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->addButton, "", "bold", 1, 1);
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
        StyleManager::GetInstance()->setBlueButtonStyle(ui->createButton, "Создать группу", "bold", 16, 13);
    }

    if (ui->teacherBox->isEnabled())
    {
        ui->teacherBox->setEnabled(false);
    }
    else
    {
        ui->addButton->setEnabled(false);
        ui->createButton->setEnabled(false);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->createButton, "Создать группу", "bold", 16, 13);
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
        StyleManager::GetInstance()->setBlueButtonStyle(ui->createButton, "Создать группу", "bold", 16, 13);
    }

    if (ui->studentBox->isEnabled())
    {
        ui->studentBox->setEnabled(false);
    }
    else
    {
        ui->addButton->setEnabled(false);
        ui->createButton->setEnabled(false);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->createButton, "Создать группу", "bold", 16, 13);
        ui->studentBox->setEnabled(true);
    }
}


void AddGroup::on_addButton_clicked()
{
    heightLine += 30;
    count++;
    if (count == 25)
    {
        ui->addButton->setEnabled(false);
    }
    QLineEdit* newLine = new QLineEdit(ui->groupBox);
    QLabel* newLabel = new QLabel(ui->groupBox);
    newLine->setPlaceholderText("ФИО");
    nameList.append(newLine);

    newLabel->setFont(StyleManager::GetInstance()->getBold());
    newLabel->setText(QString::number(count));
    newLabel->setStyleSheet("font-size: 16px;");
    newLabel->move(ui->numberLabel->pos().x(), ui->numberLabel->pos().y() + heightLine);
    newLabel->show();

    newLine->move(ui->studentLineEdit->pos().x(), ui->studentLineEdit->pos().y() + heightLine);
    newLine->show();
}


void AddGroup::on_createButton_clicked()
{
    foreach(QLineEdit* lineEdit, nameList)
    {
        QString text = lineEdit->text();
        qDebug() << text;
    }
}

