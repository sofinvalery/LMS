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
    this->setWindowTitle("Reconnect");
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: 1px solid grey;"
        "}");
    //statuslabel
    StyleManager::GetInstance()->setLabelStyle(ui->statusLabel, "Потеряно соединение", false, "red", true, 20);
    ui->statusLabel->setFixedSize(ui->statusLabel->sizeHint().width(), ui->statusLabel->sizeHint().height());
    ui->statusLabel->move(this->width() / 2 - ui->statusLabel->width() / 2, 200);
    //exitbutton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->exitButton, "Выход", true, 16, 10);
    ui->exitButton->setFixedSize(178, 40);
    ui->exitButton->move(30, 250);
    //reconnectbutton
    StyleManager::GetInstance()->setBlueButtonStyle(ui->reconnectButton, "Переподключиться", true, 16, 10);
    ui->reconnectButton->setEnabled(true);
    ui->reconnectButton->setFixedSize(178, 40);
    ui->reconnectButton->move(40 + 178, 250);

    ui->processLabel->setMovie(movie);
    movie->setScaledSize(QSize(180, 133));
    ui->processLabel->setFixedSize(180, 133);
    ui->processLabel->move(this->width() / 2 - ui->processLabel->width() / 2, this->height() / 2 - ui->processLabel->height() / 2 - 50);
    movie->start();
}

void Reconnect::on_exitButton_clicked()
{
    QApplication::exit();
}

void Reconnect::on_reconnectButton_clicked()
{
        qInfo()<<"on_reconnectButton_clicked";
    ui->statusLabel->setText("Переподключение...");
    StyleManager::GetInstance()->setDisableButtonStyle(ui->reconnectButton, "Переподключиться", true, 16, 10);
    ui->statusLabel->setFixedSize(ui->statusLabel->sizeHint().width(), ui->statusLabel->sizeHint().height());
    ui->statusLabel->move(this->width() / 2 - ui->statusLabel->width() / 2 + 30, 200);
    ui->reconnectButton->setEnabled(false);
    emit re();
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
    StyleManager::GetInstance()->setBlueButtonStyle(ui->reconnectButton, "Переподключиться", true, 16, 10);
    ui->statusLabel->setFixedSize(ui->statusLabel->sizeHint().width(), ui->statusLabel->sizeHint().height());
    ui->statusLabel->move(this->width() / 2 - ui->statusLabel->width() / 2, 200);
}

Reconnect::~Reconnect()
{
    delete ui;
}
