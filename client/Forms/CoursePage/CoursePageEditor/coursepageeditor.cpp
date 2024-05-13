#include "coursepageeditor.h"
#include "ui_coursepageeditor.h"
#include "StyleManager/stylemanager.h"
#include <QFileDialog>
#include "ClientManager/clientmanager.h"
#include "ClientState/clientstate.h"

CoursePageEditor::CoursePageEditor(CoursePage * coursepage, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoursePageEditor)
{
    ui->setupUi(this);
    this->coursepage = coursepage;
    //StyleManager::GetInstance()->setLineEditStyle(ui->ComponentOrderLineEdit, "Порядок компонента", false, 16, 300, 30);
    StyleManager::GetInstance()->setLabelStyle(ui->ComponentOrderLabel, "Номер компонента по порядку:", false, "black", true, 16);
    StyleManager::GetInstance()->setLabelStyle(ui->MaxMarkLabel, "Максимум баллов за задание:", false, "black", true, 16);
    StyleManager::GetInstance()->setLabelStyle(ui->TaskContentLabel, "Описание задания:", false, "black", true, 16);
    ui->ComponentOrderLabel->setFixedSize(ui->ComponentOrderLabel->sizeHint().width(), ui->ComponentOrderLabel->sizeHint().height());
    ui->MaxMarkLabel->setFixedSize(ui->MaxMarkLabel->sizeHint().width(), ui->MaxMarkLabel->sizeHint().height());
    ui->TaskContentLabel->setFixedSize(ui->TaskContentLabel->sizeHint().width(), ui->TaskContentLabel->sizeHint().height());
    StyleManager::GetInstance()->setLineEditStyle(ui->NameOnComponentLineEdit, "Название компонента", false, 16, 300, 30);
    StyleManager::GetInstance()->setLineEditStyle(ui->AllowedTypeOfFilesLineEdit, "Разрешенные типы файлов", false, 16, 300, 30);
    StyleManager::GetInstance()->setLabelStyle(ui->TestTimeLabel, "Ограничение по времени теста:", false, "black", true, 16);
    StyleManager::GetInstance()->setLabelStyle(ui->TestCountLabel, "Количество вопросов в тесте:", false, "black", true, 16);
    ui->TestTimeLabel->setFixedSize(ui->TestTimeLabel->sizeHint().width(), ui->TestTimeLabel->sizeHint().height());
    ui->TestCountLabel->setFixedSize(ui->TestCountLabel->sizeHint().width(), ui->TestCountLabel->sizeHint().height());

    StyleManager::GetInstance()->setBlueButtonStyle(ui->AddWidgetButton, ui->AddWidgetButton->text(), true, 14, 13);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->EditWidgetButton, ui->EditWidgetButton->text(), true, 14, 13);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->DeleteWidgetButton, ui->DeleteWidgetButton->text(), true, 14, 13);

    StyleManager::GetInstance()->setBlueButtonStyle(ui->ChooseButton, ui->ChooseButton->text(), true, 14, 10);

    StyleManager::GetInstance()->setBlueButtonStyle(ui->DoneButton, ui->DoneButton->text(), true, 14, 13);
    StyleManager::GetInstance()->setBlueButtonStyle(ui->LoadFileButton, ui->LoadFileButton->text(), true, 14, 13);

    StyleManager::GetInstance()->setCustomButtonStyle(ui->exitButton, ui->exitButton->text(), "#E65D4F", true, 16, 4);
    StyleManager::GetInstance()->setLabelStyle(ui->ErrorLabel,"Праверьте правильность\n заполнения полей",true,"red",false,14);

    QList<QPushButton*> buttons = {ui->AddTextButton, ui->AddDzButton, ui->AddFileButton, ui->AddTestButton};
    for(QPushButton* button : buttons) {
        StyleManager::GetInstance()->setBlueButtonStyle(button, button->text(), true, 14, 13);
    }
    ui->ContentTextEdit->hide();
    ui->NameOnComponentLineEdit->hide();
    ui->ComponentOrderSpinBox->hide();
    ui->ComponentOrderLabel->hide();
    ui->AddDzButton->hide();
    ui->AddFileButton->hide();
    ui->AddTestButton->hide();
    ui->AddTextButton->hide();
    ui->LoadFileButton->hide();
    ui->PathLabel1->hide();
    ui->PathLabel2->hide();
    ui->AllowedTypeOfFilesLineEdit->hide();
    ui->MaxMarkLabel->hide();
    ui->MaxMarkSpinBox->hide();
    ui->TaskContentLabel->hide();
    ui->TestTimeLabel->hide();
    ui->TestTimeEdit->hide();
    ui->TestTimeEdit->setMaximumTime(QTime(03, 55));
    ui->TestCountLabel->hide();
    ui->TestCountSpinBox->hide();
    ui->ChooseButton->hide();

}

