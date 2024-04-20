#include "reconnect.h"
#include "ui_reconnect.h"
#include "StyleManager/stylemanager.h"
#include "ClientState/clientstate.h"

Reconnect::Reconnect(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reconnect)
{
    ui->setupUi(this);
    this->hide();
    this->setStyleSheet("background-color: white;");
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(this->size());
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: 2px solid grey;"
        "border-radius: 10px;"
        "}");
    //statuslabel
    StyleManager::GetInstance()->setLabelStyle(ui->statusLabel, "Потеряно соединение", false, "red", true, 20);
    ui->statusLabel->setAlignment(Qt::AlignHCenter);
    //exitbutton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->exitButton, "Выход", true, 16, 10);
    ui->exitButton->setFixedSize(178, 40);
    ui->exitButton->move(30, 250);
    //reconnectbutton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->reconnectButton, "Переподключиться", true, 10, 10);
    ui->reconnectButton->setEnabled(true);
    ui->reconnectButton->setFixedSize(178, 40);
    ui->reconnectButton->move(40 + 178, 250);

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

    //ui->exitButton->setEnabled(true);
    //ui->reconnectButton->setEnabled(true);
    //this->close();
}

void Reconnect::reconnectGood()
{
    qInfo()<<"reconnectGood";
    if(ClientState::GetInstance()->getAuth()!= nullptr)
    {
       ClientManager::GetInstance()->SendJsonToServer(RECONECT,ClientState::GetInstance()->getAuth()->Serialize());
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
