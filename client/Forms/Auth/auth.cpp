#include "auth.h"
#include "ui_auth.h"
#include "StyleManager/stylemanager.h"

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
    ui->groupBox->setStyleSheet("QGroupBox { border: none; }");
    //errorbox
    StyleManager::GetInstance()->setLabelStyle(ui->errorbox, "Неправильный логин или пароль", "bold", "red", false, 14);
    //labelAuth
    StyleManager::GetInstance()->setLabelStyle(ui->labelAuth, "Авторизация", "bold", "black", true, 26);
    ui->labelAuth->setAlignment(Qt::AlignHCenter);
    //дизайн логина
    ui->login->setFont(StyleManager::GetInstance()->getRegular());
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
    ui->password->setFont(StyleManager::GetInstance()->getRegular());
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
    StyleManager::GetInstance()->setBlueButtonStyle(ui->pushButton, "Войти", "bold", 20, 10);
    ui->pushButton->setFixedHeight(50);
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
        ui->errorbox->show();
    }
}




