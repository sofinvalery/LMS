#include "auth.h"
#include "ui_auth.h"


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
    if (authstatus != 1)
    this->exit = true;
}

void Auth::on_pushButton_clicked()
{
    QString log = ui->login->text();
    QString pass = ui->password->text();
    if (log == "1" && pass == "1"){
        authstatus = 1;
        this->close();
    }
    else
    {
        ui->errorbox->setText("Ошибка, введены неправильные данные");
    }
}




