#include "auth.h"
#include "ui_auth.h"

Auth::Auth(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Auth)
{
    //connect(SocketParser::GetInstance(),SIGNAL(logined()),this,SLOT(showMainPage()));
    ui->setupUi(this);
    //дизайн окна
    this->setWindowTitle("mOdle");
    this->setStyleSheet("background-color: white;");
    this->setFixedSize(this->size());
    //groupbox
    ui->groupBox->setFont(FontManager::GetInstance()->getBold());
    ui->groupBox->setStyleSheet("QGroupBox { border: none; }");
    //errorbox
    ui->errorbox->setFont(FontManager::GetInstance()->getBold());
    ui->errorbox->setStyleSheet(
        "QLabel {"
        "qproperty-alignment: AlignCenter;"
        "color: red;"
        "font-size: 14px;"
        "}");
    //labelAuth
    ui->labelAuth->setFont(FontManager::GetInstance()->getBold());
    ui->labelAuth->setStyleSheet(
        "QLabel {"
        "qproperty-alignment: AlignCenter;"
        "font-size: 26px;"
        "}"
        );
    //дизайн логина
    ui->login->setFont(FontManager::GetInstance()->getRegular());
    ui->login->setStyleSheet(
        "QLineEdit {"
        "border: none;"
        "width: 100px;"
        "height: 50px;"
        "font-size: 20px;"
        "border-bottom: 2px solid lightgrey;"
        "}"
        );
    //дизайн пароля
    ui->password->setFont(FontManager::GetInstance()->getRegular());
    ui->password->setStyleSheet(
        "QLineEdit {"
        "border: none;"
        "width: 100px;"
        "height: 50px;"
        "font-size: 20px;"
        "border-bottom: 2px solid lightgrey;"
        "}"
        );
    //дизайн кнопки
    ui->pushButton->setCursor(Qt::PointingHandCursor);
    ui->pushButton->setFont(FontManager::GetInstance()->getBold());
    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "background-color: #4AB8FF;"
        "border-radius: 10px;"
        "border: none;"
        "color: white;"
        "padding: 15px 32px;"
        "font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "background-color: #2194DE;"
        "}"
        "QPushButton:pressed {"
        "background-color: #0E5FA8;"
        "}"
        );
    //errorbox
    ui->errorbox->setText("Неправильный логин или пароль");
    ui->errorbox->hide();
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
    if (log == "" && pass == ""){
        //QMessageBox::information(this, "Статус входа", "Успешный вход");
        authstatus = 1;
        this->close();
    }
    else
    {
        //QMessageBox::warning(this, "Статус входа", "Ошибка входа");
        ui->errorbox->show();
    }
    //штука гледа полезная оч
    // Authentication* auth =new Authentication(log,pass);
    // QJsonObject json = auth->Serialize();
    // delete auth;
    // ClientManager::GetInstance()->Send(LOGINING,json);

}

void Auth::showMainPage()
{
    Authentication* auth=ClientState::GetInstance()->getAuth();
    QList<Course*> list= ClientState::GetInstance()->getListCourses();
    if (auth->IsAuthenticated()){
        MainWindow* mainwindow = new MainWindow;
        mainwindow->showFullScreen();
        this->close();
    }
    else
    {
        ui->errorbox->setText("Ошибка, введены неправильные данные");
    }
}




