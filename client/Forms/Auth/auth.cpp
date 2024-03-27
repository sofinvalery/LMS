#include "auth.h"
#include "ui_auth.h"

Auth::Auth(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Auth)
{
    ui->setupUi(this);
    //дизайн окна
    this->setWindowTitle("mOdle");
    this->setStyleSheet("background-color: white;");
    this->setFixedSize(this->size());
    //загрузка шрифта
    int fontIdBold = QFontDatabase::addApplicationFont(":/font/resources/Comfortaa-Bold.ttf");
    QString fontBold = QFontDatabase::applicationFontFamilies(fontIdBold).at(0);

    // int fontIdRegular = QFontDatabase::addApplicationFont(":/font/resources/Comfortaa-Regular.ttf");
    // QString fontRegular = QFontDatabase::applicationFontFamilies(fontIdRegular).at(0);

    //groupbox
    ui->groupBox->setFont(fontBold);
    ui->groupBox->setStyleSheet("QGroupBox { border: none; }");
    //errorbox
    ui->errorbox->setStyleSheet(
        "QLabel {"
        "qproperty-alignment: AlignCenter;"
        "color: red;"
        "font-size: 14px;"
        "}");
    ui->errorbox->setFont(fontBold);
    //labelAuth
    ui->labelAuth->setFont(fontBold);
    ui->labelAuth->setStyleSheet(
        "QLabel {"
        "qproperty-alignment: AlignCenter;"
        "font-size: 26px;"
        "}"
        );
    //дизайн логина
    ui->login->setStyleSheet(
        "QLineEdit {"
        "border: none;"
        "width: 100px;"
        "height: 50px;"
        "font-size: 20px;"
        "border-bottom: 1px solid lightgrey;"
        "}"
        );
    //дизайн пароля
    ui->password->setStyleSheet(
        "QLineEdit {"
        "border: none;"
        "width: 100px;"
        "height: 50px;"
        "font-size: 20px;"
        "border-bottom: 1px solid lightgrey;"
        "}"
        );
    //дизайн кнопки
    ui->pushButton->setCursor(Qt::PointingHandCursor);
    ui->pushButton->setFont(fontBold);
    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "background-color: #2194DE;"
        "border-radius: 10px;"
        "border: none;"
        "color: white;"
        "padding: 15px 32px;"
        "text-align: center;"
        "text-decoration: none;"
        "font-size: 16px;"
        "margin: 4px 2px;"
        "}"
        "QPushButton:hover {"
        "background-color: #4AB8FF;"
        "}"
        "QPushButton:pressed {"
        "background-color: #0E5FA8;"
        "}"
        );
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




