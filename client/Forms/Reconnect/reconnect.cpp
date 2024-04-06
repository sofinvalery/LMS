#include "reconnect.h"
#include "ui_reconnect.h"
#include "FontManager/fontmanager.h"

Reconnect::Reconnect(QWidget *parent)
    : QDialog(parent,Qt::WindowStaysOnTopHint)
    , ui(new Ui::Reconnect)
{
    ui->setupUi(this);
    this->hide();
    this->setStyleSheet("background-color: white;");
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setFixedSize(this->size());
    //statuslabel
    ui->statusLabel->setFont(FontManager::GetInstance()->getRegular());
    ui->statusLabel->setText("Потеряно соединение");
    ui->statusLabel->setStyleSheet(
        "QLabel {"
        "font-size: 20px;"
        "color: red;"
        "qproperty-alignment: AlignCenter;"
        "}");
    //exitbutton
    ui->exitButton->setEnabled(true);
    ui->exitButton->setFont(FontManager::GetInstance()->getBold());
    ui->exitButton->setText("Выход");
    ui->exitButton->setFixedSize(178, 40);
    ui->exitButton->move(30, 250);
    ui->exitButton->setStyleSheet(
        "QPushButton {"
        "background-color: #4AB8FF;"
        "border-radius: 10px;"
        "border: none;"
        "color: white;"
        //"padding: 15px 32px;"
        "font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "background-color: #2194DE;"
        "}"
        "QPushButton:pressed {"
        "background-color: #0E5FA8;"
        "}");
    //reconnectbutton
    ui->reconnectButton->setEnabled(true);
    ui->reconnectButton->setFont(FontManager::GetInstance()->getBold());
    ui->reconnectButton->setText("Переподключиться");
    ui->reconnectButton->setFixedSize(178, 40);
    ui->reconnectButton->move(40 + 178, 250);
    ui->reconnectButton->setStyleSheet(
        "QPushButton {"
        "background-color: #4AB8FF;"
        "border-radius: 10px;"
        "border: none;"
        "color: white;"
        //"padding: 15px 32px;"
        "font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "background-color: #2194DE;"
        "}"
        "QPushButton:pressed {"
        "background-color: #0E5FA8;"
        "}");

}

void Reconnect::on_exitButton_clicked()
{
    QApplication::exit();
}

void Reconnect::on_reconnectButton_clicked()
{
        qInfo()<<"on_reconnectButton_clicked";
    ui->statusLabel->setText("Переподключение...");
    ui->reconnectButton->setEnabled(false);
    emit re();
    //reconnect dlya gleda
    //esli che okno zapuskaetsa kogda na glavnoe nazhimaesh v mainwindow

    //ui->exitButton->setEnabled(true);
    //ui->reconnectButton->setEnabled(true);
    //this->close();
}

void Reconnect::reconnectGood()
{
    qInfo()<<"reconnectGood";
    if(ClientState::GetInstance()->getAuth()!= nullptr)
    {
       ClientManager::GetInstance()->Send(RECONECT,ClientState::GetInstance()->getAuth()->Serialize());
    }
    this->done(0);
}

void Reconnect::reconnectEr(QAbstractSocket::SocketError socketError)
{
    qInfo()<<"reconnectEr";
    ui->statusLabel->setText("Ошибка переподключения");
    ui->reconnectButton->setEnabled(true);
}

Reconnect::~Reconnect()
{
    delete ui;
}