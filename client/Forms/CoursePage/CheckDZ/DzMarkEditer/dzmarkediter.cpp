#include "dzmarkediter.h"
#include "ui_dzmarkediter.h"
#include "StyleManager/stylemanager.h"
#include "ClientManager/clientmanager.h"
#include "ClientState/clientstate.h"
#include "Forms/CoursePage/coursepage.h"

DzMarkEditer::DzMarkEditer(Submit* submit,QList<Submit*> subs, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DzMarkEditer)
{
    ui->setupUi(this);
    task = qobject_cast<CourseTask*>(submit->work);
    this->subs=subs;
    this->submit=submit;
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");
    this->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    ui->scrollArea->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);

    StyleManager::GetInstance()->setLabelStyle(ui->titleLbl, task->getTitle(), true, "black", true, 24);
    ui->titleLbl->setFixedSize(ui->titleLbl->sizeHint().width(), ui->titleLbl->sizeHint().height());
    ui->titleHorLine->setFixedSize(StyleManager::GetInstance()->getScreenWidth(), 2);
    ui->titleHorLine->setStyleSheet("border: 2px solid lightgrey;");

    if (!task->getAnswerUrl().isEmpty())
    {
        StyleManager::GetInstance()->setLabelStyle(ui->timeLbl, task->getSolutionTime().toString("Сдано: dd.MM.yyyy"), false, "black", true, 20);
    }
    else
    {
        StyleManager::GetInstance()->setLabelStyle(ui->timeLbl, "Не сдано", false, "black", true, 20);
    }
    ui->timeLbl->setFixedSize(ui->timeLbl->sizeHint().width(), ui->timeLbl->sizeHint().height());
    ui->timeLbl->move(ui->titleLbl->width() + ui->titleLbl->x() + 30, ui->titleLbl->y());
    StyleManager::GetInstance()->setLabelStyle(ui->maxMarkLbl, QString::number(task->getMaxMark()), false, "black", true, 20);
    ui->maxMarkLbl->setFixedSize(ui->maxMarkLbl->sizeHint().width(), ui->maxMarkLbl->sizeHint().height());
    ui->maxMarkLbl->move(ui->timeLbl->width() + ui->timeLbl->x() + 20, ui->timeLbl->y());

    ui->verdictBox->setMaximum(task->getMaxMark());

    ui->noteTextEdit->setPlaceholderText("Комментарий к ДЗ");
    ui->noteTextEdit->setFont(StyleManager::GetInstance()->getRegular());

    StyleManager::GetInstance()->setLabelStyle(ui->fioLbl, submit->student->GetFIO(), true, "black", true, 20);
    ui->fioLbl->setFixedSize(ui->fioLbl->sizeHint().width(), ui->fioLbl->sizeHint().height());
    ui->fioLbl->move(ui->maxMarkLbl->x() + ui->maxMarkLbl->width() + 20, ui->maxMarkLbl->y());

    StyleManager::GetInstance()->setBlueButtonStyle(ui->excelButton, "Получить", true, 16, 13);

    StyleManager::GetInstance()->setBlueButtonStyle(ui->confirmButton, "Применить", true, 16, 13);


    StyleManager::GetInstance()->setCustomButtonStyle(ui->exitButton, "<--", "#E65D4F", true, 16, 4);
    ui->exitButton->move(20, 20);
}

DzMarkEditer::~DzMarkEditer()
{
    delete ui;
}

void DzMarkEditer::on_exitButton_clicked()
{
    this->close();
    delete this;
}

//получить
void DzMarkEditer::on_excelButton_clicked()
{
    ClientManager::GetInstance()->SendRequestFileToServer(task->getAnswerUrl());
}

//применить
void DzMarkEditer::on_confirmButton_clicked()
{
    if(ui->verdictBox->value()>0)
    {
        task->setNotes(ui->noteTextEdit->toPlainText());
        task->setVerdict(ui->verdictBox->value());
        QJsonObject sub;
        sub["Authentication"] = submit->student->Serialize();
        sub["CourseSubmit"] = submit->work->Serialize();
        ClientManager::GetInstance()->SendJsonToServer(TEACHERCHECKSUBMIT,sub);
        on_exitButton_clicked();
        qobject_cast<CoursePage*>(ClientState::GetInstance()->getMainwindow()->getWidget())->on_checkButton_clicked();
    }
}