CoursePageEditor::~CoursePageEditor()
{
    delete ui;
}

void CoursePageEditor::on_LoadFileButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор картинки", QDir::homePath(), "All Files (*.*)");
    ui->PathLabel2->setText(path);
}


void CoursePageEditor::on_AddWidgetButton_clicked()
{
    if(ui->DeleteWidgetButton->isEnabled()){
        on_mainButton_clicked(ui->AddWidgetButton);
        ui->ComponentOrderSpinBox->setMaximum(coursepage->GetCourse()->getListComponents().size() + 1);
        ui->ComponentOrderSpinBox->setValue(1);
        ui->DeleteWidgetButton->setEnabled(false);
        ui->EditWidgetButton->setEnabled(false);
        ui->AddDzButton->show();
        ui->AddFileButton->show();
        ui->AddTestButton->show();
        ui->AddTextButton->show();
        ui->AddDzButton->setEnabled(true);
        ui->AddTestButton->setEnabled(true);
        ui->AddTextButton->setEnabled(true);
        ui->AddFileButton->setEnabled(true);
    }
    else{
        ui->DeleteWidgetButton->setEnabled(true);
        ui->EditWidgetButton->setEnabled(true);
        on_mainButton_clickedAgain();
        on_AddButton_clickedAgain();
        ui->AddDzButton->hide();
        ui->AddFileButton->hide();
        ui->AddTestButton->hide();
        ui->AddTextButton->hide();

        AddingStatus = 0;
        ui->ContentTextEdit->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->ComponentOrderLabel->hide();
        ui->LoadFileButton->hide();
        ui->PathLabel1->hide();
        ui->PathLabel2->hide();

        ui->TestTimeLabel->hide();
        ui->TestTimeEdit->hide();
        ui->TestCountLabel->hide();
        ui->TestCountSpinBox->hide();

        ui->AllowedTypeOfFilesLineEdit->hide();
        ui->MaxMarkLabel->hide();
        ui->MaxMarkSpinBox->hide();
        ui->TaskContentLabel->hide();
    }
}


void CoursePageEditor::on_EditWidgetButton_clicked()
{
    if(ui->AddWidgetButton->isEnabled()){
        on_mainButton_clicked(ui->EditWidgetButton);
        ui->ComponentOrderSpinBox->setMaximum(coursepage->GetCourse()->getListComponents().size());
        ui->ComponentOrderSpinBox->setValue(1);
        ui->AddWidgetButton->setEnabled(false);
        ui->DeleteWidgetButton->setEnabled(false);
        ui->ComponentOrderSpinBox->show();
        ui->ComponentOrderLabel->show();
        ui->ChooseButton->show();
        //ui->NameOnComponent->show();
    }
    else{
        on_mainButton_clickedAgain();
        ui->AddWidgetButton->setEnabled(true);
        ui->DeleteWidgetButton->setEnabled(true);
        ui->ComponentOrderSpinBox->hide();
        ui->ComponentOrderLabel->hide();
        ui->ChooseButton->hide();
        ui->ComponentOrderSpinBox->setEnabled(true);
        ui->ContentTextEdit->setText("");
        ui->ComponentOrderLabel->hide();
        ui->ContentTextEdit->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->AllowedTypeOfFilesLineEdit->hide();
        ui->MaxMarkLabel->hide();
        ui->MaxMarkSpinBox->hide();
        ui->TaskContentLabel->hide();
        ui->TestTimeLabel->hide();
        ui->TestTimeEdit->hide();
        ui->TestCountLabel->hide();
        ui->TestCountSpinBox->hide();
        ui->LoadFileButton->hide();
        ui->PathLabel1->hide();
        ui->PathLabel2->hide();
        //ui->NameOnComponent->hide();
    }
}


