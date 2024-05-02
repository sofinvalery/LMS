#include "groupeditor.h"
#include "ui_groupeditor.h"
#include "ClientState/clientstate.h"
#include <QCompleter>
#include "ClientManager/socketparser.h"
#include "XlsxUtils/xlsxutils.h"


groupEditor::groupEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::groupEditor)
{
    ui->setupUi(this);
    connect(SocketParser::GetInstance(),SIGNAL(getShowEditGroup()),this,SLOT(ShowGroup()),Qt::QueuedConnection);
    StyleManager::GetInstance()->setWidgetStyle(this, ui->groupBox, 90);

    StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Данной группы не существует", true, "red", false, 16);

    ui->createButton->setFixedSize(145, 45);

    ui->addButton->setFixedSize(145, 45);
    ui->addButton->move(ui->createButton->x() + 165, ui->createButton->y());
    StyleManager::GetInstance()->setDisableButtonStyle(ui->createButton, "Применить\nизменения", true, 16, 13);
    StyleManager::GetInstance()->setDisableButtonStyle(ui->addButton, "Добавить\nстудента", true, 16, 13);
    ui->createButton->setEnabled(false);
    ui->addButton->setEnabled(false);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight()-200);
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, false);

    StyleManager::GetInstance()->setLineEditStyle(ui->searchLineEdit, "Название группы", false, 16, 200, 30);
    //searchLineEdit
    ui->searchLineEdit->setPlaceholderText("Название группы");
    QCompleter* completer = new QCompleter(ClientState::GetInstance()->getGroupsName());
    StyleManager::GetInstance()->setCompleterStyle(completer);
    ui->searchLineEdit->setCompleter(completer);

    //showGroupButton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->showGroupButton, "Показать\nстудентов", true, 16, 13);
    ui->showGroupButton->setFixedSize(145, 45);
}

groupEditor::~groupEditor()
{
    delete ui;
}

void groupEditor::ShowGroup()
{
    ClientState::GetInstance()->getMainwindow()->getDownload()->close();
    this->raise();
    StyleManager::GetInstance()->setBlueButtonStyle(ui->createButton, "Изменить\nгруппу", true, 16, 13);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->addButton, "Добавить", true, 16, 13);
    ui->createButton->setEnabled(true);
    ui->addButton->setEnabled(true);
    for (int i = 0; i < ClientState::GetInstance()->getGroup()->getParticipants().size(); i++)
    {
        heightLine += 35;
        Authentication* student = ClientState::GetInstance()->getGroup()->getParticipants()[i];
        QLabel* login = new QLabel(ui->scrollAreaWidgetContents);
        QPushButton* generateButton = new QPushButton(ui->scrollAreaWidgetContents);
        QPushButton* deleteButton = new QPushButton(ui->scrollAreaWidgetContents);
        QLineEdit* newLine = new QLineEdit(ui->scrollAreaWidgetContents);

        nameList.append(newLine);
        deleteButtons.append(deleteButton);
        generatePasswordButtons.append(generateButton);
        logins.append(login);

        connect(generateButton, &QPushButton::clicked, this, &groupEditor::generateButton_clicked);
        connect(deleteButton, &QPushButton::clicked, this, &groupEditor::deleteButton_clicked);

        StyleManager::GetInstance()->setLineEditStyle(newLine, "ФИО", true, 16, 150, 30);

        //generatebutton
        generateButton->move(345, heightLine);
        generateButton->setFixedSize(145, 25);
        StyleManager::GetInstance()->setBlueButtonStyle(generateButton, "Новый пароль", true, 16, 4);
        generateButton->show();

        //deletebutton
        deleteButton->move(310, heightLine);
        deleteButton->setFixedSize(25, 25);
        StyleManager::GetInstance()->setCustomButtonStyle(deleteButton, "Х", "#E65D4F", true, 16, 4);
        deleteButton->show();

        StyleManager::GetInstance()->setLabelStyle(login, student->GetLogin(), true, "black", false, 12);
        login->setGeometry(10, heightLine, 130, 25);
        login->show();

        nameList[i]->setGeometry(150, heightLine, 150, 25);
        nameList[i]->setText(student->GetFIO());
        nameList[i]->setPlaceholderText(student->GetFIO());
        nameList[i]->show();
        ui->scrollAreaWidgetContents->setMinimumHeight(heightLine+200);
    }
}

void groupEditor::on_showGroupButton_clicked()
{
    heightLine = 0;
    nameList.clear();
    deleteButtons.clear();
    generatePasswordButtons.clear();
    logins.clear();
    if (!ClientState::GetInstance()->getGroupsName().contains(ui->searchLineEdit->text()))
    {
        StyleManager::GetInstance()->setLabelStyle(ui->warningLabel, "Данной группы не существует", true, "red",true, 16);
        ui->warningLabel->show();

    }
    else
    {
        ClientState::GetInstance()->getMainwindow()->getDownload()->raise();
        ClientState::GetInstance()->getMainwindow()->getDownload()->show();
        QJsonObject json;
        json["groupName"]=ui->searchLineEdit->text();
        ClientManager::GetInstance()->SendJsonToServer(GETGROUP,json);
        ui->warningLabel->hide();
    }
}


