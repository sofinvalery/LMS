#include "coursesmpwidget.h"
#include "ui_coursesmpwidget.h"
#include "StyleManager/stylemanager.h"


#define arrlen 25

CoursesMPWidget::CoursesMPWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoursesMPWidget)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet("background-color: white;");
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: white;");
    this->move(0, 90);
    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height());
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

    int widgetwidth = MyWidget().width();
    int widgetheight = MyWidget().height();
    int vertspace = scr->availableGeometry().height()/ 17;
    int horizspace = scr->availableGeometry().width()/ 30;

    int columncnt = scr->availableGeometry().width()/ (widgetwidth + 2 * horizspace);

    //ui->scrollArea->resize(this->frameGeometry().width()-20,this->frameGeometry().height()-100);
    //ui->scrollAreaWidgetContents->setMinimumWidth(this->frameGeometry().width()-20); - ширина области в которой работает скролл
    ui->scrollAreaWidgetContents->setMinimumHeight((arrlen/columncnt)*(2*vertspace+widgetheight)+widgetheight/2 + 20);//+350);
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().width());
    // ui->gridLayoutWidget->setFixedWidth(this->frameGeometry().height());
    ui->gridLayoutWidget->resize(this->frameGeometry().width(),this->frameGeometry().height());
    ui->gridLayoutWidget->setMinimumHeight((arrlen/columncnt)*(2*vertspace+widgetheight)+widgetheight/2);//+350);
    // ui->gridLayout->setColumnMinimumWidth(0,351);
    // ui->gridLayout->setColumnMinimumWidth(1,351);
    // ui->gridLayout->setColumnMinimumWidth(2,351);
    // ui->gridLayout->setColumnMinimumWidth(3,351);
    //ui->gridLayout->setRowMinimumHeight(0,0);
    ui->gridLayout->setVerticalSpacing(vertspace);
    ui->gridLayout->setHorizontalSpacing(horizspace);
    //ui->gridLayout->setContentsMargins(0,0,0,0);
    //ui->gridLayout->setGeometry(this->frameGeometry());
    for (int i = 0, j = 0, z = 0; z < arrlen; z++, j++){
        course[z] = new MyWidget();
        if (z % columncnt == 0){
            j = 0;
            i++;
            //ui->gridLayout->setRowMinimumHeight(i,1);
        }
        ui->gridLayout->addWidget(course[z],i,j);

    }

}


CoursesMPWidget::~CoursesMPWidget()
{
    delete ui;
}
