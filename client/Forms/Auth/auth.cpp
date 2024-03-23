#include "auth.h"
#include "ui_auth.h"
#include <QMessageBox>
#include "Forms/Main/mainwindow.h"


Auth::Auth(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Auth)
{
    ui->setupUi(this);
}

Auth::~Auth()
{
    delete ui;
}

void Auth::closeEvent(QCloseEvent *){
    exit = true;
}

void Auth::on_pushButton_clicked()
{
    QString log = ui->login->text();
    QString pass = ui->password->text();
    if (log == "admin" && pass == "admin"){
        //QMessageBox::information(this, "Статус входа", "Успешный вход");
        authstatus = 1;
        this->close();
    }
    else
    {
        //QMessageBox::warning(this, "Статус входа", "Ошибка входа");
        ui->errorbox->setText("Ошибка, введены неправильные данные");
    }
}