void groupEditor::deleteButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int index;
    for(index=0;index<deleteButtons.size();index++)
    {
        if(button==deleteButtons[index])
            break;
    }
    delete nameList[index];
    nameList.erase(nameList.begin()+index);

    delete deleteButtons[index];
    deleteButtons.erase(deleteButtons.begin()+index);

    delete logins[index];
    logins.erase(logins.begin()+index);

    delete generatePasswordButtons[index];
    generatePasswordButtons.erase(generatePasswordButtons.begin()+index);

    int deletedButtonheightLine=index*35+35;
    for(; index<nameList.size();index++)
    {
        generatePasswordButtons[index]->move(345, deletedButtonheightLine);
        nameList[index]->setGeometry(150, deletedButtonheightLine, 150, 25);
        logins[index]->setGeometry(10, deletedButtonheightLine, 130, 25);
        deleteButtons[index]->move(310, deletedButtonheightLine);
        deletedButtonheightLine+=35;
    }
    heightLine-=35;
}

//генерация пароля
void groupEditor::generateButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    StyleManager::GetInstance()->setDisableButtonStyle(button, "Новый пароль", true, 16, 4);
    button->setEnabled(false);
    int index;
    for(index=0;index<generatePasswordButtons.size();index++)
    {
        if(button==generatePasswordButtons[index])
            break;
    }
    if(logins[index]->text()!="unknown")
    {
        QString newPassword= passwordRand(1,10)[0];
        for(auto temp: ClientState::GetInstance()->getGroup()->getParticipants())
        {
            if(temp->GetLogin()==logins[index]->text())
            {
                temp->setPassword(newPassword);
                break;
            }
        }
    }
}

//кнопка добавить чела
void groupEditor::on_addButton_clicked()
{
    heightLine += 35;
    QLabel* login = new QLabel(ui->scrollAreaWidgetContents);
    QPushButton* generateButton = new QPushButton(ui->scrollAreaWidgetContents);
    QPushButton* deleteButton = new QPushButton(ui->scrollAreaWidgetContents);
    QLineEdit* newLine = new QLineEdit(ui->scrollAreaWidgetContents);
    connect(generateButton, &QPushButton::clicked, this, &groupEditor::generateButton_clicked);
    connect(deleteButton, &QPushButton::clicked, this, &groupEditor::deleteButton_clicked);
    StyleManager::GetInstance()->setLineEditStyle(newLine, "ФИО", false, 16, 150, 30);
    StyleManager::GetInstance()->setLabelStyle(login, "unknown", true, "black", false, 12);
    StyleManager::GetInstance()->setBlueButtonStyle(generateButton, "Новый пароль", true, 16, 4);
    StyleManager::GetInstance()->setCustomButtonStyle(deleteButton, "Х", "#E65D4F", true, 16, 4);
    deleteButton->move(310, heightLine);
    deleteButton->setFixedSize(25, 25);
    generateButton->move(345, heightLine);
    generateButton->setFixedSize(145, 25);
    login->setGeometry(10, heightLine, 130, 25);
    newLine->setGeometry(150, heightLine, 150, 25);
    login->show();
    newLine->show();
    deleteButton->show();
    generateButton->show();
    ui->scrollAreaWidgetContents->setMinimumHeight(heightLine+200);
    nameList.append(newLine);
    deleteButtons.append(deleteButton);
    generatePasswordButtons.append(generateButton);
    logins.append(login);
}

//кнопка применить
void groupEditor::on_createButton_clicked()
{
    QString login = ClientState::GetInstance()->getGroup()->getParticipants()[ ClientState::GetInstance()->getGroup()->getParticipants().size()-1]->GetLogin();
    int lastParticipantId = login.split('_')[1].toInt()+1;
    EnumRoles role;
    Group* gr = ClientState::GetInstance()->getGroup();
    if(gr->getIsTeacherGroup())
        role=TEACHER;
    else
        role=STUDENT;
    for(int i=0; i <gr->getParticipants().size();i++){
        if(!(i<nameList.size())){
            delete gr->getParticipants()[i];
            gr->getParticipants().erase(gr->getParticipants().begin()+i);
            i--;
            continue;
        }
        if(gr->getParticipants()[i]->GetLogin()!=logins[i]->text())
        {
            delete gr->getParticipants()[i];
            gr->getParticipants().erase(gr->getParticipants().begin()+i);
            i--;
            continue;
        }
        else{
            if(gr->getParticipants()[i]->GetFIO()!=nameList[i]->text())
                gr->getParticipants()[i]->setFio(nameList[i]->text());
        }
    }
    for(int i=0;i<nameList.size();i++)
        if(logins[i]->text()=="unknown"){
           gr->getParticipants().append(new Authentication(translate(gr->getClassname())+"_"+QString::number(lastParticipantId++),passwordRand(1,10)[0],-100,nameList[i]->text(),"sadsa",role));
        }
    XlsxUtils::GetInstance()->getAddedGroup(gr);
    ClientManager::GetInstance()->SendJsonToServer(UPDATEGROUP,gr->Serialize());
    ClientState::GetInstance()->getMainwindow()->on_mainButton_clicked();
}

