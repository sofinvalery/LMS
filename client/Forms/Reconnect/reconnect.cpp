#include "reconnect.h"
#include "ui_reconnect.h"
#include "StyleManager/stylemanager.h"

Reconnect::Reconnect(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reconnect)
{
    ui->setupUi(this);
    this->hide();
    this->setWindowTitle("vlad lox pidor");
    this->setStyleSheet("background-color: white;");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(this->size());
    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: 2px solid grey;"
        "border-radius: 10px;"
        "}");
    //statuslabel
    ui->statusLabel->setFont(StyleManager::GetInstance()->getRegular());
    ui->statusLabel->setText("Потеряно соединение");
    ui->statusLabel->setStyleSheet(
        "QLabel {"
        "font-size: 20px;"
        "color: red;"
        "qproperty-alignment: AlignCenter;"
        "}");
    //exitbutton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->exitButton, "Выход", "bold", 16, 10);
    ui->exitButton->setFixedSize(178, 40);
    ui->exitButton->move(30, 250);
    //reconnectbutton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->reconnectButton, "Переподключиться", "bold", 10, 10);
    ui->reconnectButton->setEnabled(true);
    ui->reconnectButton->setFixedSize(178, 40);
    ui->reconnectButton->move(40 + 178, 250);

}

void Reconnect::on_exitButton_clicked()
{
    QApplication::quit();
}

void Reconnect::on_reconnectButton_clicked()
{
    ui->statusLabel->setText("Gled lox");
    ui->reconnectButton->setEnabled(false);
    //reconnect dlya gleda
    //esli che okno zapuskaetsa kogda na glavnoe nazhimaesh v mainwindow

    //ui->exitButton->setEnabled(true);
    //ui->reconnectButton->setEnabled(true);
    //this->close();
}

Reconnect::~Reconnect()
{
    delete ui;
}
