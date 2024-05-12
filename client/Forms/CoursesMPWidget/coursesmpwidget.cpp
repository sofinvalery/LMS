#include "coursesmpwidget.h"
#include "ui_coursesmpwidget.h"
#include <QScreen>
#include <QScrollBar>
#include "../../ClientState/clientstate.h"
#include "StyleManager/stylemanager.h"
#include "ClientState/clientstate.h"
#include "../common/course/course.h"


CoursesMPWidget::CoursesMPWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoursesMPWidget)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet("background-color: white;");
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");
    this->move(0, 90);

    this->resize( StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    ui->scrollArea->setWidgetResizable(true);

    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->scrollArea->resize(this->frameGeometry().width(),this->frameGeometry().height() - 42);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //groupbox
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border: none;"
        "}");
    //scrollarea
    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);
    Course* temp =new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1));
    int widgetwidth = MyWidget(temp).width();
    int widgetheight = MyWidget(temp).height();
    delete temp;
    int vertspace = StyleManager::GetInstance()->getScreenHeight()/ 17;
    int horizspace = StyleManager::GetInstance()->getScreenWidth()/ 30;

    int columncnt = StyleManager::GetInstance()->getScreenWidth()/ (widgetwidth + 2 * horizspace);

    //ui->scrollArea->resize(this->frameGeometry().width()-20,this->frameGeometry().height()-100);
    //ui->scrollAreaWidgetContents->setMinimumWidth(this->frameGeometry().width()-20); - ширина области в которой работает скролл
    ui->scrollAreaWidgetContents->setMinimumHeight((ClientState::GetInstance()->getListCourses().size()/columncnt+1)*(2*vertspace+widgetheight)+widgetheight/2 + 20);//+350);
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().width());
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().height());
    ui->gridLayoutWidget->resize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->gridLayoutWidget->setMinimumHeight((ClientState::GetInstance()->getListCourses().size()/columncnt)*(2*vertspace+widgetheight)+widgetheight/2);//+350);
    // ui->gridLayout->setColumnMinimumWidth(0,351);
    // ui->gridLayout->setColumnMinimumWidth(1,351);
    // ui->gridLayout->setColumnMinimumWidth(2,351);
    // ui->gridLayout->setColumnMinimumWidth(3,351);
    //ui->gridLayout->setRowMinimumHeight(0,0);
    ui->gridLayout->setVerticalSpacing(vertspace);
    ui->gridLayout->setHorizontalSpacing(horizspace);
    //ui->gridLayout->setContentsMargins(0,0,0,0);
    //ui->gridLayout->setGeometry(this->frameGeometry());
    qInfo()<< ClientState::GetInstance()->getListCourses().size();
    for (int i = 0, j = 0, z = 0; z < ClientState::GetInstance()->getListCourses().size(); z++, j++){
        if (z % columncnt == 0){
            j = 0;
            i++;
            //ui->gridLayout->setRowMinimumHeight(i,1);
        }
        ui->gridLayout->addWidget(new MyWidget(ClientState::GetInstance()->getListCourses()[z]),i,j);
    }

}


CoursesMPWidget::~CoursesMPWidget()
{
    delete ui;
}
