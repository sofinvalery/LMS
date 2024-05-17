#include "coursedzpage.h"
#include "ui_coursedzpage.h"
#include "StyleManager/stylemanager.h"
#include <QFileDialog>

CourseDzPage::CourseDzPage(CourseTask* dz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseDzPage)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");
    this->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    ui->scrollArea->resize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);

    StyleManager::GetInstance()->setLabelStyle(ui->pathLbl, "Путь к файлу: " + dz->getAnswerUrl(), false, "black", true, 16);
    ui->pathLbl->move(ui->pathLbl->x(), 200);
    ui->pathLbl->setFixedSize(ui->pathLbl->sizeHint().width(), ui->pathLbl->sizeHint().height());

    StyleManager::GetInstance()->setLabelStyle(ui->titleLbl, dz->getTitle(), true, "black", true, 24);
    ui->titleLbl->setFixedSize(ui->titleLbl->sizeHint().width(), ui->titleLbl->sizeHint().height());
    ui->titleHorLine->setFixedSize(StyleManager::GetInstance()->getScreenWidth(), 2);
    ui->titleHorLine->setStyleSheet("border: 2px solid lightgrey;");
    if (dz->getVerdict() != 0)
    {
        StyleManager::GetInstance()->setLabelStyle(ui->verdictLbl, "Оценено: " + QString::number(dz->getVerdict()), false, "black", true, 20);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->setPathButton, ui->setPathButton->text(), true, 16, 13);
        ui->setPathButton->setEnabled(false);
    }
    else if (!dz->getAnswerUrl().isEmpty())
    {
        StyleManager::GetInstance()->setLabelStyle(ui->timeLbl, dz->getSolutionTime().toString("Сдано: dd.MM.yyyy"), false, "black", true, 20);
        StyleManager::GetInstance()->setDisableButtonStyle(ui->setPathButton, ui->setPathButton->text(), true, 16, 13);
        ui->setPathButton->setEnabled(false);
    }
    else
    {
        StyleManager::GetInstance()->setLabelStyle(ui->timeLbl, "Не сдано", false, "black", true, 20);
        StyleManager::GetInstance()->setLabelStyle(ui->verdictLbl, "Не оценено", false, "black", true, 20);
        StyleManager::GetInstance()->setBlueButtonStyle(ui->setPathButton, ui->setPathButton->text(), true, 16, 13);
        ui->setPathButton->setEnabled(true);
    }
    ui->setPathButton->move(ui->pathLbl->x(), 120);
    ui->timeLbl->setFixedSize(ui->timeLbl->sizeHint().width(), ui->timeLbl->sizeHint().height());
    ui->timeLbl->move(ui->titleLbl->width() + ui->titleLbl->x() + 30, ui->titleLbl->y());

    StyleManager::GetInstance()->setLabelStyle(ui->maxMarkLbl, QString::number(dz->getMaxMark()), false, "black", true, 20);
    ui->maxMarkLbl->setFixedSize(ui->maxMarkLbl->sizeHint().width(), ui->maxMarkLbl->sizeHint().height());
    ui->maxMarkLbl->move(ui->verdictLbl->width() + ui->verdictLbl->x() + 20, ui->verdictLbl->y());

    StyleManager::GetInstance()->setLabelStyle(ui->verdictLbl, QString::number(dz->getVerdict()), false, "black", true, 20); //текущая оценка
    ui->verdictLbl->setFixedSize(ui->verdictLbl->sizeHint().width(), ui->verdictLbl->sizeHint().height());
    ui->verdictLbl->move(ui->timeLbl->width() + ui->timeLbl->x() + 30, ui->timeLbl->y());

    ui->groupBoxContent->setTitle("Описание задания");
    ui->groupBoxContent->setFont(StyleManager::GetInstance()->getBold());
    ui->groupBoxContent->setStyleSheet(
        "QGroupBox {"
        "border-radius: 5px;"
        "border: 2px solid lightgrey;"
        "font-size: 20px;"
        "}");
    ui->contentLbl->setWordWrap(true);
    ui->contentLbl->setAlignment(Qt::AlignTop | Qt::AlignLeft);
     ui->contentLbl->setFixedWidth(400);
     ui->contentLbl->setMaximumWidth(400);
    ui->groupBoxContent->move(20, ui->titleHorLine->y() + 41);
    StyleManager::GetInstance()->setLabelStyle(ui->contentLbl, dz->getContent(), false, "black", true, 18); //описание
    ui->contentLbl->adjustSize();
    ui->groupBoxContent->setFixedWidth(420);
    ui->groupBoxContent->adjustSize();

    ui->groupBoxNote->setTitle("Замечание");
    ui->groupBoxNote->setFont(StyleManager::GetInstance()->getBold());
    ui->groupBoxNote->setStyleSheet(
        "QGroupBox {"
        "border-radius: 5px;"
        "border: 2px solid lightgrey;"
        "font-size: 20px;"
        "}");
    ui->noteLbl->setWordWrap(true);
    ui->noteLbl->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->noteLbl->setFixedWidth(400);
    ui->noteLbl->setMaximumWidth(400);
    ui->groupBoxNote->move(20, ui->groupBoxContent->y() + ui->groupBoxContent->height() + 40);
    StyleManager::GetInstance()->setLabelStyle(ui->noteLbl, dz->getNotes(), false, "black", true, 18); //комментарий препода
    ui->noteLbl->adjustSize();
    ui->groupBoxNote->setFixedWidth(420);
    ui->groupBoxNote->adjustSize();

    StyleManager::GetInstance()->setCustomButtonStyle(ui->exitButton, ui->exitButton->text(), "#E65D4F", true, 16, 4);
    ui->exitButton->move(StyleManager::GetInstance()->getScreenWidth() - ui->exitButton->size().width() - 10, ui->exitButton->size().height() - 10);

    StyleManager::GetInstance()->setBlueButtonStyle(ui->setPathButton, ui->setPathButton->text(), true, 16, 13);
    ui->setPathButton->setEnabled(true);
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

void CourseDzPage::on_setPathButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор файла", QDir::homePath(), "DZ files (*.xlsx *.pdf)");
    ui->pathLbl->setText("Путь к файлу: " + path);
    ui->pathLbl->setFixedSize(ui->pathLbl->sizeHint().width(), ui->pathLbl->sizeHint().height());
}
