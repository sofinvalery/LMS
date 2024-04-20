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
    StyleManager::GetInstance()->setLabelStyle(ui->errorbox, "Неправильный логин или пароль", true, "red", false, 14);
    //labelAuth
    StyleManager::GetInstance()->setLabelStyle(ui->labelAuth, "Авторизация", true, "black", true, 26);
    ui->labelAuth->setAlignment(Qt::AlignHCenter);
    //дизайн логина
    StyleManager::GetInstance()->setLineEditStyle(ui->login, "Логин", false, 20, 100, 50);

    //дизайн пароля
    StyleManager::GetInstance()->setLineEditStyle(ui->password, "Пароль", false, 20, 100, 50);

    //дизайн кнопки
    StyleManager::GetInstance()->setBlueButtonStyle(ui->pushButton, "Войти", true, 20, 10);
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




