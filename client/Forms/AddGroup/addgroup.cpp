#include "addgroup.h"
#include "ui_addgroup.h"
#include "ClientState/clientstate.h"
#include <QCompleter>
#include "../../common/authentication/group.h"
#include "../../common/authentication/generate_password.h"
#include "../../common/authentication/translate.h"

AddGroup::AddGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddGroup)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 90);
    ui->addButton->setEnabled(false);
    ui->createButton->setEnabled(false);
    ui->groupLineEdit->setMaxLength(8);
    StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Данная группа\nуже существует", true, "red", false, 16);
    ui->warningLabel->move(350,220);

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

    StyleManager::GetInstance()->setBlueButtonStyle(ui->deleteButton, "Удалить", true, 16, 13);
    ui->deleteButton->setFixedSize(145, 45);


    StyleManager::GetInstance()->setBlueButtonStyle(ui->exampleExcelButton, "Получить\nпример таблицы", true, 14, 13);
    ui->exampleExcelButton->setFixedSize(145, 45);

    //numberlabel
    ui->numberLabel->setFont(StyleManager::GetInstance()->getBold());
    ui->numberLabel->setStyleSheet("font-size: 16px;");

    //excelfind
    StyleManager::GetInstance()->setBlueButtonStyle(ui->FindExcelButton, "Выбрать таблицу", true, 14, 13);
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
}

void AddGroup::on_createButton_clicked()
{
    // список ФИО - nameList
    // ui->studentBox->isEnabled(); - проверка нажат ли чекбокс студентов
    // ui->teacherBox->isEnabled(); - проверка нажат ли чекбокс преподов
    if (ClientState::GetInstance()->getGroupsName().contains(ui->groupLineEdit->text()) || ui->groupLineEdit->text()=="")
    {
        StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Данная группа \nуже существует", true, "red", false, 16);
        ui->warningLabel->show();
    }
    else
    {
        ui->warningLabel->hide();
        bool isNotEmptyFio=false;
        QList<Authentication*> list;
        QList<QString> passwords = passwordRand(nameList.size(),10);
        QString groupName = translate(ui->groupLineEdit->text());
        bool isTeacherGroup=ui->teacherBox->isEnabled()==true?true:false;
        EnumRoles role;
        if(isTeacherGroup)
            role=TEACHER;
        else
            role=STUDENT;
        for(int i=0;i<nameList.size();i++){
            if(nameList[i]->text()!=""){
                list.append(new Authentication(groupName+"_"+QString::number(i),passwords[i],100,nameList[i]->text(),"none",role));
                isNotEmptyFio=true;
            }
        }
        Group* group = new Group(100,ui->groupLineEdit->text(),isTeacherGroup,list);
        if(isNotEmptyFio)
        {
            if(data!=nullptr)
            {
                delete data;
                data=nullptr;
            }
            XlsxUtils::GetInstance()->getAddedGroup(group);
            QJsonObject json;
            json=group->Serialize();
            for(auto temp:group->getParticipants())
                delete temp;
            group->getParticipants().clear();
            delete group;
            ClientManager::GetInstance()->SendJsonToServer(SETNEWGROUP,json);
            ClientState::GetInstance()->getMainwindow()->on_mainButton_clicked();
        }
        else{
            StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Группа не может\nбыть пустой", true, "red", false, 16);
            ui->warningLabel->show();
        }
    }
}


void AddGroup::on_FindExcelButton_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбор таблицы", QDir::homePath(), "Excel files (*.xlsx)");

    ui->ExcelPath->setText(path);
    count=0;
    heightLine=0;
    if(path!="")
    {
        for(int i=1;i<nameList.size();i++)
        {
            nameList[i]->setText("");
            delete nameList[i];
        }
        nameList.erase(nameList.begin()+1,nameList.end());
        for(int i=1;i<numberList.size();i++)
        {
            numberList[i]->setText("");
            delete numberList[i];
        }
        numberList.erase(numberList.begin()+1,numberList.end());
        if(data!=nullptr)
        {
            delete data;
            data=nullptr;
        }
        data = XlsxUtils::GetInstance()->parsAddingXlsx(path);
        if(data->pathName.size()>0)
        {
            nameList[0]->setText(data->titleName);
            nameList[0]->setText(data->pathName[0]);
        for(int i=1;i<data->pathName.size();i++)
        {
            on_addButton_clicked();
            nameList[i]->setText(data->pathName[i]);
        }
        ui->groupLineEdit->setText(data->titleName);
        }
    }
}


//получить пример таблциы эксель
void AddGroup::on_exampleExcelButton_clicked()
{
    XlsxUtils::GetInstance()->getExampleForAddingGroup();
}