void CoursePageEditor::on_DeleteWidgetButton_clicked()
{
    if(ui->AddWidgetButton->isEnabled()){
        on_mainButton_clicked(ui->DeleteWidgetButton);
        if(!coursepage->GetCourse()->getListComponents().isEmpty()){
            ui->ComponentOrderSpinBox->setMaximum(coursepage->GetCourse()->getListComponents().size());
            ui->ComponentOrderSpinBox->setValue(1);
            DeletingStatus = 1;
            ui->AddWidgetButton->setEnabled(false);
            ui->EditWidgetButton->setEnabled(false);
            ui->ComponentOrderSpinBox->show();
            ui->ComponentOrderLabel->show();
        }
    }
    else{
        on_mainButton_clickedAgain();
        DeletingStatus = 0;
        ui->AddWidgetButton->setEnabled(true);
        ui->EditWidgetButton->setEnabled(true);
        ui->ComponentOrderSpinBox->hide();
        ui->ComponentOrderLabel->hide();
    }
}


void CoursePageEditor::on_DoneButton_clicked()
{
    int32_t courseID= coursepage->GetCourse()->GetCourseId();
    QJsonObject json;
    json["courseID"]=int(courseID);
    if(AddingStatus == 1&&ui->NameOnComponentLineEdit->text()!=""&& (ui->TestTimeEdit->time().hour()*3600+ui->TestTimeEdit->time().minute()*60+ui->TestTimeEdit->time().second())>60){ // добавить на сервер тест (не доделано)
        CourseTest* temp=new CourseTest(-100, ui->ComponentOrderSpinBox->value(), ui->NameOnComponentLineEdit->text(), 10, "", ui->TestTimeEdit->time().hour()*3600+ui->TestTimeEdit->time().minute()*60+ui->TestTimeEdit->time().second(), 1, "", QDate(2004, 03, 02), ui->TestCountSpinBox->value());
        json["type"] = temp->getType();
        json["Class"]= temp->Serialize();
        coursepage->CleanComponents();
        coursepage->GetCourse()->AddCourseComponent(temp, ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
        ClientManager::GetInstance()->SendJsonToServer(ADDCOURSECOMPONENT,json);
        ui->ErrorLabel->hide();
        this->close();
        this->deleteLater();
        return;
    }
    if(AddingStatus == 2&&ui->NameOnComponentLineEdit->text()!=""&& ui->PathLabel2->text()!=""){// добавить на сервер загрузочный файл


        QString fileName;
        for(int j=ui->PathLabel2->text().size()-1; j>=0; j--)
            if(ui->PathLabel2->text()[j]=='/')
            {
                fileName=ui->PathLabel2->text().mid(j+1);
                break;
            }
        QString serverPath = "./data/Courses/media_files/"+QString::number(coursepage->GetCourse()->GetCourseId())+"/";
        ClientManager::GetInstance()->SendFileToServer(ui->PathLabel2->text(),serverPath);
        serverPath+=fileName;
        ClientState::GetInstance()->ShowNotifacate("Перед выходом дождитесь уведомления\nО выгрузке файла:"+fileName,"black");
        CourseMediaFiles* temp=new CourseMediaFiles(-100, ui->ComponentOrderSpinBox->value(), ui->NameOnComponentLineEdit->text(),  serverPath,PDF);
        json["type"] = temp->getType();
        json["Class"]= temp->Serialize();
        coursepage->CleanComponents();
        coursepage->GetCourse()->AddCourseComponent(temp, ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
        ClientManager::GetInstance()->SendJsonToServer(ADDCOURSECOMPONENT,json);
        ui->ErrorLabel->hide();
        this->close();
        this->deleteLater();
        return;
    }
    if (AddingStatus == 3&&ui->ContentTextEdit->toPlainText()!=""&&ui->NameOnComponentLineEdit->text()!=""){                                  // добавить на сервер дз (не доделано)
        CourseTask* temp = new CourseTask(-100, (int32_t)ui->ComponentOrderSpinBox->value(), ui->ContentTextEdit->toPlainText(), ui->MaxMarkSpinBox->value(), 7000, ui->AllowedTypeOfFilesLineEdit->text(), "", QDate(2004,4,4), 0, "", ui->NameOnComponentLineEdit->text());
        json["type"] = temp->getType();
        json["Class"]= temp->Serialize();
        coursepage->CleanComponents();
        coursepage->GetCourse()->AddCourseComponent(temp, ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
        ClientManager::GetInstance()->SendJsonToServer(ADDCOURSECOMPONENT,json);
        ui->ErrorLabel->hide();
        this->close();
        this->deleteLater();
        return;
    }
    if(AddingStatus == 4 && ui->ContentTextEdit->toPlainText()!=""){                                  // добавить на сервер туториал
        CourseTutorials* temp =new CourseTutorials(-100, ui->ComponentOrderSpinBox->value(), ui->ContentTextEdit->toPlainText());
        json["type"] = temp->getType();
        json["Class"]= temp->Serialize();
        coursepage->CleanComponents();
        coursepage->GetCourse()->AddCourseComponent(temp, ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
        ClientManager::GetInstance()->SendJsonToServer(ADDCOURSECOMPONENT,json);
        ui->ErrorLabel->hide();
        this->close();
        this->deleteLater();
        return;
    }
    if (DeletingStatus == 1){            // удалить из сервера элемент  ui->ComponentOrderSpinBox->value()-1
        CourseComponent* temp = coursepage->GetCourse()->getListComponents()[ui->ComponentOrderSpinBox->value()-1];
        json["type"] = temp->getType();
        json["ComponentId"]= temp->getId();
        coursepage->CleanComponents();
        ui->ComponentOrderSpinBox->setMaximum(ui->ComponentOrderSpinBox->maximum()-1);
        coursepage->GetCourse()->DeleteCourseComponent(ui->ComponentOrderSpinBox->value()-1);
        coursepage->ShowComponents();
        ClientManager::GetInstance()->SendJsonToServer(DELETECOURSECOMPONENT,json);
        ui->ErrorLabel->hide();
        this->close();
        this->deleteLater();
        return;
    }
    if (EditingStatus == 1&&ui->NameOnComponentLineEdit->text()!=""&& (ui->TestTimeEdit->time().hour()*3600+ui->TestTimeEdit->time().minute()*60+ui->TestTimeEdit->time().second())>60){                                // поменять на сервере тест
        coursepage->CleanComponents();
        temptest->setTitle(ui->NameOnComponentLineEdit->text());
        temptest->setTimeInSeconds(ui->TestTimeEdit->time().hour()*3600+ui->TestTimeEdit->time().minute()*60+ui->TestTimeEdit->time().second());
        temptest->setTestSize(ui->TestCountSpinBox->value());
        coursepage->ShowComponents();

        json["type"] = temptest->getType();
        json["Class"]= temptest->Serialize();
        ClientManager::GetInstance()->SendJsonToServer(EDITCOURSECOMPONENT,json);

        this->close();
        this->deleteLater();
        return;
    }
    if (EditingStatus == 2&&ui->NameOnComponentLineEdit->text()!=""&& ui->PathLabel2->text()!=""){        // поменять на сервере файл

        QString fileName;
        for(int j=ui->PathLabel2->text().size()-1; j>=0; j--)
            if(ui->PathLabel2->text()[j]=='/')
            {
                fileName=ui->PathLabel2->text().mid(j+1);
                break;
            }
        QString serverPath = "./data/Courses/media_files/"+QString::number(coursepage->GetCourse()->GetCourseId())+"/";
        ClientManager::GetInstance()->SendFileToServer(ui->PathLabel2->text(),serverPath);
        serverPath+=fileName;
        ClientState::GetInstance()->ShowNotifacate("Перед выходом дождитесь уведомления\nО выгрузке файла:"+fileName,"black");

        coursepage->CleanComponents();
        tempfile->setTitle(ui->NameOnComponentLineEdit->text());
        tempfile->setUrl(ui->PathLabel2->text());

        json["type"] = tempfile->getType();
        json["Class"]= tempfile->Serialize();
        ClientManager::GetInstance()->SendJsonToServer(EDITCOURSECOMPONENT,json);

        coursepage->ShowComponents();
        this->close();
        this->deleteLater();
        return;
    }
    if (EditingStatus == 3&&ui->ContentTextEdit->toPlainText()!=""&&ui->NameOnComponentLineEdit->text()!=""){        // поменять на сервере дз
        coursepage->CleanComponents();
        tempdz->setTitle(ui->NameOnComponentLineEdit->text());
        tempdz->setAllowedTypeOfFiles(ui->AllowedTypeOfFilesLineEdit->text());
        tempdz->setContent(ui->ContentTextEdit->toPlainText());
        tempdz->setMaxMark(ui->MaxMarkSpinBox->value());

        json["type"] = tempdz->getType();
        json["Class"]= tempdz->Serialize();
        ClientManager::GetInstance()->SendJsonToServer(EDITCOURSECOMPONENT,json);


        coursepage->ShowComponents();
        this->close();
        this->deleteLater();
        return;
    }
    if (EditingStatus == 4 && ui->ContentTextEdit->toPlainText()!=""){    // поменять на сервере туториал
        coursepage->CleanComponents();
        temptext->setContent(ui->ContentTextEdit->toPlainText());

        json["type"] = temptext->getType();
        json["Class"]= temptext->Serialize();
        ClientManager::GetInstance()->SendJsonToServer(EDITCOURSECOMPONENT,json);

        coursepage->ShowComponents();
        this->close();
        this->deleteLater();
        return;
    }
    ui->ErrorLabel->show();
}


void CoursePageEditor::on_AddFileButton_clicked()
{
    if(ui->LoadFileButton->isHidden()){
        on_AddButton_clicked(ui->AddFileButton);
        AddingStatus = 2;
        ui->LoadFileButton->show();
        ui->PathLabel1->show();
        ui->PathLabel2->show();
        ui->ComponentOrderLabel->show();
        ui->ComponentOrderSpinBox->show();
        ui->NameOnComponentLineEdit->show();
        ui->AddDzButton->setEnabled(false);
        ui->AddTestButton->setEnabled(false);
        ui->AddTextButton->setEnabled(false);
    }
    else{
        on_AddButton_clickedAgain();
        AddingStatus = 0;
        ui->LoadFileButton->hide();
        ui->PathLabel1->hide();
        ui->PathLabel2->hide();
        ui->ComponentOrderLabel->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->AddDzButton->setEnabled(true);
        ui->AddTestButton->setEnabled(true);
        ui->AddTextButton->setEnabled(true);
    }
}


void CoursePageEditor::on_AddTextButton_clicked()
{
    if (ui->ContentTextEdit->isHidden()){
        on_AddButton_clicked(ui->AddTextButton);
        AddingStatus = 4;
        ui->ContentTextEdit->show();
        ui->ComponentOrderLabel->show();
        ui->ComponentOrderSpinBox->show();
        ui->AddDzButton->setEnabled(false);
        ui->AddTestButton->setEnabled(false);
        ui->AddFileButton->setEnabled(false);
    }
    else{
        on_AddButton_clickedAgain();
        AddingStatus = 0;
        ui->ContentTextEdit->setText("");
        ui->ContentTextEdit->hide();
        ui->ComponentOrderLabel->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->AddDzButton->setEnabled(true);
        ui->AddTestButton->setEnabled(true);
        ui->AddFileButton->setEnabled(true);
    }
}


void CoursePageEditor::on_AddTestButton_clicked()
{
    if (ui->ComponentOrderLabel->isHidden()){
        on_AddButton_clicked(ui->AddTestButton);
        ui->TestTimeEdit->setTime(QTime(0,0));
        AddingStatus = 1;
        ui->ComponentOrderLabel->show();
        ui->ComponentOrderSpinBox->show();
        ui->NameOnComponentLineEdit->show();
        ui->TestTimeLabel->show();
        ui->TestTimeEdit->show();
        ui->TestCountLabel->show();
        ui->TestCountSpinBox->show();
        ui->AddTextButton->setEnabled(false);
        ui->AddDzButton->setEnabled(false);
        ui->AddFileButton->setEnabled(false);

    }
    else
    {
        on_AddButton_clickedAgain();
        AddingStatus = 0;
        ui->ComponentOrderLabel->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->TestTimeLabel->hide();
        ui->TestTimeEdit->hide();
        ui->TestCountLabel->hide();
        ui->TestCountSpinBox->hide();
        ui->AddTextButton->setEnabled(true);
        ui->AddDzButton->setEnabled(true);
        ui->AddFileButton->setEnabled(true);
    }
}


void CoursePageEditor::on_AddDzButton_clicked()
{
    if (ui->ComponentOrderLabel->isHidden()){
        on_AddButton_clicked(ui->AddDzButton);
        AddingStatus = 3;
        ui->ComponentOrderLabel->show();
        ui->ComponentOrderSpinBox->show();
        ui->NameOnComponentLineEdit->show();
        ui->ContentTextEdit->show();
        ui->AllowedTypeOfFilesLineEdit->show();
        ui->MaxMarkLabel->show();
        ui->MaxMarkSpinBox->show();
        ui->TaskContentLabel->show();
        ui->AddTextButton->setEnabled(false);
        ui->AddTestButton->setEnabled(false);
        ui->AddFileButton->setEnabled(false);
    }
    else
    {
        on_AddButton_clickedAgain();
        AddingStatus = 0;
        ui->ContentTextEdit->setText("");
        ui->ComponentOrderLabel->hide();
        ui->ComponentOrderSpinBox->hide();
        ui->ContentTextEdit->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->AllowedTypeOfFilesLineEdit->hide();
        ui->MaxMarkLabel->hide();
        ui->MaxMarkSpinBox->hide();
        ui->TaskContentLabel->hide();
        ui->AddTextButton->setEnabled(true);
        ui->AddTestButton->setEnabled(true);
        ui->AddFileButton->setEnabled(true);
    }
}

void CoursePageEditor::on_mainButton_clicked(QPushButton *clickedButton)
{
    StyleManager::GetInstance()->setBlueButtonStyle(clickedButton, clickedButton->text(), true, 14, 13);
    QList<QPushButton*> buttons = {ui->AddWidgetButton, ui->EditWidgetButton, ui->DeleteWidgetButton};
    for(QPushButton* button : buttons) {
        if(button != clickedButton) {
            StyleManager::GetInstance()->setDisableButtonStyle(button, button->text(), true, 14, 13);
        }
    }
}

void CoursePageEditor::on_mainButton_clickedAgain()
{
    QList<QPushButton*> buttons = {ui->AddWidgetButton, ui->EditWidgetButton, ui->DeleteWidgetButton};
    for(QPushButton* button : buttons) {
        StyleManager::GetInstance()->setBlueButtonStyle(button, button->text(), true, 14, 13);
    }
}

void CoursePageEditor::on_AddButton_clicked(QPushButton *clickedButton)
{
    StyleManager::GetInstance()->setBlueButtonStyle(clickedButton, clickedButton->text(), true, 14, 13);
    QList<QPushButton*> buttons = {ui->AddTextButton, ui->AddDzButton, ui->AddFileButton, ui->AddTestButton};
    for(QPushButton* button : buttons) {
        if(button != clickedButton) {
            StyleManager::GetInstance()->setDisableButtonStyle(button, button->text(), true, 14, 13);
        }
    }
}

void CoursePageEditor::on_AddButton_clickedAgain()
{
    QList<QPushButton*> buttons = {ui->AddTextButton, ui->AddDzButton, ui->AddFileButton, ui->AddTestButton};
    for(QPushButton* button : buttons) {
        StyleManager::GetInstance()->setBlueButtonStyle(button, button->text(), true, 14, 13);
    }
}

void CoursePageEditor::on_exitButton_clicked()
{
    this->close();
    delete this;
}


void CoursePageEditor::on_ChooseButton_clicked()
{
    QString type = coursepage->GetCourse()->getListComponents()[ui->ComponentOrderSpinBox->value()-1]->getType();
    bool courseEditFlag = true;
    if (type == "CourseTest" && ui->TestTimeEdit->isHidden() && courseEditFlag){
        //temp = qobject_cast<CourseTest*>(coursepage->GetCourse()->getListComponents()[ui->ComponentOrderSpinBox->value()-1]);
        temptest = qobject_cast<CourseTest*>(coursepage->GetCourse()->getListComponents()[ui->ComponentOrderSpinBox->value()-1]);
        ui->TestTimeEdit->setTime(QTime(temptest->getTimeInSeconds()/3600, temptest->getTimeInSeconds()%3600/60));
        courseEditFlag = false;
        EditingStatus = 1;
        ui->NameOnComponentLineEdit->show();
        ui->NameOnComponentLineEdit->setText(temptest->getTitle());
        ui->TestTimeLabel->show();
        ui->TestTimeEdit->show();
        ui->TestCountLabel->show();
        ui->TestCountSpinBox->setValue(temptest->getTestSize());
        ui->TestCountSpinBox->show();
        ui->ComponentOrderSpinBox->setEnabled(false);
    }
    if (type == "CourseTest" && !ui->TestTimeEdit->isHidden() && courseEditFlag){
        EditingStatus = 0;
        ui->NameOnComponentLineEdit->hide();
        ui->NameOnComponentLineEdit->setText("");
        courseEditFlag = false;
        ui->TestTimeLabel->hide();
        ui->TestTimeEdit->hide();
        ui->TestTimeEdit->setTime(QTime(0, 0));
        ui->TestCountLabel->hide();
        ui->TestCountSpinBox->hide();
        ui->TestCountSpinBox->setValue(1);
        ui->ComponentOrderSpinBox->setEnabled(true);
    }
    if (type == "CourseMediaFiles" && ui->LoadFileButton->isHidden() && courseEditFlag){
        tempfile = qobject_cast<CourseMediaFiles*>(coursepage->GetCourse()->getListComponents()[ui->ComponentOrderSpinBox->value()-1]);
        courseEditFlag = false;
        EditingStatus = 2;
        ui->NameOnComponentLineEdit->show();
        ui->NameOnComponentLineEdit->setText(tempfile->getTitle());
        ui->LoadFileButton->show();
        ui->PathLabel1->show();
        ui->PathLabel2->show();
        ui->PathLabel2->setText(tempfile->getUrl());
        ui->ComponentOrderSpinBox->setEnabled(false);
    }
    if (type == "CourseMediaFiles" && !ui->LoadFileButton->isHidden() && courseEditFlag){
        courseEditFlag = false;
        EditingStatus = 0;
        ui->NameOnComponentLineEdit->hide();
        ui->NameOnComponentLineEdit->setText("");
        ui->LoadFileButton->hide();
        ui->PathLabel1->hide();
        ui->PathLabel2->setText("");
        ui->PathLabel2->hide();
        ui->ComponentOrderSpinBox->setEnabled(true);
    }
    if (type == "CourseTask" && ui->NameOnComponentLineEdit->isHidden() && courseEditFlag){
        tempdz = qobject_cast<CourseTask*>(coursepage->GetCourse()->getListComponents()[ui->ComponentOrderSpinBox->value()-1]);
        courseEditFlag = false;
        EditingStatus = 3;
        ui->NameOnComponentLineEdit->show();
        ui->NameOnComponentLineEdit->setText(tempdz->getTitle());
        ui->ContentTextEdit->setText(tempdz->getContent());
        ui->ContentTextEdit->show();
        ui->MaxMarkLabel->show();
        ui->MaxMarkSpinBox->setValue(tempdz->getMaxMark());
        ui->MaxMarkSpinBox->show();
        ui->AllowedTypeOfFilesLineEdit->setText(tempdz->getAllowedTypeOfFiles());
        ui->AllowedTypeOfFilesLineEdit->show();
        ui->ComponentOrderSpinBox->setEnabled(false);
    }
    if (type == "CourseTask" && !ui->NameOnComponentLineEdit->isHidden() && courseEditFlag){
        courseEditFlag = false;
        EditingStatus = 0;
        ui->ContentTextEdit->setText("");
        ui->ContentTextEdit->hide();
        ui->NameOnComponentLineEdit->hide();
        ui->NameOnComponentLineEdit->setText("");
        ui->AllowedTypeOfFilesLineEdit->hide();
        ui->AllowedTypeOfFilesLineEdit->setText("");
        ui->MaxMarkLabel->hide();
        ui->MaxMarkSpinBox->hide();
        ui->TaskContentLabel->hide();
        ui->ComponentOrderSpinBox->setEnabled(true);
    }
    if (type == "CourseTutorials" && ui->ContentTextEdit->isHidden() && courseEditFlag){
        courseEditFlag = false;
        temptext = qobject_cast<CourseTutorials*>(coursepage->GetCourse()->getListComponents()[ui->ComponentOrderSpinBox->value()-1]);
        EditingStatus = 4;
        ui->ContentTextEdit->show();
        ui->ContentTextEdit->setText(temptext->getContent());
        ui->ComponentOrderSpinBox->setEnabled(false);
    }
    if (type == "CourseTutorials" && !ui->ContentTextEdit->isHidden() && courseEditFlag){
        courseEditFlag = false;
        EditingStatus = 0;
        ui->ContentTextEdit->setText("");
        ui->ContentTextEdit->hide();
        ui->ComponentOrderSpinBox->setEnabled(true);
    }
}

