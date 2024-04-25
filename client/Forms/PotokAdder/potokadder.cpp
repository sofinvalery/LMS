#include "potokadder.h"
#include "ui_potokadder.h"
#include <QScreen>
#include <QFileDialog>
#include <QDir>
#include "StyleManager/stylemanager.h"
#include "ClientState/clientstate.h"


PotokAdder::PotokAdder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PotokAdder)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 80);

    QScreen* scr = QGuiApplication::primaryScreen();

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->resize(this->frameGeometry().width()-25-350,this->frameGeometry().height() - 20);

    GroupNames.clear();
    GroupErrors.clear();
    GroupNames.append(ui->Group_name);
    GroupErrors.append(ui->Error_Box);
    StyleManager::GetInstance()->setLabelStyle(ui->Error_Box, "", false, "red", true, 16);

}

PotokAdder::~PotokAdder()
{
    delete ui;
}

void PotokAdder::on_Add_line_clicked()
{
    counter++;
    GroupNames.append(new QLineEdit(ui->scrollAreaWidgetContents));
    GroupErrors.append(new QLabel(ui->scrollAreaWidgetContents));
    GroupNames[counter]->setGeometry(ui->Group_name->x(), counter == 1 ? ui->Group_name->y()*2 : ui->Group_name->y()*(counter + 1), ui->Group_name->width(), ui->Group_name->height());
    GroupErrors[counter]->setGeometry(ui->Error_Box->x(), counter == 1 ? ui->Error_Box->y()*2 : ui->Error_Box->y()*(counter + 1), ui->Error_Box->width(), ui->Error_Box->height());

    StyleManager::GetInstance()->setLabelStyle(GroupErrors[counter], "", false, "red", true, 16);
    GroupNames[counter]->show();
    GroupErrors[counter]->show();
    if (counter*(ui->Group_name->height()*4) > this->frameGeometry().height() - 20)
        ui->scrollAreaWidgetContents->setMinimumHeight(counter*(ui->Group_name->height()*4));

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
    path = QFileDialog::getOpenFileName(this, "Выбор таблицы", QDir::homePath(), "Excel files (*.xlsx)");

    ui->Excel_Path->setText(path);
    counter=0;
    for(int i=1;i<GroupNames.size();i++)
    {
        GroupNames[i]->setText("");
        delete GroupNames[i];
    }
    for(int i=1;i<GroupErrors.size();i++)
    {
        GroupErrors[i]->setText("");
        delete GroupErrors[i];
    }
    GroupNames.clear();
    GroupErrors.clear();
    GroupNames.append(ui->Group_name);
    GroupErrors.append(ui->Error_Box);

    if(path!="")
    {
    if(data!=nullptr)
    {
            delete data;
        data=nullptr;
    }
    data = XlsxUtils::GetInstance()->parsAddingXlsx(path);
    if(data->pathName.size()>0)
    {
        ui->Potok_name->setText(data->titleName);
        ui->Group_name->setText(data->pathName[0]);
        for(int i=1;i<data->pathName.size();i++)
        {
            counter++;
            GroupNames.append(new QLineEdit(ui->scrollAreaWidgetContents));
            GroupNames[i]->setText(data->pathName[i]);
            GroupErrors.append(new QLabel(ui->scrollAreaWidgetContents));
            GroupNames[counter]->setGeometry(ui->Group_name->x(), counter == 1 ? ui->Group_name->y()*2 : ui->Group_name->y()*(counter + 1), ui->Group_name->width(), ui->Group_name->height());
            GroupErrors[counter]->setGeometry(ui->Error_Box->x(), counter == 1 ? ui->Error_Box->y()*2 : ui->Error_Box->y()*(counter + 1), ui->Error_Box->width(), ui->Error_Box->height());

            StyleManager::GetInstance()->setLabelStyle(GroupErrors[counter], "", false, "red", false, 16);
            GroupNames[counter]->show();
            GroupErrors[counter]->show();
            if (counter*(ui->Group_name->height()*4) > this->frameGeometry().height() - 20)
                ui->scrollAreaWidgetContents->setMinimumHeight(counter*(ui->Group_name->height()*4));
        }
    }
    }
}


void PotokAdder::on_Create_potok_clicked()
{
    bool isGood=true;
    for(auto temp:GroupErrors)
    {
        temp->setText("");
    }
    ui->PotoknameError->setText("");
    qInfo()<<ClientState::GetInstance()->getGroupsName();
    if (!ClientState::GetInstance()->getGroupsName().contains(ui->Group_name->text()))
        {
            ui->Error_Box->setText("Ошибка, такой группы не существует");
            isGood=false;
        }
    for (int i = 1; i < counter+1; i++){
        if (!ClientState::GetInstance()->getGroupsName().contains(GroupNames[i]->text()))
        {   GroupErrors[i]->setText("Ошибка, такой группы не существует");
            isGood=false;
        }
    }
    for(int i=0;i<GroupNames.size();i++)
    {
        for(int j=i+1;j<GroupNames.size();j++)
        {
            if(GroupNames[i]->text()==GroupNames[j]->text())
            {
                GroupErrors[j]->setText("Ошибка, такая группа создана выше");
                isGood=false;
            }
        }
    }
    if (ClientState::GetInstance()->getPotoksName().contains(ui->Potok_name->text()))
            {
                ui->PotoknameError->setText("Ошибка, это название занято");
                isGood=false;
            }
    if (ui->Potok_name->text()=="")
    {
        ui->PotoknameError->setText("Название не может быть пустым");
        isGood=false;
    }
    if(isGood){
        QJsonObject json;
        QJsonArray groupComponents;
        for (auto & user : GroupNames)
            groupComponents.append(user->text());
        json["groupsList"]=groupComponents;
        json["unionName"]=ui->Potok_name->text();
        if(data!=nullptr)
            delete data;
        data = new AddingData();
        data->titleName=ui->Potok_name->text();
        QList<QString> path;
        for (auto & user : GroupNames)
            path.append(user->text());
        data->pathName=path;
        XlsxUtils::GetInstance()->getAddedPotok(data);
        ClientManager::GetInstance()->SendJsonToServer(SETNEWPOTOK,json);
        ClientState::GetInstance()->getMainwindow()->on_mainButton_clicked();
    }
}

