#include "courseattestacion.h"
#include "ui_courseattestacion.h"
#include "StyleManager/stylemanager.h"
#include "ClientState/clientstate.h"

CourseAttestacion::CourseAttestacion(CourseComponent * test, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseAttestacion)
{
    ui->setupUi(this);
    this->test = qobject_cast<CourseTest*>(test);
    icon = new QPixmap(":/img/resources/test.png");
    ui->LabelIMG->setPixmap(icon->scaled(31, 21, Qt::KeepAspectRatio));
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->DownloadButton, this->test->getTitle(), true, 16, 15);
    ui->DownloadButton->setFixedSize(ui->DownloadButton->sizeHint().width(), ui->DownloadButton->sizeHint().height());
}

CourseAttestacion::~CourseAttestacion()
{
    delete ui;
}

void CourseAttestacion::SetTextOnButton(QString buttontext)
{
    StyleManager::GetInstance()->setSimpleButtonStyle(ui->DownloadButton, buttontext, true, 16, 15);
    ui->DownloadButton->setFixedSize(ui->DownloadButton->sizeHint().width(), ui->DownloadButton->sizeHint().height());
}

void CourseAttestacion::on_DownloadButton_clicked()
{
    testwidget = new TestWidget(test);
    testwidget->setParent(ClientState::GetInstance()->getMainwindow());
    testwidget->show();
    qDebug() << "bebra";
}

