#include "coursedzpage.h"
#include "ui_coursedzpage.h"
#include "StyleManager/stylemanager.h"

CourseDzPage::CourseDzPage(CourseTask* dz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDzPage)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");
    this->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    ui->scrollArea->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);

    StyleManager::GetInstance()->setLabelStyle(ui->titleLbl, dz->getTitle(), true, "black", true, 24);
    ui->titleLbl->setFixedSize(ui->titleLbl->sizeHint().width(), ui->titleLbl->sizeHint().height());

    StyleManager::GetInstance()->setLabelStyle(ui->timeLbl, dz->getSolutionTime().toString("Сдать до dd.MM.yyyy"), true, "black", true, 24);
    ui->timeLbl->setFixedSize(ui->timeLbl->sizeHint().width(), ui->timeLbl->sizeHint().height());

    StyleManager::GetInstance()->setLabelStyle(ui->maxMarkLbl, QString::number(dz->getMaxMark()), true, "black", true, 24);
    ui->maxMarkLbl->setFixedSize(ui->maxMarkLbl->sizeHint().width(), ui->maxMarkLbl->sizeHint().height());

    StyleManager::GetInstance()->setLabelStyle(ui->noteLbl, dz->getNotes(), true, "black", true, 24); //комментарий препода
    ui->noteLbl->setFixedSize(ui->noteLbl->sizeHint().width(), ui->noteLbl->sizeHint().height());

    StyleManager::GetInstance()->setLabelStyle(ui->verdictLbl, QString::number(dz->getVerdict()), true, "black", true, 24); //текущая оценка
    ui->verdictLbl->setFixedSize(ui->verdictLbl->sizeHint().width(), ui->verdictLbl->sizeHint().height());

    StyleManager::GetInstance()->setLabelStyle(ui->urlLbl, dz->getAnswerUrl(), true, "black", true, 24);
    ui->urlLbl->setFixedSize(ui->urlLbl->sizeHint().width(), ui->urlLbl->sizeHint().height());

    StyleManager::GetInstance()->setLabelStyle(ui->contentLbl, dz->getContent(), true, "black", true, 24); //описание
    ui->contentLbl->setFixedSize(ui->contentLbl->sizeHint().width(), ui->contentLbl->sizeHint().height());

    StyleManager::GetInstance()->setCustomButtonStyle(ui->exitButton, ui->exitButton->text(), "#E65D4F", true, 16, 4);
    ui->exitButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->exitButton->size().width() - 10, ui->exitButton->size().height() + 10);

    StyleManager::GetInstance()->setBlueButtonStyle(ui->setPathButton, ui->setPathButton->text(), true, 16, 13);
    ui->setPathButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->setPathButton->size().width() - 10, StyleManager::GetInstance()->getScreenHeight() - ui->setPathButton->size().height() - 10);
}

CourseDzPage::~CourseDzPage()
{
    delete ui;
}

void CourseDzPage::on_exitButton_clicked()
{
    this->close();
    delete this;
}

